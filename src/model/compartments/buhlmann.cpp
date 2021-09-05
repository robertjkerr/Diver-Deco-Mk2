/*
Logic for a Buhlmann tissue compartment
*/

#include "buhlmann.hpp"



//******************************************
// Invokes a dive segment on dissolved gases
//******************************************
void DecoModel::Cell::dive_segment_buhl(int time, int start_depth, 
        int rate, std::vector<float> gas) {

    float pAmb, pN2_rate, pHe_rate;

    pAmb = DEPTH2PRES(start_depth);
    pN2_rate = rate * gas[0] / 10;
    pHe_rate = rate * gas[1] / 10;

    pN2 = SCHREINER(pN2, pN2_rate, time, kN2, pAmb * gas[0]);
    pHe = SCHREINER(pHe, pHe_rate, time, kHe, pAmb * gas[1]);
}