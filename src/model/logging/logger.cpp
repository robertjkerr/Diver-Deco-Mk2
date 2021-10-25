/*
Methods for logger class
*/

#include "logger.h"
#include "../compartments/tissues.h"

namespace DecoModel {
    Logger::Logger() {}

    //******************************************
    // Logs data for Buhlmann cells
    //******************************************
    void Logger::log_buhl(void* tissues_in) {
        Tissues* tissues = (Tissues*) tissues_in; 

        uint8_t i;
        float pN2, pHe;
        std::array<float, 3> members;
        std::vector<Cell> compartments = tissues->get_compartments();
        
        std::array<float, NUM_COMPARTMENTS> N2s;
        std::array<float, NUM_COMPARTMENTS> Hes;

        for (i = 0; i < NUM_COMPARTMENTS; i++) {
            members = compartments[i].get_members();
            pN2 = members[0];
            pHe = members[1];

            N2s[i] = pN2; Hes[i] = pHe;
        }

        N2_pres_log.push_back(N2s);
        He_pres_log.push_back(Hes);
        otu_log.push_back(tissues->get_otu());
    }
}