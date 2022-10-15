/*
Header for deco algorithm methods
*/

#ifndef DECO_ALG_H
#define DECO_ALG_H

#include "../compartments/tissues.h"

namespace DecoModel {
    //Deco stops algorithm function
    std::vector<DecoStop> get_deco_stops(Buhlmann compartments, uint16_t current_depth,
                                    std::vector<uint8_t*> gases, uint8_t dt);

    //Convert deco stops into an array of dive segments
    //std::vector<Segment> deco2seg(uint8_t bottom_depth, std::vector<DecoStop>& stops, 
     //   uint8_t* bottom_gas);

}

#endif //DECO_ALG_H