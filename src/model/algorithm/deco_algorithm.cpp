/*
Deco algorithm logic
*/

#include "deco_algorithm.h"

namespace DecoModel{
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
        compartments->invoke_dive_segment(asc_seg(current_depth, ceiling, gas, in_deco));
        return ceiling;
    }


    //******************************************
    // Waits at depth until ceiling changes
    //******************************************
    static void wait(Tissues* compartments, int current_depth, int* gas) {
        int first_ceiling, ceiling;
        float dt = compartments->dt;

        first_ceiling = ROUNDSTOP(compartments->get_ceiling());
        ceiling = first_ceiling;

        while (ceiling == first_ceiling) {
            compartments->invoke_dive_segment(
                stop2seg(DecoStop(current_depth, dt, gas)));
            
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

    //******************************************
    // Deco stops algorithm
    //******************************************
    std::vector<DecoStop> get_deco_stops(Tissues compartments, int current_depth,
                                    std::vector<int*> gases) {
        //Note that each cell obj is within the Tissues obj so they are all copied
        float time, max_PO2;
        int num_stops, stop_depth;
        bool in_deco = false;
        std::vector<DecoStop> deco_stops;
        int* gas;

        //Select richest possible gas, ascend to next stop and wait 
        do {
            gas = select_rich_gas(gases, current_depth, in_deco);
            current_depth = asc2ceil(&compartments, current_depth, gas, in_deco);
            in_deco = true;

            
        }
        while (current_depth > 0);


        return deco_stops;
    }


    //******************************************
    // Turn deco stops to dive segments
    //******************************************
    std::vector<Segment> deco2seg(int bottom_depth,
        std::vector<DecoStop*> stops, int* bottom_gas) {

        int depth, next_depth, stop_num;
        std::vector<Segment> segments;
        DecoStop* stop;

        next_depth = stops[0]->depth; 

        //Ascent from bottom to first stop
        segments.push_back(asc_seg(next_depth, bottom_depth, bottom_gas, false));

        //Deco stops and ascents
        for (stop_num = 0; stop_num < stops.size(); stop_num++) {
            stop = stops[stop_num];
            segments.push_back(stop2seg(*stop));

            depth = stop->depth;

            //Get next stop depth
            next_depth = depth == SHALLOWEST_STOP ? next_depth = 0
                            : next_depth = stops[stop_num + 1]->depth;

            //Append ascent to next stop
            segments.push_back(asc_seg(depth, next_depth, stop->gas, true));
        } 

        return segments;
    }
}

