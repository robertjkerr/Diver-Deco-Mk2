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
    static Segment asc_seg(int depth1, int depth2, const int* gas, bool in_deco) {
        int rate, time;

        //Pick ascent rate
        rate = in_deco == true ? MAX_DECO_ASCENT_RATE : MAX_ASCENT_RATE;

        //Find time and create segment
        time = static_cast<int> ((depth2 - depth1) / rate);
        return Segment(depth1, rate, time, gas);
    }


    //******************************************
    // Ascend to ceiling routine
    //******************************************
    static int asc2ceil(Tissues* compartments, int current_depth,
                            int* gas, bool in_deco) {

        int ceiling = compartments->get_ceiling();
        Segment segment = asc_seg(current_depth, ceiling, gas, in_deco);
        compartments->invoke_dive_segment(segment);
        return ceiling;
    }


    //******************************************
    // Waits at depth until ceiling changes
    //******************************************
    static void wait(Tissues* compartments, int current_depth, int* gas, float dt) {
        int first_ceiling, ceiling;

        first_ceiling = ROUNDSTOP(compartments->get_ceiling());
        ceiling = first_ceiling;

        while (ceiling == first_ceiling) {
            Segment segment = stop2seg(DecoStop(current_depth, dt, gas));
            compartments->invoke_dive_segment(segment);
            
            ceiling = ROUNDSTOP(compartments->get_ceiling());
        }

    }


    //******************************************
    // Returns the richest possible gas
    //******************************************
    static int* select_rich_gas(std::vector<int*> gases, 
                        int current_depth, bool in_deco) {

        int* rich_gas = gases[0];
        int mod, best_mod;

        for (int n = 0; n < gases.size(); n++) {
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