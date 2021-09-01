/*
Varying Permeability Model definition
*/

#include <iostream>
#include <vector>

#include "vpm.hpp"

using cell = ModelVPM::Cell;

//******************************************
// Set constants
//******************************************
cell::Cell(float dtime, std::vector<float> gas_mix, float AN2In, float BN2, 
        float AHeIn, float BHeIn, float halfLivesN2, float halfLiveHe)
        : AN2(AN2In), BN2(BN2In), AHe(AHeIn), BHe(BHeIn), 
        kN2(HALFLIVE2K(halfLifeN2In)), kHe(HALFLIVE2K(halfLifeHeIn)) {

    in_deco = false;
}


//******************************************
// Wait at depth - gases and bubble
//******************************************
void cell::dive_segment(int time, int depth_rate) {
    dive_segment_buhl(time, depth_rate);
    dive_segment_bubble(time, depth_rate);
    //Set new ambient pressure
    pAmb = pAmb + time * depth_rate / 10;
}


//******************************************
// Change depth - gases and bubble
//******************************************
