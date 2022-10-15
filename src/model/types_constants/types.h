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
#include <stdint.h>

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

//Macros
#define PRES2DEPTH(pressure) (pressure - 1) * 10
#define DEPTH2PRES(depth) static_cast<float> (depth) / 10 + 1
#define ROUNDSTOP(depth) depth - depth % 3 + 3
#define MOD(gas, in_deco) static_cast<uint16_t> (DEPTH2PRES(100 * in_deco==true?MAX_DECO_PO2:MAX_BOTTOM_PO2 / gas[0]))

namespace DecoModel {
    //Type for an arbitrary linear dive segment
    struct Segment {
        //Values mimic the straight line equation. Time is in minutes.
        const uint16_t start_depth;
        const int8_t rate;
        const uint16_t time;
        const uint8_t gas[NUM_INERT_GASES];
        // Input gas mix is {%O2, %He}
        Segment(uint16_t seg_start_depth, int8_t seg_rate, uint16_t seg_time, const uint8_t* gas_mix);
    };

    //Type for a deco stop
    struct DecoStop {
        // Time is in minutes
        const uint16_t depth;
        const uint16_t time;
        const uint8_t gas[NUM_INERT_GASES]; //{%O2, %He}
        DecoStop(uint16_t stop_depth, uint16_t stop_time, const uint8_t* gas_mix);
    };

}

#endif //MODEL_TYPES_H