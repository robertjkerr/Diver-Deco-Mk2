/*
Header for a VPM tissue compartment
*/

#ifndef MODEL_VPM_H
#define MODEL_VPM_H

#include "../types_constants/types.h"
#include "buhlmann.h"

namespace DecoModel {
    class CellVPM : public Cell {
        private:

            //*****Methods*****

            //Dive segment - bubble only
            void dive_segment_vpm(uint16_t time, uint16_t start_depth, int depth_rate, float* gas);

            //Bubble ceiling
            uint16_t get_ceiling_vpm();

        public:
            //Set constants
            CellVPM(Constants constants, float GFLo);

            //Override dive segment function
            void invoke_dive_segment(uint16_t time, uint16_t start_depth, uint8_t rate, float* gas);

            //Override ceiling function
            uint16_t get_ceiling();
            
    };
}

#endif //MODEL_VPM_H