/*
Header for a single Buhlmann tissue compartment
*/

#ifndef TISSUE_CLASS_H
#define TISSUE_CLASS_H

#include <vector>

#define SEA_LEVEL_PAMB 1
#define RESET_N2 0.8
#define RESET_HE 0
#define AIR_PO2 0.21
#define AIR_PHE 0

//Pressure/depth conversions
#define PRES2DEPTH(pressure) (pressure + 1) * 10
#define DEPTH2PRES(depth) depth / 10 - 1

//Namespace for the Buhlmann GF model
namespace ModelBuhlmann {
    //Class for tissue compartment
    class Cell {
    protected:
        //Tissue partial pressures
        float pN2 = RESET_N2; 
        float pHe = RESET_HE;

        //Half live constants
        const float kN2;
        const float kHe;

        //Inert gas A and B values
        const float AN2;
        const float BN2;
        const float AHe;
        const float BHe;

        //Gradient factor
        float GF;

        //Ambient pressure
        float pAmb = SEA_LEVEL_PAMB; 
        
        //Deco status
        static bool in_deco;

        //Gas mix {O2, He}
        static std::vector<float> gas;

        //Dive segment - gas only
        void dive_segment_buhl(int time, int depth_rate);


    public:
        //Constructor sets gas mix and constants
        Cell(float dtime, std::vector<float> gas_mix, float AN2In, float BN2, 
            float AHeIn, float BHeIn, float halfLivesN2, float halfLiveHe);

        //To be used to set pressures on repetitive dive
        void set_partial_pressures(float new_pN2, float new_pHe);

        //Wrapper for dive segment
        void dive_segment(int time, int depth_rate);

        //Switch class gas
        static void switch_gas(std::vector<int> new_gas);

    };
}

#endif //TISSUE_CLASS_H