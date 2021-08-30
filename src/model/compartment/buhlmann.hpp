/*
Header for a single Buhlmann tissue compartment
*/

#ifndef TISSUE_CLASS_H
#define TISSUE_CLASS_H

#define SEA_LEVEL_PAMB 1
#define RESET_N2 0.8
#define RESET_HE 0
#define AIR_PO2 0.21
#define AIR_PHE 0
#define MAX_DECO_ASCENT_RATE 3
#define MAX_ASCENT_RATE 9

//Pressure/depth conversions
#define PRES2DEPTH(pressure) (pressure + 1) * 10
#define DEPTH2PRES(depth) depth / 10 - 1

//Namespace for the Buhlmann GF model
namespace ModelBuhlmann {
    //Class for tissue compartment
    class BuhlmannCell {
    private:
        //Pressure attributes
        float pAmb = SEA_LEVEL_PAMB; 
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

        //Gradient factor and time delta
        float GF;
        const float dt;

        //Deco status
        static bool in_deco;

        //Gas mix {O2, He}
        float gas[2];        


    public:
        //Constructor sets gas mix
        BuhlmannCell(float dtime, float *gas_mix, float AN2In, float BN2, 
        float AHeIn, float BHeIn, float halfLivesN2, float halfLiveHe);

        //Wait at depth
        void wait(int time);

        //Change depth progressively
        void change_depth(int new_depth, int rate);

        //To be used to set pressures on repetitive dive
        void set_partial_pressures(float new_pN2, float new_pHe);
    };
}

#endif //TISSUE_CLASS_H