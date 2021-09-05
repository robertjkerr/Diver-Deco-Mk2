/*
Header for a VPM tissue compartment
*/

#ifndef MODEL_VPM_H
#define MODEL_VPM_H

#include "../types_constants/types.hpp"
#include "buhlmann.hpp"

namespace DecoModel {
    class CellVPM : public Cell {
        private:

            //*****Methods*****

            //Dive segment - bubble only
            void dive_segment_vpm(int time, int start_depth, int depth_rate);

        public:
            //Set constants
            CellVPM(float sample_time, Constants constants);
            
            //Override dive segment wrapper
            void dive_segment(Segment segment);

    };
}

#endif //MODEL_VPM_H