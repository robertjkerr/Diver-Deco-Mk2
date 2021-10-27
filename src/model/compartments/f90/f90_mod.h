/*
Header for Fortran method interface
*/

#ifndef FORTRAN_INCLUDE_H
#define FORTRAN_INCLUDE_H

#include <stdint.h>

namespace F90Mod {
    extern "C" {
        void invoke_buhl_seg(float** pressures_both, float* gas, 
                    int16_t* start_depth, int8_t* depth_rate, int16_t* time);

        int16_t get_ceiling(float** pressures_both, float* GF); //pressures_both = {{N2 pressures}, {He pressures}}
    }
}

#endif //FORTRAN_INCLUDE_H