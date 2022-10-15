/*
Logic for Buhlmann class
*/

#include "Tissues.h"
#include "f90/f90_mod.h"

namespace DecoModel {

    Buhlmann::Buhlmann(float GFLo_In, float GFHi_In) 
    : GFHi(GFHi_In), GFLo(GFLo_In) {

        uint8_t i;
        GF = GFLo;

        // Initialise all tissue compartments to surface pressures
        for (i = 0; i < NUM_COMPARTMENTS; i++) {
            cell_pressures[0][i] = RESET_N2;
            cell_pressures[1][i] = RESET_HE;
        }
    }

    void Buhlmann::invoke_dive_segment_buhl(float gas[NUM_INERT_GASES], int16_t start_depth, 
                    int8_t depth_rate, int16_t time) {
        /*
        Wrapper for f90 function. Does tissue partial pressure calculations*/
        
        F90Mod::invoke_dive_segment_buhl(cell_pressures, gas,
            &start_depth, &depth_rate, &time);
    }


    void Buhlmann::invoke_dive_segment(Segment segment) {
        /*
        Performs on/off-gas calculations based on a dive segment
        In: Segment struct. Contains, depth, time, descent rate and the gas being breathed
        Effects: Modifies cell_pressures array to describe the partial pressures of dissolved gases
        */

        float gas[NUM_INERT_GASES];
        int16_t start_depth, time;
        int8_t depth_rate;

        // Converts gas from {%02, %He} to {fN2, fHe}
        gas[0] = static_cast<float> (100 - segment.gas[0] - segment.gas[1]) / 100;
        gas[1] = static_cast<float> (segment.gas[1]) / 100;

        // Extract start depth, descent rate and time length of segment
        start_depth = static_cast<int16_t> (segment.start_depth);
        depth_rate = static_cast<int8_t> (segment.rate);
        time = static_cast<int16_t> (segment.time) * 60;

        // Calls f90 function and performs on/off-gas calculations, changing state of tissues
        invoke_dive_segment_buhl(gas, start_depth, depth_rate, time);
    }

    uint16_t Buhlmann::get_ceiling() {
        /*
        Calls f90 ceiling function which calculates the shallowest depth the tissues can go to
        In: No args, only depends on state of object
        Out: Integer - ascent ceiling
        */

        int16_t ceiling = F90Mod::get_ceiling(cell_pressures, &GF);
        return static_cast<uint16_t> (ceiling);
    }


    void Buhlmann::set_GF_grad(uint16_t first_stop_depth) {
        /*
        Sets the gradient of the gradient factor. Once the first stop depth is known (ie ceiling)
         we can determine how the GF will change once we start ascending
        In: Integer - depth of the first deco stop
        Effects: changes GF_grad based on first stop depth, GFHi and GFLo
        */

        float first_ceiling = DEPTH2PRES(first_stop_depth);
        GF_grad = (GFHi - GFLo) / (1 - first_ceiling);
    }

    void Buhlmann::reset_GF(uint16_t depth) {
        /*
        Sets GF based on current depth. GF is determined from a straight line from
         (first deco stop depth, GFHi) to (surface, GFLo)
        set_GF_grad must have been called prior to this
        In: Integer - current depth
        Effects: changes the gradient factor
        */

        float p_amb = DEPTH2PRES(depth);
        GF = GF_grad * (p_amb - 1.3f) + GFHi;
    }
}