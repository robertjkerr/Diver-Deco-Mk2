/*
Gas tracking header
*/

#ifndef GAS_TRACK_H
#define GAS_TRACK_H

#include <vector>

namespace Body {
    //Breathing rate should be litres per minute
    const int breathing_rate = 25;

    //Structure for a tank of gas
    struct Tank {
        const std::vector<int> gas;
        int vol_gas_used = 0;

        Tank(std::vector<int> gas_mix);
        void use_gas(int depth, int time, int rate);
    };
}

#endif //GAS_TRACK_H