/*
Header for decompression algorithm
*/

#ifndef DECO_ALG_H
#define DECO_ALG_H

#include <vector>

#include "../compartment/tissues.hpp"
#include "../compartment/buhlmann.hpp"
#include "../compartment/vpm.hpp"

#define SHALLOWEST_STOP 6
#define MAX_DECO_ASCENT_RATE -3
#define MAX_ASCENT_RATE -9

namespace Algorithm {
    //Structure for deco stop
    struct DecoStop {
        DecoStop(int stop_depth, int stop_time, std::vector<int> gas_mix) 
            : depth(stop_depth), time(stop_time), gas(gas_mix) {}
        const int depth;
        const int time;
        const std::vector<int> gas;
    };

    //Deco algorithm function
    using decostops = std::vector<DecoStop*>;
    template<class cell>
    decostops get_deco_stops(Body::Tissues<cell> *compartments, float waittime);

}

#endif //DECO_ALG_H