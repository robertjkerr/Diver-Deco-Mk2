/*
Logic for tissues class
*/

#include "tissues.h"

namespace DecoModel {
    //******************************************
    // Initialise compartments
    //******************************************
    Tissues::Tissues(bool vpm_flag_in, float GFHiIn, float GFLoIn) 
        : GFHi(GFHiIn), GFLo(GFLoIn) {

        vpm_flag = vpm_flag_in;

        //Build vector of cells
        for (int n = 0; n < NUM_COMPARTMENTS; n++) {
            //Init Buhlmann or VPM compartment
            compartments.push_back(vpm_flag == false ? 
                Cell(Constants(n), GFLo) : Cell(Constants(n), GFLo));
        }

    }


    //******************************************
    // Sets the gradient of the GF slope
    //******************************************
    void Tissues::set_GF_grad(uint16_t first_stop_depth) {
        float first_ceiling = DEPTH2PRES(first_stop_depth);
        GF_grad = (GFHi - GFLo) / (1 - first_ceiling);
    }


    //******************************************
    // Sets the GF for a given depth
    //******************************************
    void Tissues::reset_GF(uint16_t depth) {
        float new_GF, pAmb;
        pAmb = DEPTH2PRES(depth);
        new_GF = GF_grad * (pAmb - 1.3f) + GFHi;
        for (Cell cell: compartments)
            cell.set_GF(new_GF);
    }


    //******************************************
    // Gets maximum ceiling of all cells
    //******************************************
    uint16_t Tissues::get_ceiling() {
        uint8_t n; 
        uint16_t this_ceiling;
        std::vector<uint16_t> ceilings(NUM_COMPARTMENTS);

        for (n = 0; n < NUM_COMPARTMENTS; n++) {
            this_ceiling = compartments[n].get_ceiling();
            ceilings[n] = this_ceiling;
        }

        return *max_element(ceilings.begin(), ceilings.end());
    }


    //******************************************
    // Forces all compartments to follow segment
    //******************************************
    void Tissues::invoke_dive_segment(Segment segment) {
        uint16_t time, start_depth; 
        uint8_t n;
        int8_t depth_rate;
        float gas[2], pO2_rate, pAmb;

        time = segment.time * 60; //Convert to seconds
        start_depth = segment.start_depth;
        depth_rate = segment.rate;

        pO2_rate = depth_rate * (1 - gas[0] - gas[1]) / 10;
        pAmb = DEPTH2PRES(start_depth);

        //Get gas in form of {fN2, fHe}
        gas[0] = static_cast<float> (100 - segment.gas[0] - segment.gas[1]) / 100;
        gas[1] = static_cast<float> (segment.gas[1]) / 100;

        for (n = 0; n < NUM_COMPARTMENTS; n++) {
            compartments[n].invoke_dive_segment(time, start_depth, depth_rate, gas);
        }

        //Increment otu
        otu = otu + OTU(pO2_rate, time, (pAmb * (1 - gas[0] - gas[1])));

        //Log data
        //vpm_flag == false ? logger->log_buhl(this) : logger->log_vpm(this);
        if (log_flag == true) {
            logger->log_buhl(this);
        }
    }

    
    //******************************************
    // Hard sets OTU
    //******************************************
    void Tissues::set_otu(float new_otu) {
        otu = new_otu;
    }


    //******************************************
    // Switches logging on
    //******************************************
    void Tissues::start_logging() {
        log_flag = true;
    }


    //******************************************
    // Switches logging off
    //******************************************
    void Tissues::stop_logging() {
        log_flag = false;
    }
    

    //******************************************
    // Associates logger object to tissues
    //******************************************
    void Tissues::attach_logger(Logger* logger_ptr) {
        logger = logger_ptr;
    }


    //******************************************
    // Returns pointer to the tissues vector
    //******************************************
    std::vector<Cell> Tissues::get_compartments() {
        return compartments;
    }


    //******************************************
    // Returns OTU
    //******************************************
    float Tissues::get_otu() {
        return otu;
    }
}