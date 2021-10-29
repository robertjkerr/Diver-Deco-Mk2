/*
Logic for Buhlmann class
*/

#include "Tissues.h"
#include "f90/f90_mod.h"

namespace DecoModel {

    Buhlmann::Buhlmann(float GFLo_In, float GFHi_In) 
    : GFHi(GFHi_In), GFLo(GFLo_In) {

        int i;
        GF = GFLo;

        for (i = 0; i < NUM_COMPARTMENTS; i++) {
            cell_pressures[0][i] = RESET_N2;
            cell_pressures[1][i] = RESET_HE;
        }
    }

    void Buhlmann::invoke_dive_segment_buhl(float gas[NUM_INERT_GASES], int16_t start_depth, 
                    int8_t depth_rate, int16_t time) {
        
        F90Mod::invoke_dive_segment_buhl(cell_pressures, gas,
            &start_depth, &depth_rate, &time);
    }


    void Buhlmann::invoke_dive_segment(Segment segment) {
        float gas[NUM_INERT_GASES], pO2_rate;
        int16_t start_depth, time;
        int8_t depth_rate;

        gas[0] = static_cast<float> (100 - segment.gas[0] - segment.gas[1]) / 100;
        gas[1] = static_cast<float> (segment.gas[1]) / 100;

        start_depth = static_cast<int16_t> (segment.start_depth);
        depth_rate = static_cast<int8_t> (segment.rate);
        time = static_cast<int16_t> (segment.time) * 60;

        invoke_dive_segment_buhl(gas, start_depth, depth_rate, time);

        pO2_rate = static_cast<float> (segment.gas[0]) * depth_rate / 100;
        otu = otu + OTU(pO2_rate, time, DEPTH2PRES(start_depth));
    }

    uint16_t Buhlmann::get_ceiling() {
        int16_t ceiling = F90Mod::get_ceiling(cell_pressures, &GF);
        return static_cast<uint16_t> (ceiling);
    }


    void Buhlmann::set_GF_grad(uint16_t first_stop_depth) {
        float first_ceiling = DEPTH2PRES(first_stop_depth);
        GF_grad = (GFHi - GFLo) / (1 - first_ceiling);
    }

    void Buhlmann::reset_GF(uint16_t depth) {
        float p_amb = DEPTH2PRES(depth);
        GF = GF_grad * (p_amb - 1.3f) + GFHi;
    }
}