/*
Logic for a Buhlmann tissue compartment
*/

#include "buhlmann.hpp"

//******************************************
// Constructor sets constants
//******************************************
DecoModel::Cell::Cell(float sample_time, Constants constants)
        : kN2(HALFLIVE2K(constants.halflifeN2)), kHe(HALFLIVE2K(constants.halflifeHe)),
        AN2(constants.AN2), BN2(constants.BN2), 
        AHe(constants.AHe), BHe(constants.BHe), dt(sample_time) {};


//******************************************
// Invokes a dive segment on dissolved gases
//******************************************
void DecoModel::Cell::dive_segment_buhl(int time, int start_depth, 
        int rate, std::vector<float> gas) {

    float pAmb, pN2_rate, pHe_rate;

    pAmb = DEPTH2PRES(start_depth);
    pN2_rate = rate * gas[0] / 10;
    pHe_rate = rate * gas[1] / 10;

    pN2 = SCHREINER(pN2, pN2_rate, time, kN2, pAmb * gas[0]);
    pHe = SCHREINER(pHe, pHe_rate, time, kHe, pAmb * gas[1]);
}


//******************************************
// Invoke dive segment
//******************************************
void DecoModel::Cell::invoke_dive_segment(int time, int start_depth, 
        int rate, std::vector<float> gas) {

    dive_segment_buhl(time, start_depth, rate, gas);
}


//******************************************
// Ceiling calculation wrapper
//******************************************
int DecoModel::Cell::get_ceiling() {
    return get_ceiling_buhl();
}


//******************************************
// Gets ceiling - dissolved gas
//******************************************
int DecoModel::Cell::get_ceiling_buhl() {
    float A, B, p_ceiling; 
    int ceiling;

    A = ((AN2 * pN2) + (AHe * pHe)) / (pN2 + pHe);
	B = ((BN2 * pN2) + (BHe * pHe)) / (pN2 + pHe);
	p_ceiling = ((pN2 + pHe) - GF * A) * B / (B + GF * (1 - B));

    ceiling = static_cast<int> (PRES2DEPTH(p_ceiling));
    return ceiling;
}
