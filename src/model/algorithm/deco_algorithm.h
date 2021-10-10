/*
Header for deco algorithm methods
*/

#ifndef DECO_ALG_H
#define DECO_ALG_H

#include "../compartments/tissues.h"

namespace DecoModel {
    //Deco stops algorithm function
    std::vector<DecoStop> get_deco_stops(Tissues compartments, int current_depth,
                                    std::vector<int*> gases, float dt);

    //Convert deco stops into an array of dive segments
    std::vector<Segment> deco2seg(int bottom_depth, std::vector<DecoStop>& stops, 
        int* bottom_gas);

}

#endif //DECO_ALG_H