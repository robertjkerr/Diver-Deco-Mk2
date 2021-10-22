/*
Gas tracking structures
*/

#ifndef GAS_TRACKING_H
#define GAS_TRACKING_H

#include "../types_constants/types.h"

namespace DecoModel {
    struct Tank {
        const int gas[NUM_INERT_GASES];
        const int breathing_rate;
        int vol_used;

        void breathe(int depth, int time);
        Tank(int b_rate, int* gas_mix);
    };
}

#endif //GAS_TRACKING_H