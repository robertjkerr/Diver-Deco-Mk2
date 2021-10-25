/*
Constructor and values of constants
*/

#include "types.h"

namespace DecoModel {
    //Arrays with all the constants options
    static const float halfLivesN2[] = {4, 8, 12, 18, 27, 38, 54, 77, 109, 146, 187, 239, 305, 390, 498, 635};
    static const float AValsN2[] = {1.23, 1, 0.86, 0.76, 0.62, 0.5, 0.44, 0.4, 0.38, 0.35, 0.33, 0.31, 0.28, 0.26, 0.25, 0.23};
    static const float BValsN2[] = {0.51, 0.65, 0.72, 0.78, 0.81, 0.84, 0.87, 0.89, 0.9, 0.92, 0.93, 0.94, 0.94, 0.95, 0.96, 0.97};
    static const float halfLivesHe[] = {1.51, 3.02, 4.72, 6.99, 10.21, 14.48, 20.53, 29.11, 41.20, 55.19, 70.69, 90.34, 115.29, 147.42, 188.24, 240.03};
    static const float AValsHe[] = {1.74, 1.38, 1.19, 1.05, 0.92, 0.82, 0.73, 0.65, 0.6, 0.55, 0.53, 0.52, 0.52, 0.52, 0.52, 0.51};
    static const float BValsHe[] = {0.42, 0.57, 0.65, 0.72, 0.76, 0.8, 0.83, 0.86, 0.88, 0.89, 0.9, 0.91, 0.91, 0.92, 0.92, 0.93};


    //******************************************
    // Choose constants based on compartment
    //******************************************
    Constants::Constants(uint8_t index) 
            : halflifeN2(halfLivesN2[index]), AN2(AValsN2[index]),
            BN2(BValsN2[index]), halflifeHe(halfLivesHe[index]),
            AHe(AValsHe[index]), BHe(BValsHe[index]), cell_index(index) {}
}