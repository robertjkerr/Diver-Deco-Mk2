/*
Logic of a tissue compartment
*/

#include <iostream>
#include <math.h>

#include "buhlmann.hpp"

#define LOG2 0.693147
#define HALFLIVE2K(halflife) LOG2/(halflife*60)

using cell = ModelBuhlmann::BuhlmannCell;


//******************************************
// Set constants
//******************************************
cell::BuhlmannCell(float dtime, float *gas_mix, float AN2In, float BN2In, 
        float AHeIn, float BHeIn, float halfLifeN2In, float halfLifeHeIn) 
        : dt(dtime), AN2(AN2In), BN2(BN2In), AHe(AHeIn), BHe(BHeIn), 
        kN2(HALFLIVE2K(halfLifeN2In)), kHe(HALFLIVE2K(halfLifeHeIn)) {

    gas[0] = gas_mix[0];
    gas[1] = gas_mix[1];
    in_deco = false;
}


//******************************************
// Wait at constant depth
//******************************************
void cell::wait(int time) {
    float pN2Amb, pHeAmb;

    //Get the ambient partial pressures
    pN2Amb = gas[0] * pAmb;
    pHeAmb = gas[1] * pAmb;

    //Schreiner equation with no change in depth
    pN2 = pN2 - (pN2Amb - pN2) * (1 - exp(-kN2 * time)); 
    pHe = pHe - (pHeAmb - pHe) * (1 - exp(-kHe * time));
}


//******************************************
// Change depth at a fixed rate
//******************************************
void cell::change_depth(int new_depth, int rate) {
    float pN2Amb, pHeAmb, ascent_time;
    int depth;

    //Get the ambient partial pressures
    pN2Amb = gas[0] * pAmb;
    pHeAmb = gas[1] * pAmb;

    //Find the amount of time spent ascending
    ascent_time = (new_depth - PRES2DEPTH(pAmb)) / rate;

    //Schreiner equation
    pN2 = pN2Amb + rate * (ascent_time - 1 / kN2) - 
        (pN2Amb - pN2 - rate / kN2) * exp(-kN2 * ascent_time);
    pHe = pHeAmb + rate * (ascent_time - 1 / kHe) - 
    (pHeAmb - pHe - rate / kHe) * exp(-kHe * ascent_time);

    pAmb = DEPTH2PRES(new_depth); 
}


//******************************************
// Set tissue pressures for a repeat dive
//******************************************
void cell::set_partial_pressures(float new_pN2, float new_pHe) {
    pN2 = new_pN2;
    pHe = new_pHe;
}

