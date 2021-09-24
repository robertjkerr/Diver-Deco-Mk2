/*
Logic for gas tracking
*/

#include "gases.h"

//******************************************
// Sets up breathing rate and gas mix
//******************************************
DecoModel::Tank::Tank(int b_rate, std::vector<int> gas_mix) 
        : gas(gas_mix), breathing_rate(b_rate) {}


//******************************************
// Consumes gas based on depth and time
//******************************************
void DecoModel::Tank::breathe(int depth, int time) {
    float pAmb = DEPTH2PRES(depth);
    vol_used = pAmb * breathing_rate;
}