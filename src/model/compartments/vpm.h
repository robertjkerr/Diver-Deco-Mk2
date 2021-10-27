/*
Header for a VPM tissue compartment
*/

#ifndef MODEL_VPM_H
#define MODEL_VPM_H

#include "tissues.h"

namespace DecoModel {
    class VPMTissues : public Tissues {
        private:

            uint16_t get_ceiling_vpm();
            void invoke_dive_segment_vpm(float* gas, int16_t start_depth, 
                    int8_t depth_rate, int16_t time);

        public:
            VPMTissues(float GFLo_In, float GFHi_In);

            uint16_t get_ceiling();

            void invoke_dive_segment(Segment segment);

    };
}

#endif //MODEL_VPM_H