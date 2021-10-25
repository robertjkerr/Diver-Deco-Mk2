/*
Logic for Varying permeability cell
*/

#include "vpm.h"

namespace DecoModel {
    //******************************************
    // Override dive segment
    //******************************************
    void CellVPM::invoke_dive_segment(uint16_t time, uint16_t start_depth, 
            uint8_t rate, float* gas) {

        dive_segment_buhl(time, start_depth, rate, gas);
        dive_segment_vpm(time, start_depth, rate, gas);
    }


    //******************************************
    // Override ceiling wrapper
    //******************************************
    uint16_t CellVPM::get_ceiling() {
        uint16_t ceiling_buhl, ceiling_vpm;

        ceiling_buhl = get_ceiling_buhl();
        ceiling_vpm = get_ceiling_vpm();

        return std::max(ceiling_buhl, ceiling_vpm);
    }
}