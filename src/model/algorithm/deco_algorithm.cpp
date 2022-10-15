/*
Deco algorithm logic
*/

#include "deco_algorithm.h"
#include "alg_tools.h"

namespace DecoModel{
    //******************************************
    // Deco stops algorithm
    //******************************************
    std::vector<DecoStop> get_deco_stops(Buhlmann compartments, uint16_t current_depth,
                            std::vector<uint8_t*> gases, uint8_t dt) {
        //Note that compartments is passed by value so the obj is copied

        bool in_deco = false;
        std::vector<DecoStop> stops;
        uint16_t ceiling, time, num_stops;
        uint8_t i;
        uint8_t* gas = select_rich_gas(gases, current_depth, in_deco);
        DecoStop stop(0, 0, gas);

        
        // Ascend to ceiling 
        do {
            // Check ceiling
            ceiling = compartments.get_ceiling();

            // Choose richest gas and ascend to the ceiling
            gas = select_rich_gas(gases, current_depth, in_deco);
            current_depth = asc2ceil(&compartments, current_depth, gas, in_deco);

        // Is ceiling continue to reduce while the compartments ascend and offgas? Ascend until ceiling is hit
        } while (current_depth > ceiling);

        // Check if we ascended all the way to the surface - no deco needed
        if (current_depth <= 0) {
            stops.push_back(stop);
            return stops;
        }

        // First deco stop reached - find number of stops required
        in_deco = true;
        num_stops = current_depth / 3;

        for (i=0; i<num_stops; i++) {
            // Switch to rich gas and get ceiling
            gas = select_rich_gas(gases, current_depth, in_deco);
            ceiling = compartments.get_ceiling();

            // Wait at depth until ceiling increases - time elasped is the stop time
            time = 0;
            while (current_depth == ceiling) {
                wait(&compartments, current_depth, gas, dt);
                ceiling = compartments.get_ceiling();
                time = time + dt;
            }

            // Add deco stop to stop list and ascend to next stop 
            stops.push_back(DecoStop(current_depth, time, gas));
            current_depth = asc2ceil(&compartments, current_depth, gas, in_deco);
        }
        
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

