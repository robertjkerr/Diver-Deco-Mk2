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

        dt = sample_time;

        compartments = new Tissues(vpm_flag, GFHi, GFLo);

        num_tanks = gases.size();
        for (n = 0; n < num_tanks; n++) {
            tanks.push_back(Tank(breathing_rate, gases[n]));
        }

        

    }


    

    //******************************************
    // Returns the deco stops needed
    //******************************************
    std::vector<DecoStop> Diver::get_deco_stops() {
        std::vector<int[NUM_INERT_GASES]> gases;
        int* gas;

        //Get gases from tanks
        for (Tank tank: tanks) {
            gas = tank.gas;
            gases.push_back(tank.gas);
        }


        //Call deco algorithm function
        return DecoModel::get_deco_stops(*compartments, gases);
    }


}