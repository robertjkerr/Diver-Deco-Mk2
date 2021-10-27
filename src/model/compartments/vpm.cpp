/*
Logic for Varying permeability cell
*/

#include "vpm.h"

namespace DecoModel {


    uint16_t VPMTissues::get_ceiling() {
        uint16_t buhl_ceil, vpm_ceil;

        buhl_ceil = get_ceiling_buhl();
        vpm_ceil = get_ceiling_buhl();

        return std::max(buhl_ceil, vpm_ceil);
    } 


    void VPMTissues::invoke_dive_segment(Segment segment) {
        float gas[NUM_INERT_GASES];
        int16_t start_depth, time;
        int8_t depth_rate;

        gas[0] = static_cast<float> (100 - segment.gas[0] - segment.gas[1]) / 100;
        gas[1] = static_cast<float> (segment.gas[1]) / 100;

        start_depth = static_cast<int16_t> (segment.start_depth);
        depth_rate = static_cast<int8_t> (segment.rate);
        time = static_cast<int16_t> (segment.time);

        invoke_dive_segment_buhl(gas, start_depth, depth_rate, time);
        invoke_dive_segment_vpm(gas, start_depth, depth_rate, time);
    }
    
}