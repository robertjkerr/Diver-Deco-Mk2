/*
Header for halflives, A and B constants
*/

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <vector>

struct Constants {
    Constants(int cell_index);
    const float AN2;
    const float BN2;
    const float AHe;
    const float BHe;
    const float halfLifeN2;
    const float halfLifeHe;
};

#endif //CONSTANTS_H