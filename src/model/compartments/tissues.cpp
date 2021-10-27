/*
Logic for tissues class
*/

#include "tissues.h"
#include "f90/f90_mod.h"

namespace DecoModel {

    Tissues::Tissues(float GFLo_In, float GFHi_In) 
    : GFHi(GFHi_In), GFLo(GFLo_In) {

        int i;

        GF = GFLo;

        for (i = 0; i < NUM_COMPARTMENTS; i++) {
            cell_pressures[0][i] = RESET_N2;
            cell_pressures[1][i] = RESET_HE;
        }
    }

    void Tissues::invoke_dive_segment_buhl(float* gas, int16_t start_depth, 
                    int8_t depth_rate, int16_t time) {
        
        F90Mod::invoke_buhl_seg((float**) cell_pressures, gas,
            &start_depth, &depth_rate, &time);
    }


    void Tissues::invoke_dive_segment(Segment segment) {
        float gas[NUM_INERT_GASES];
        int16_t start_depth, time;
        int8_t depth_rate;

        gas[0] = static_cast<float> (100 - segment.gas[0] - segment.gas[1]) / 100;
        gas[1] = static_cast<float> (segment.gas[1]) / 100;

        start_depth = static_cast<int16_t> (segment.start_depth);
        depth_rate = static_cast<int8_t> (segment.rate);
        time = static_cast<int16_t> (segment.time);

        invoke_dive_segment_buhl(gas, start_depth, depth_rate, time);
    }

    uint16_t Tissues::get_ceiling_buhl() {
        int16_t ceiling = F90Mod::get_ceiling((float**) cell_pressures, &GF);
        return static_cast<uint16_t> (ceiling);
    }


    uint16_t Tissues::get_ceiling() {return get_ceiling_buhl();}

    float Tissues::get_otu() {return otu;}
    void Tissues::set_otu(float new_otu) {otu = new_otu;}

    void Tissues::set_GF_grad(uint16_t first_stop_depth) {
        float first_ceiling = DEPTH2PRES(first_stop_depth);
        GF_grad = (GFHi - GFLo) / (1 - first_ceiling);
    }

    void Tissues::reset_GF(uint16_t depth) {
        float p_amb = DEPTH2PRES(depth);
        GF = GF_grad * (p_amb - 1.3f) + GFHi;
    }
}