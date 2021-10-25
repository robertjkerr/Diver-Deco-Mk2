/*
Header for the class for a single Buhlmann tissue compartment
*/

#ifndef MODEL_BUHL_H
#define MODEL_BUHL_H

#include "../types_constants/types.h"

namespace DecoModel {
    class Cell {
        protected:
            //Constants
            const float kN2;
            const float kHe;
            const float AN2;
            const float BN2;
            const float AHe;
            const float BHe;

            //Tissue partial pressure
            float pN2 = RESET_N2;
            float pHe = RESET_HE;

            //Gradient factor params
            float GF;

            //*****Methods*****
            
            //Dive segment - dissolved gas & otu counting
            void dive_segment_buhl(uint16_t time, uint16_t start_depth, 
                int8_t depth_rate, float* gas); //Gas {FN2, FHe}

            //Ceiling - gas only
            uint16_t get_ceiling_buhl();


        public:
            //Constructor sets constants and GF
            Cell(Constants constants, float GFLo);

            //Manually set partial pressures
            void set_partial_pressures(float new_pN2, float new_pHe);

            //Manually set otu
            void set_otu(float new_otu);

            //Invoke dive segment (Wrapper for buhl)
            void invoke_dive_segment(uint16_t time, uint16_t start_depth, 
                int8_t depth_rate, float* gas); //Gas {FN2, FHe}

            //Ceiling wrapper
            uint16_t get_ceiling();

            //Changes gradient factor
            void set_GF(float new_GF);

            //Returns members values
            std::array<float, 3> get_members();

    };
}

#endif //MODEL_BUHL_H