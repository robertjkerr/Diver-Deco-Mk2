/*
Logic for tissues class
*/

#include "tissues.h"

//******************************************
// Initialise compartments
//******************************************
DecoModel::Tissues::Tissues(bool vpm_flag, float GFHiIn, float GFLoIn, 
        float sample_time) : GFHi(GFHiIn), GFLo(GFLoIn), dt(sample_time) {

    int n;
    Cell* compartment;

    for (n = 0; n < NUM_COMPARTMENTS; n++) {
        //Init Buhlmann or VPM compartment
        compartment = vpm_flag == false ? new Cell(dt, Constants(n)) : 
                                        new CellVPM(dt, Constants(n));

        compartments.push_back(compartment);
    }
}


//******************************************
// Gets maximum ceiling of all cells
//******************************************
int DecoModel::Tissues::get_ceiling() {
    int n, this_ceiling;
    std::vector<int> ceilings(NUM_COMPARTMENTS);

    for (n = 0; n < NUM_COMPARTMENTS; n++) {
        this_ceiling = compartments[n]->get_ceiling();
        ceilings[n] = this_ceiling;
    }

    return *max_element(ceilings.begin(), ceilings.end());
}


//******************************************
// Forces all compartments to follow segment
//******************************************
void DecoModel::Tissues::invoke_dive_segment(Segment* segment) {
    int time, start_depth, depth_rate, n;
    std::vector<float> gas(2);

    time = segment->time;
    start_depth = segment->start_depth;
    depth_rate = segment->rate;

    gas[0] = (100 - segment->gas[0] - segment->gas[1]) / 100;
    gas[1] = segment->gas[1] / 100;

    for (n = 0; n < NUM_COMPARTMENTS; n++) {
        compartments[n]->invoke_dive_segment(time, start_depth, depth_rate, gas);
    }
}