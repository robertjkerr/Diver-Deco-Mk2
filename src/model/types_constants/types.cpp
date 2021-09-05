/*
Constructor definitions for types
*/

#include "types.hpp"

//******************************************
// Assign params for dive segment
//******************************************
DecoModel::Segment::Segment(int seg_start_depth, float seg_rate, 
        int seg_time, std::vector<int> gas_mix)
        : start_depth(seg_start_depth), rate(seg_rate), 
        time(seg_time), gas(gas_mix) {}


//******************************************
// Assign params for deco stop
//******************************************
DecoModel::DecoStop::DecoStop(int stop_depth, int stop_time, 
        std::vector<int> gas_mix)
        : depth(stop_depth), time(stop_time), gas(gas_mix) {}