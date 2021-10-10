/*
Logic for tissues class
*/

#include "tissues.h"

namespace DecoModel {
    //******************************************
    // Initialise compartments
    //******************************************
    Tissues::Tissues(bool vpm_flag, float GFHiIn, float GFLoIn) 
        : GFHi(GFHiIn), GFLo(GFLoIn) {

        //Build vector of cells
        for (int n = 0; n < NUM_COMPARTMENTS; n++) {
            //Init Buhlmann or VPM compartment
            compartments.push_back(vpm_flag == false ? 
                Cell(Constants(n)) : Cell(Constants(n)));
        }

    }


    //******************************************
    // Sets the gradient of the GF slope
    //******************************************
    void Tissues::set_GF_grad(int first_stop_depth) {
        float first_ceiling = DEPTH2PRES(first_stop_depth);
        GF_grad = (GFHi - GFLo) / (1 - first_ceiling);
    }


    //******************************************
    // Sets the GF for a given depth
    //******************************************
    void Tissues::reset_GF(int depth) {
        float new_GF, pAmb;
        pAmb = DEPTH2PRES(depth);
        new_GF = GF_grad * (pAmb - 1.3) + GFHi;
        for (Cell cell: compartments)
            cell.set_GF(new_GF);
    }


    //******************************************
    // Gets maximum ceiling of all cells
    //******************************************
    int Tissues::get_ceiling() {
        int n, this_ceiling;
        std::vector<int> ceilings(NUM_COMPARTMENTS);

        for (n = 0; n < NUM_COMPARTMENTS; n++) {
            this_ceiling = compartments[n].get_ceiling();
            ceilings[n] = this_ceiling;
        }

        return *max_element(ceilings.begin(), ceilings.end());
    }


    //******************************************
    // Forces all compartments to follow segment
    //******************************************
    void Tissues::invoke_dive_segment(Segment& segment) {
        int time, start_depth, depth_rate, n;
        float gas[2];

        time = segment.time * 60; //Convert to seconds
        start_depth = segment.start_depth;
        depth_rate = segment.rate;

        gas[0] = static_cast<float> (100 - segment.gas[0] - segment.gas[1]) / 100;
        gas[1] = static_cast<float> (segment.gas[1]) / 100;

        for (n = 0; n < NUM_COMPARTMENTS; n++) {
            compartments[n].invoke_dive_segment(time, start_depth, depth_rate, gas);
        }
    }
}