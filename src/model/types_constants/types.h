/*
Header for various types for the deco model
The defined types abstraction for deco stops etc
*/

#ifndef MODEL_TYPES_H
#define MODEL_TYPES_H

#include <vector>
#include <algorithm>
#include <array>
#include <math.h>

//Some constants
#define SHALLOWEST_STOP 6
#define MAX_ASCENT_RATE -9
#define MAX_DECO_ASCENT_RATE -3
#define METRES_PER_STOP 3
#define SEA_LEVEL_PAMB 1
#define RESET_N2 0.8f
#define RESET_HE 0.0f
#define AIR_PO2 0.21f
#define AIR_PHE 0.0f
#define NUM_COMPARTMENTS 16
#define NUM_INERT_GASES 2
#define MAX_BOTTOM_PO2 1.4f
#define MAX_DECO_PO2 1.6f
#define LOG2 0.693147f

//Macros
#define PRES2DEPTH(pressure) (pressure - 1) * 10
#define DEPTH2PRES(depth) depth / 10 + 1
#define HALFLIVE2K(halflife) LOG2/(halflife*60)
#define SCHREINER(pInit, rate, time, k, pAmbInit) pAmbInit+rate*(time-1/k)-(pAmbInit-pInit-rate/k)*exp(-k*time)
#define ROUNDSTOP(depth) depth - depth % 3 + 3
#define MOD(gas, in_deco) static_cast<int> (DEPTH2PRES(100 * in_deco==true?MAX_DECO_PO2:MAX_BOTTOM_PO2 / gas[0]))
#define OTU(rate, time, pO2Init) (3*time/11)/(pO2Init+rate*time-pO2Init)*(pow((pO2Init+rate*time-0.5f)/0.5f,11/6)-pow((pO2Init-0.5f)/0.5f,11/6))

namespace DecoModel {
    //Type for an arbitrary linear dive segment
    struct Segment {
        //Values mimic the straight line equation. Time is in minutes.
        const int start_depth;
        const float rate;
        const int time;
        const int gas[NUM_INERT_GASES];
        Segment();
        Segment(int seg_start_depth, float seg_rate, int seg_time, const int* gas_mix);
    };

    //Type for a deco stop
    struct DecoStop {
        const int depth;
        const int time;
        const int gas[NUM_INERT_GASES]; //{%O2, %He}
        DecoStop();
        DecoStop(int stop_depth, int stop_time, const int* gas_mix);
    };

    //Structure for the halflives, A and B values for nth cell
    struct Constants {
        const float halflifeN2;
        const float AN2;
        const float BN2;
        const float halflifeHe;
        const float AHe;
        const float BHe;
        const unsigned int cell_index;
        Constants();
        Constants(unsigned int cell_index);
    };
}


#endif //MODEL_TYPES_H