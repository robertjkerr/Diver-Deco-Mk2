/*
Varying Permeability Model extension to Buhlmann model
*/

#ifndef VPM_H
#define VPM_H

#include <vector>

#include "buhlmann.hpp"

//Namespace for VPM model
namespace ModelVPM {
    //The VPM is an extension of the Buhlann model so inheritance can be used
    class Cell : public ModelBuhlmann::Cell {
    private:

        //Dive segment for bubble only
        void dive_segment_bubble(int time, int depth_rate);

    public:
        //Constructor sets gas mix and constants - override
        Cell(float dtime, std::vector<float> gas_mix, float AN2In, float BN2, 
            float AHeIn, float BHeIn, float halfLivesN2, float halfLiveHe);

        //Dive segment for both gas and the bubble
        void dive_segment(int time, int depth_rate);

    };
}

#endif //VPM_H