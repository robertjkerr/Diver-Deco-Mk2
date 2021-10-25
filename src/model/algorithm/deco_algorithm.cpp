/*
Deco algorithm logic
*/

#include "deco_algorithm.h"
#include "alg_tools.h"

namespace DecoModel{
    //******************************************
    // Deco stops algorithm
    //******************************************
    std::vector<DecoStop> get_deco_stops(Tissues compartments, int current_depth,
                                    std::vector<int*> gases, float dt) {
        //Note that compartments is passed by value so the obj is copied
        float time, max_PO2;
        int num_stops, stop_depth;
        bool in_deco = false;
        std::vector<DecoStop> deco_stops;
        int* gas;
        int ceil, new_ceil;

        //Select richest possible gas, ascend to next stop and wait 
        do {
            gas = select_rich_gas(gases, current_depth, in_deco);
            //Ascend twice to account for offgassing during first ascent
            current_depth = asc2ceil(&compartments, current_depth, gas, in_deco);
            current_depth = asc2ceil(&compartments, current_depth, gas, in_deco);

            compartments.set_GF_grad(current_depth);
            in_deco = true;

            ceil = ROUNDSTOP(compartments.get_ceiling());
            new_ceil = ceil;
            time = 0;

            while (ceil == new_ceil) {
                wait(&compartments, current_depth, gas, dt);
                new_ceil = ROUNDSTOP(compartments.get_ceiling());
                time = time + dt;
            }

            //Append deco_stop to vector. Convert time to minutes
            deco_stops.push_back(DecoStop(current_depth, time/60, gas));
        }
        while (current_depth > 0);

        return deco_stops;
    }


    //******************************************
    // Turn deco stops to dive segments
    //******************************************
    std::vector<Segment> deco2seg(int bottom_depth,
        std::vector<DecoStop>& stops, int* bottom_gas) {

        int depth, next_depth, stop_num;
        std::vector<Segment> segments;
        DecoStop stop;

        next_depth = stops[0].depth; 

        //Ascent from bottom to first stop
        segments.push_back(asc_seg(next_depth, bottom_depth, bottom_gas, false));

        //Deco stops and ascents
        for (stop_num = 0; stop_num < stops.size(); stop_num++) {
            segments.push_back(stop2seg(stops[stop_num]));

            depth = stops[stop_num].depth;

            //Get next stop depth
            next_depth = depth == SHALLOWEST_STOP ? 0
                            : stops[stop_num + 1].depth;

            //Append ascent to next stop
            segments.push_back(asc_seg(depth, next_depth, stops[stop_num].gas, true));
        } 

        return segments;
    }
}

