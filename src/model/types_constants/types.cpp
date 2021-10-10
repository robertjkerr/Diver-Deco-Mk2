/*
Constructor definitions for types
*/

#include "types.h"

namespace DecoModel {
        //******************************************
        // Assign params for dive segment
        //******************************************
        Segment::Segment(int seg_start_depth, float seg_rate, 
                int seg_time, const int* gas_mix)
                : start_depth(seg_start_depth), rate(seg_rate), 
                time(seg_time), gas{gas_mix[0], gas_mix[1]} {}

        
        //******************************************
        // Default constructor - empty segment
        //******************************************
        Segment::Segment() : start_depth(0), rate(0), time(0), gas{0,0} {}


        //******************************************
        // Assign params for deco stop
        //******************************************
        DecoStop::DecoStop(int stop_depth, int stop_time, 
                const int* gas_mix)
                : depth(stop_depth), time(stop_time), gas{gas_mix[0], gas_mix[1]} {}


        //******************************************
        // Default constructor - empty segment
        //******************************************
        DecoStop::DecoStop() : depth(0), time(0), gas{0,0} {}
}