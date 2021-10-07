/*
Logic for diver tracker
*/

#include "tracker.h"

namespace DecoModel {
    //******************************************
    // Sets up compartments and tanks
    //******************************************
    DecoModel::Diver::Diver(bool vpm_flag, float GFHi, float GFLo, float sample_time,
            std::vector<std::vector<int>> gases, int breathing_rate) {
        
        int n, num_tanks;

        compartments = new Tissues(vpm_flag, GFHi, GFLo, sample_time);

        num_tanks = gases.size();
        std::vector<Tank*> tanks(num_tanks);
        for (n = 0; n < num_tanks; n++) {
            tanks[n] = new Tank(breathing_rate, gases[n]);
        }

        



    }


}