/*
Tissues class using Fortran Buhlmann backend
*/

#include "../types_constants/types.h"

namespace DecoModel {
    class Tissues {
        private:
            float cell_pressures[NUM_INERT_GASES][NUM_COMPARTMENTS];

            float GF;
            const float GFHi;
            const float GFLo;

            uint16_t get_ceiling_buhl();
            void invoke_dive_segment_buhl(Segment segment);

        public:
            Tissues(bool vpm_flag, float GFLo_In, float GFHi_In);

            void invoke_dive_segment(Segment segment);

            uint16_t get_ceiling();

    };
}