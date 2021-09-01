/*
Dive segments logic
*/

#include <vector>

#include "segments.hpp"

//******************************************
// Set attributes
//******************************************
Planner::BottomSegment::BottomSegment(int timeIn, int start_depthIn, int end_depthIn, std::vector<int> gasIn)
    : time(timeIn), start_depth(start_depthIn), end_depth(end_depthIn), gas(gasIn) {};


//******************************************
// Bottom segment ascent/descent rate 
//******************************************
float Planner::BottomSegment::rate() {
    int diff;
    float change_rate;

    //Calculate rate
    diff = end_depth - start_depth;
    change_rate = diff / time;
    return change_rate;
}


//******************************************
// Invokes a set of bottom segments on body
//******************************************
template<class cell>
void Planner::invoke_profile(Body::Tissues<cell> *compartments, std::vector<Planner::BottomSegment*> *dive_profile) {
    int num_segments, n, time;
    float seg_rate;

    //Run dive segment on all tissues
    num_segments = dive_profile->size();
    for (n = 0; n < num_segments; n++) {
        seg_rate = dive_profile[n]->rate();
        time = dive_profile[n]->time;
        compartments->dive_segment(time, seg_rate);
    }
}