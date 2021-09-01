/*
Logic for decompression algorithm
*/

#include <vector>

#include "deco_algorithm.hpp"
#include "../tracking/segments.hpp"

using DecoStop = Algorithm::DecoStop;
using decostops = std::vector<DecoStop*>;
using segment = Planner::BottomSegment;

//******************************************
// Deco algorithm function
//******************************************
template<class cell>
decostops Algorithm::get_deco_stops(Body::Tissues<cell> *compartments, const float waittime) {
    const int num_stops;
    int n, stop_depth, this_stop_depth;
    float time;
    DecoStop *stop;
    std::vector<int> gas;

    //Ascend to first stop and make sure at ceiling to account for offgassing while ascending
    for (n = 0; n < 2; n++) {
        go_to_next_stop(compartments);
    }

    //Set deco flags
    compartments->in_deco = true;
    compartments->first_stop = true;

    //Find number of deco stops and init output vector
    num_stops = get_num_deco_stops(compartments);
    decostops deco_stops(num_stops);

    //Find stop time for each stop
    for (n = 0; n < num_stops; n++) {
        this_stop_depth = compartments->get_next_stop();
        stop_depth = this_stop_depth;
        time = 0;

        //Wait until ceiling changes
        while (stop_depth == this_stop_depth) {
            compartments->wait(waittime);
            time = time + waittime;
        }

        //Create deco stop object and add to vector
        gas = compartments->get_gas_mix();
        stop = new DecoStop(this_stop_depth, time, gas);
        deco_stops[n] = stop;

        //Go to the next stop
        compartments->first_stop = false;
        go_to_next_stop(compartments);
    }

    return deco_stops;
}


//******************************************
// Ascends to next stop
//******************************************
template<class cell>
static void go_to_next_stop(Body::Tissues<cell> *compartments) {
    int stop_depth, time, this_depth, rate;
    std::vector<int> gas;
    segment ascent_segment;
    std::vector<segment> profile(1);

    stop_depth = compartments->get_next_stop();
    this_depth = compartments->get_depth();
    gas = compartments->get_gas_mix();

    if (compartments->in_deco == true) {
        rate = MAX_DECO_ASCENT_RATE;
    }    
    else {
        rate = MAX_ASCENT_RATE;
    }

    time = std::abs((stop_depth - this_depth) / rate);
    ascent_segment = segment(time, this_depth, stop_depth, gas);
    profile[0] = ascent_segment; 

    Planner::invoke_profile(compartments, profile);
}


//******************************************
// Get number of deco stops
//******************************************
template<class cell>
static int get_num_deco_stops(Body::Tissues<cell> *compartments) {
    int num_stops, ceiling;

    //Find num of multiples of 3 between first and last stop
    ceiling = compartments->get_next_stop();
    num_stops = static_cast<int> ((ceiling - SHALLOWEST_STOP) / 3) + 1;

    return num_stops;
}