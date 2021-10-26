/*
Logic for tissues class
*/

#include "tissues_new.h"
#include "f90/f90_mod.h"

namespace DecoModel {

    Tissues::Tissues(bool vpm_flag, float GFLo_In, float GFHi_In) 
    : GFHi(GFHi_In), GFLo(GFLo_In) {

        int i;

        for (i = 0; i < NUM_COMPARTMENTS; i++) {
            cell_pressures[0][i] = RESET_N2;
            cell_pressures[1][i] = RESET_HE;
        }
    }

    void Tissues::invoke_dive_segment_buhl(Segment segment) {
        float gas[NUM_INERT_GASES];
        int16_t start_depth, time;
        int8_t depth_rate;

        gas[0] = static_cast<float> (100 - segment.gas[0] - segment.gas[1]) / 100;
        gas[1] = static_cast<float> (segment.gas[1]) / 100;

        start_depth = static_cast<int16_t> (segment.start_depth);
        depth_rate = static_cast<int16_t> (segment.rate);
        time = static_cast<int16_t> (segment.time);

        F90Mod::invoke_buhl_seg((float**) cell_pressures, gas,
            &start_depth, &depth_rate, &time);

    }

    uint16_t Tissues::get_ceiling_buhl() {
        int16_t ceiling = F90Mod::get_ceiling((float**) cell_pressures, &GF);
        return static_cast<uint16_t> (ceiling);
    }


    uint16_t Tissues::get_ceiling() {
        return get_ceiling_buhl();
    }
}