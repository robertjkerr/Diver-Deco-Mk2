/*
Deco algorithm logic
*/

#include "deco_algorithm.h"
#include "alg_tools.h"

namespace DecoModel{
    //******************************************
    // Deco stops algorithm
    //******************************************
    std::vector<DecoStop> get_deco_stops(Tissues compartments, uint16_t current_depth,
                            std::vector<uint8_t*> gases, uint8_t dt) {
        //Note that compartments is passed by value so the obj is copied

        std::vector<DecoStop> stops;
        uint16_t ceiling, time;
        uint8_t* gas;
        bool in_deco = false;

        do {
            if (in_deco == false) {
                //Ascend to first stop, set GF
                gas = gases[0];
                current_depth = asc2ceil(&compartments, current_depth, gas, in_deco);
                compartments.set_GF_grad(current_depth);
                in_deco = true;
            }
            else {
                //Ordinary deco stop - select gas, set GF and wait till ceiling ascends
                gas = select_rich_gas(gases, current_depth, in_deco);
                compartments.reset_GF(current_depth);

                ceiling = ROUNDSTOP(compartments.get_ceiling());
                time = 0;
                while (current_depth == ceiling) {
                    wait(&compartments, current_depth, gas, dt);
                    time = time + dt;
                }

                stops.push_back(DecoStop(current_depth, time, gas));

                //Ascend to next stop, or the surface
                current_depth = asc2ceil(&compartments, current_depth, gas, in_deco);
            }
        }
        while (current_depth > 0);
        
        return stops;
    }


    //******************************************
    // Turn deco stops to dive segments
    //******************************************
    /*
    std::vector<Segment> deco2seg(uint16_t bottom_depth,
        std::vector<DecoStop>& stops, uint8_t* bottom_gas) {

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
    */
}

