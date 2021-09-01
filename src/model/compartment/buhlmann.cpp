/*
Logic of a tissue compartment
*/

#include <vector>
#include <math.h>

#include "buhlmann.hpp"

#define LOG2 0.693147
#define HALFLIVE2K(halflife) LOG2/(halflife*60)

using cell = ModelBuhlmann::Cell;

//******************************************
// Set constants
//******************************************
cell::Cell(float dtime, std::vector<float> gas_mix, float AN2In, float BN2In, 
        float AHeIn, float BHeIn, float halfLifeN2In, float halfLifeHeIn) 
        : AN2(AN2In), BN2(BN2In), AHe(AHeIn), BHe(BHeIn), 
        kN2(HALFLIVE2K(halfLifeN2In)), kHe(HALFLIVE2K(halfLifeHeIn)) {

    in_deco = false;
}


//*******************************************
// Logic for a linear dive segment
//*******************************************
void cell::dive_segment(int time, int depth_rate) {
    dive_segment_buhl(time, depth_rate);
    //Set new ambient pressure
    pAmb = pAmb + time * depth_rate / 10;
}

//*******************************************
// Logic for a dive segment - gas only
//******************************************I
void cell::dive_segment_buhl(int time, int depth_rate) {
    float pN2Amb, pHeAmb, rate;

    //Get the ambient partial pressures
    pN2Amb = gas[0] * pAmb;
    pHeAmb = gas[1] * pAmb;

    //Get pressure ascent/descent rate
    rate = depth_rate / 10;

    //Schreiner equation
    pN2 = pN2Amb + rate * (time - 1 / kN2) - 
        (pN2Amb - pN2 - rate / kN2) * exp(-kN2 * time);
    pHe = pHeAmb + rate * (time - 1 / kHe) - 
    (pHeAmb - pHe - rate / kHe) * exp(-kHe * time);
}


//******************************************
// Set tissue pressures for a repeat dive
//******************************************
void cell::set_partial_pressures(float new_pN2, float new_pHe) {
    pN2 = new_pN2;
    pHe = new_pHe;
}


//******************************************
// Switch breathing gas
//******************************************
void cell::switch_gas(std::vector<int> new_gas) {
    gas[0] = 1 - (new_gas[0] + new_gas[1]) / 100;
    gas[1] = new_gas[1] / 100;
}

