/*
Deco algorithm logic
*/

#include "deco_algorithm.h"

using Segment = DecoModel::Segment;
using DecoStop = DecoModel::DecoStop;
using Tissues = DecoModel::Tissues;

//******************************************
// Deco stops algorithm
//******************************************
std::vector<DecoStop> get_deco_stops(Tissues compartments) {
    //Note that compartments and all the properties of it are in the stack
    // so the object is essentially copied
    float time;
    int num_stops, stop_depth;
    std::vector<DecoStop> deco_stops;





    return deco_stops;
}


//******************************************
// Turn a single deco stop into a segment
//******************************************
static Segment stop2seg(DecoStop* stop) {
    return Segment(stop->depth, 0, stop->time, stop->gas);
}


//******************************************
// Create ascent segment
//******************************************
static Segment asc_seg(int depth1, int depth2, std::vector<int> gas, bool in_deco) {
    int rate, time;

    //Pick ascent rate
    rate = in_deco == true ? MAX_DECO_ASCENT_RATE : MAX_ASCENT_RATE;

    //Find time and create segment
    time = static_cast<int> ((depth2 - depth1) / rate);
    return Segment(depth1, rate, time, gas);
}


//******************************************
// Turn deco stops to dive segments
//******************************************
std::vector<Segment> DecoModel::deco2seg(int bottom_depth,
    std::vector<DecoStop*> stops, std::vector<int> bottom_gas) {

    int depth, next_depth, stop_num;
    std::vector<Segment> segments;
    DecoStop* stop;

    next_depth = stops[0]->depth; 

    //Ascent from bottom to first stop
    segments.push_back(asc_seg(next_depth, bottom_depth, bottom_gas, false));

    //Deco stops and ascents
    for (stop_num = 0; stop_num < stops.size(); stop_num++) {
        stop = stops[stop_num];
        segments.push_back(stop2seg(stop));

        depth = stop->depth;

        //Get next stop depth
        next_depth = depth == SHALLOWEST_STOP ? next_depth = 0
                        : next_depth = stops[stop_num + 1]->depth;

        //Append ascent to next stop
        segments.push_back(asc_seg(depth, next_depth, stop->gas, true));
    } 

    return segments;
}


