/*
Header for Fortran method interface
*/

#ifndef FORTRAN_INCLUDE_H
#define FORTRAN_INCLUDE_H

#include <stdint.h>

namespace F90Mod {
    extern "C" {
        void invoke_dive_segment_buhl(float pressures_both[NUM_INERT_GASES][NUM_COMPARTMENTS], 
            float gas[NUM_INERT_GASES], int16_t* start_depth, int8_t* depth_rate, int16_t* time);

        int16_t get_ceiling(float pressures_both[NUM_INERT_GASES][NUM_COMPARTMENTS], float* GF); //pressures_both = {{N2 pressures}, {He pressures}}
    }
}

#endif //FORTRAN_INCLUDE_H