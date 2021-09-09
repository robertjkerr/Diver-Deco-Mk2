/*
Header for various types for the deco model
The defined types abstraction for deco stops etc
*/

#ifndef MODEL_TYPES_H
#define MODEL_TYPES_H

#include <vector>
#include <algorithm>
#include <math.h>

//Some constants
#define SHALLOWEST_STOP 6
#define MAX_ASCENT_RATE -9
#define MAX_DECO_ASCENT_RATE -3
#define METRES_PER_STOP 3
#define SEA_LEVEL_PAMB 1
#define RESET_N2 0.8
#define RESET_HE 0
#define AIR_PO2 0.21
#define AIR_PHE 0
#define NUM_COMPARTMENTS 16
#define LOG2 0.693147

//*****Macros*****

//Pressure/depth and halflife/k value conversions
#define PRES2DEPTH(pressure) (pressure + 1) * 10
#define DEPTH2PRES(depth) depth / 10 - 1
#define HALFLIVE2K(halflife) LOG2/(halflife*60)

//Schreiner equation
#define SCHREINER(pInit, rate, time, k, pAmbInit) pAmbInit+rate*(time-1/k)-(pAmbInit-pInit-rate/k)*exp(-k*time)

//Round to multiple of 3
#define ROUNDSTOP(depth) depth - depth % 3 + 3

//**********

namespace DecoModel {
    //Type for an arbitrary linear dive segment
    struct Segment {
        //Values mimic the straight line equation
        const int start_depth;
        const float rate;
        const int time;
        const std::vector<int> gas;
        Segment(int seg_start_depth, float seg_rate, int seg_time, std::vector<int> gas_mix);
    };

    //Type for a deco stop
    struct DecoStop {
        const int depth;
        const int time;
        const std::vector<int> gas; //{%O2, %He}
        DecoStop(int stop_depth, int stop_time, std::vector<int> gas_mix);
    };

    //Structure for the halflives, A and B values for nth cell
    struct Constants {
        const float halflifeN2;
        const float AN2;
        const float BN2;
        const float halflifeHe;
        const float AHe;
        const float BHe;
        Constants(int cell_index);
    };
}


#endif //MODEL_TYPES_H