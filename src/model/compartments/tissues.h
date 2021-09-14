/*
Header for type for all compartments
*/

#ifndef TISSUES_H
#define TISSUES_H

#include "../types_constants/types.h"
#include "vpm.h"

namespace DecoModel {
    class Tissues {
        private:
            std::vector<Cell> compartments;

            const float dt;

            const float GFHi;
            const float GFLo;
            float GF_grad;

            void set_GF_grad(int first_stop_depth);
            void reset_GF(int depth);

        public:
            Tissues(bool vpm_flag, float GFLoIn, float GFHiIn, float sample_time);

            int get_ceiling();

            void invoke_dive_segment(Segment* segment);

    };
}

#endif //TISSUES_H