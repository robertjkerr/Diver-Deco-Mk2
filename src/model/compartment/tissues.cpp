/*
Logic for controlling a set of all tissue compartments
*/

#include <iostream>
#include <vector>
#include <algorithm>

#include "tissues.hpp"
#include "constants.hpp"

//******************************************
// Inits all tissue compartments
//******************************************
template<class cell>
Body::Tissues<cell>::Tissues(float GFLoIn, float GFHiIn, 
        float *gas_mix, float dtime) 
        : GFHi(GFHiIn), GFLo(GFLoIn), gas(gas_mix) {
    int n;
    Constants constants;
    cell tissue;

    //Create new objects in the heap
    for (n = 0; n < NUM_COMPARTMENTS; n++) {
        constants = Constants(n);
        tissue = new cell(dtime, gas_mix, constants.AN2,
                                            constants.BN2,
                                            constants.AHe,
                                            constants.BHe,
                                            constants.halfLifeN2,
                                            constants.halfLifeHe);
        compartments.push_back(&tissue); 
    }
}


//******************************************
// Waits all compartments
//******************************************
template<class cell>
void Body::Tissues<cell>::wait(int time) {
    //Simply go through all cells and make them wait at depth
    for(int n = 0; n < NUM_COMPARTMENTS; n++) {
        compartments[n]->wait(time);
    }
}


//******************************************
// Change depth
//******************************************
template<class cell>
void Body::Tissues<cell>::change_depth(int new_depth, int rate) {
    int max_rate;

    //Select maximum ascent rate
    if (in_deco == true) {
        max_rate = MAX_DECO_ASCENT_RATE; 
    }
    else {
        max_rate = MAX_ASCENT_RATE; 
    }

    //Clamp depth change rate
    rate = std::min(rate, max_rate);

    //Simply go through all cells and change their depths
    for (int n = 0; n < NUM_COMPARTMENTS; n++) {
        compartments[n]->change_depth(new_depth, rate);
    }
}


//******************************************
// Set all cell pressures for repeat dives
//******************************************
template<class cell>
void Body::Tissues<cell>::set_partial_pressures(
        std::vector<float> new_pN2s, std::vector<float> new_pHes) {
    int n, pN2, pHe;
    //Set the inert gas pps in each compartment
    for (n = 0; n < NUM_COMPARTMENTS; n++) {
        pN2 = new_pN2s[n];
        pHe = new_pHes[n];
        compartments[n]->pN2 = pN2;
        compartments[n]->pHe = pHe;
    }
}


//******************************************
// Gets the real ceiling of the system
//******************************************
template<class cell>
int Body::Tissues<cell>::get_ceiling() {
    int ceiling = 0, n, next_ceiling;
    //Go through each cell and find the highest ceiling
    for (n = 0; n < NUM_COMPARTMENTS; n++) {
        next_ceiling = compartments[n]->get_ceiling();
        //Check and increase ceiling
        if (next_ceiling > ceiling) {
            ceiling = next_ceiling;
        }
    }

    return ceiling;
}


//******************************************
// Gets the depth of the first stop
//******************************************
template<class cell>
int Body::Tissues<cell>::get_next_stop() {
    int ceiling, remainder, stop_depth;

    //Get real ceiling and find its remainder against 3
    ceiling = get_ceiling();
    remainder = ceiling % 3;

    //If ceiling is not multiple of 3 round up
    if (remainder == 0) {
        stop_depth = ceiling;
    }
    else {
        stop_depth = ceiling - remainder + 3;
    }

    return stop_depth;
}



