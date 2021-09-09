/*
Header for type for all compartments
*/

#ifndef TISSUES_H
#define TISSUES_H

#include "../types_constants/types.hpp"
#include "vpm.hpp"

namespace DecoModel {
    class Tissues {
        private:
            std::vector<Cell*> compartments;

            const float dt;

            const float GFHi;
            const float GFLo;

        public:
            Tissues(bool vpm_flag, float GFLoIn, float GFHiIn, float sample_time);

            int get_ceiling();

            void invoke_dive_segment(Segment* segment);

    };
}

#endif //TISSUES_H