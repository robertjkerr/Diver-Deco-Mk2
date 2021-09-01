/*
Logic for gas tracking
*/

#include <vector>

#include "gas_tracking.hpp"
#include "../compartment/buhlmann.hpp"

//******************************************
// Set gas mix of tank
//******************************************
Body::Tank::Tank(std::vector<int> gas_mix) : gas(gas_mix) {};


//******************************************
// Consume gas from tank. Totals consumption
//******************************************
void Body::Tank::use_gas(int depth, int time, int rate) {
    //Time should be in seconds
    int final_depth, ave_pres, p1, p2, gas_used;

    final_depth = rate * time + depth;
    p1 = DEPTH2PRES(depth);
    p2 = DEPTH2PRES(final_depth);

    //Find the average pressure and hence gas volume used
    ave_pres = static_cast<int> ((p1 + p2) / 2);
    gas_used = static_cast<int> (ave_pres * time * Body::breathing_rate / 60);

    vol_gas_used = gas_used;
}

