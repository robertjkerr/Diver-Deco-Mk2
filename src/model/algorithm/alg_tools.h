/*
Static functions for use in the deco algorithm
This file exists to split the algorithm code
 - it is not for more efficient compilation
*/

#ifndef ALG_TOOLS_H
#define ALG_TOOLS_H

#include "../compartments/tissues.h"

namespace DecoModel {
    //******************************************
    // Turn a single deco stop into a segment
    //******************************************
    static Segment stop2seg(DecoStop stop) {
        return Segment(stop.depth, 0.0f, stop.time, stop.gas);
    }


    //******************************************
    // Create ascent segment
    //******************************************
    static Segment asc_seg(uint16_t depth1, uint16_t depth2, 
            const uint8_t* gas, bool in_deco) {

        int8_t rate; 
        uint16_t time;

        //Pick ascent rate
        rate = in_deco == true ? MAX_DECO_ASCENT_RATE : MAX_ASCENT_RATE;

        //Find time and create segment
        time = static_cast<uint16_t> ((depth2 - depth1) / rate);
        return Segment(depth1, rate, time, gas);
    }


    //******************************************
    // Ascend to ceiling routine
    //******************************************
    static uint16_t asc2ceil(Buhlmann* compartments, uint16_t current_depth,
                            uint8_t* gas, bool in_deco) {

        uint16_t ceiling;

        do {
            ceiling = ROUNDSTOP(compartments->get_ceiling());
            compartments->invoke_dive_segment(asc_seg(current_depth, ceiling, gas, in_deco));
        }
        while (ceiling == ROUNDSTOP(compartments->get_ceiling()));

        return ceiling;
    }


    //******************************************
    // Waits at depth until ceiling changes
    //******************************************
    static void wait(Buhlmann* compartments, uint16_t current_depth, uint8_t* gas, float time) {
        Segment segment = stop2seg(DecoStop(current_depth, time, gas)) ;
        compartments->invoke_dive_segment(segment);
    }


    //******************************************
    // Returns the richest possible gas
    //******************************************
    static uint8_t* select_rich_gas(std::vector<uint8_t*>& gases, 
                        uint16_t current_depth, bool in_deco) {

        uint8_t* rich_gas = gases[0];
        uint16_t mod, best_mod;

        for (uint8_t n = 0; n < gases.size(); n++) {
            best_mod = MOD(rich_gas, in_deco);
            mod = MOD(gases[n], in_deco);
            if (mod >= current_depth && mod > best_mod) {
                rich_gas = gases[n];
            }        
        }

        return rich_gas;
    }

}

#endif //ALG_TOOLS_H