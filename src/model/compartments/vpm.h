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
            void dive_segment_vpm(int time, int start_depth, int depth_rate, float* gas);

            //Bubble ceiling
            int get_ceiling_vpm();

        public:
            //Set constants
            CellVPM(float sample_time, Constants constants);
            
            //Override dive segment wrapper
            void invoke_dive_segment(int time, int start_depth, int depth_rate, float* gas);

            //Override ceiling wrapper
            int get_ceiling();

    };
}

#endif //MODEL_VPM_H