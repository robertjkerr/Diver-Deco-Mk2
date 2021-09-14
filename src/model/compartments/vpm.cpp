/*
Logic for Varying permeability cell
*/

#include "vpm.h"

//******************************************
// Override dive segment
//******************************************
void DecoModel::CellVPM::invoke_dive_segment(int time, int start_depth, 
        int rate, std::vector<float> gas) {

    dive_segment_buhl(time, start_depth, rate, gas);
    dive_segment_vpm(time, start_depth, rate, gas);
}


//******************************************
// Override ceiling wrapper
//******************************************
int DecoModel::CellVPM::get_ceiling() {
    int ceiling_buhl, ceiling_vpm;

    ceiling_buhl = get_ceiling_buhl();
    ceiling_vpm = get_ceiling_vpm();

    return std::max(ceiling_buhl, ceiling_vpm);
}