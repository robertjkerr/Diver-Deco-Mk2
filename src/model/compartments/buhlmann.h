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
            
            //Dive segment - gas only
            void dive_segment_buhl(int time, int start_depth, 
                int depth_rate, float* gas); //Gas {FN2, FHe}

            //Ceiling - gas only
            int get_ceiling_buhl();

        public:
            Cell();

            //Constructor sets gas mix and constants
            Cell(Constants constants);

            //Manually set partial pressures
            void set_partial_pressures(float new_pN2, float new_pHe);

            //Invoke dive segment (Wrapper for buhl)
            void invoke_dive_segment(int time, int start_depth, 
                int depth_rate, float* gas); //Gas {FN2, FHe}

            //Ceiling wrapper
            int get_ceiling();

            //Changes gradient factor
            void set_GF(float new_GF);

            //Returns members values
            std::array<float, 3> get_members();

            Cell& operator=(Cell& new_cell);

    };
}

#endif //MODEL_BUHL_H