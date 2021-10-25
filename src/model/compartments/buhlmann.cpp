/*
Logic for a Buhlmann tissue compartment
*/

#include "buhlmann.h"

namespace DecoModel {
    //******************************************
    // Constructor sets constants
    //******************************************
    Cell::Cell(Constants constants, float GFLo)
            : kN2(HALFLIVE2K(constants.halflifeN2)), kHe(HALFLIVE2K(constants.halflifeHe)),
            AN2(constants.AN2), BN2(constants.BN2), 
            AHe(constants.AHe), BHe(constants.BHe) {

        GF = GFLo;
    }


    //******************************************
    // Sets new partial pressures
    //******************************************
    void Cell::set_partial_pressures(float new_pN2, float new_pHe) {
        pN2 = new_pN2;
        pHe = new_pHe;
    }


    //******************************************
    // Invokes a dive segment on dissolved gases
    //******************************************
    void Cell::dive_segment_buhl(int time, int start_depth, 
            int rate, float* gas) {

        float pAmb, pN2_rate, pHe_rate, pO2_rate;

        //Unit conversions
        pAmb = DEPTH2PRES(start_depth);
        pN2_rate = rate * gas[0] / 10;
        pHe_rate = rate * gas[1] / 10;
        

        //Increment tissue partial pressures
        pN2 = SCHREINER(pN2, pN2_rate, time, kN2, (pAmb * gas[0]));
        pHe = SCHREINER(pHe, pHe_rate, time, kHe, (pAmb * gas[1]));

    }


    //******************************************
    // Invoke dive segment
    //******************************************
    void Cell::invoke_dive_segment(int time, int start_depth, 
            int rate, float* gas) {

        dive_segment_buhl(time, start_depth, rate, gas);
    }


    //******************************************
    // Ceiling calculation wrapper
    //******************************************
    int Cell::get_ceiling() {
        return get_ceiling_buhl();
    }


    //******************************************
    // Gets ceiling - dissolved gas
    //******************************************
    int Cell::get_ceiling_buhl() {
        float A, B, p_ceiling; 
        int ceiling;

        A = ((AN2 * pN2) + (AHe * pHe)) / (pN2 + pHe);
        B = ((BN2 * pN2) + (BHe * pHe)) / (pN2 + pHe);
        p_ceiling = ((pN2 + pHe) - GF * A) * B / (B + GF * (1 - B));

        ceiling = static_cast<int> PRES2DEPTH(p_ceiling);
        return ceiling;
    }



    //******************************************
    // Sets the gradient factor
    //******************************************
    void Cell::set_GF(float new_GF) {
        GF = new_GF;
    }


    //******************************************
    // Returns the members of the object
    //******************************************
    std::array<float, 3> Cell::get_members() {
        std::array<float, 3> out = {pN2, pHe, GF};
        return out;
    }


}