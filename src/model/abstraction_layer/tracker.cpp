/*
Logic for diver tracker
*/

#include "tracker.h"

namespace DecoModel {
    //******************************************
    // Sets up compartments and tanks
    //******************************************
    Diver::Diver(bool vpm_flag, float GFHi, float GFLo, float sample_time,
            std::vector<int*> gases, int breathing_rate) {
        
        int n, num_tanks;

        compartments = new Tissues(vpm_flag, GFHi, GFLo, sample_time);

        num_tanks = gases.size();
        for (n = 0; n < num_tanks; n++) {
            tanks.push_back(Tank(breathing_rate, gases[n]));
        }

        



    }


    //**************************************
    // Returns the deco stops needed
    //**************************************
    std::vector<DecoStop> Diver::get_deco_stops() {
        //Call deco algorithm function
        return DecoModel::get_deco_stops(*compartments);
    }


}