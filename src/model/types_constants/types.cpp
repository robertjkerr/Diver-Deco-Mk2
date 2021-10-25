/*
Constructor definitions for types
*/

#include "types.h"

namespace DecoModel {
        //******************************************
        // Assign params for dive segment
        //******************************************
        Segment::Segment(uint16_t seg_start_depth, int8_t seg_rate, 
                uint16_t seg_time, const uint8_t* gas_mix)
                : start_depth(seg_start_depth), rate(seg_rate), 
                time(seg_time), gas{gas_mix[0], gas_mix[1]} {}


        //******************************************
        // Assign params for deco stop
        //******************************************
        DecoStop::DecoStop(uint16_t stop_depth, uint16_t stop_time, 
                const uint8_t* gas_mix)
                : depth(stop_depth), time(stop_time), gas{gas_mix[0], gas_mix[1]} {}

}