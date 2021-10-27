/*
Tissues class using Fortran Buhlmann backend
*/

#include "../types_constants/types.h"

namespace DecoModel {
    class Tissues {
        protected:
            float cell_pressures[NUM_INERT_GASES][NUM_COMPARTMENTS];

            float GF;
            float GF_grad;
            const float GFHi;
            const float GFLo;

            float otu = 0;

            uint16_t get_ceiling_buhl();
            void invoke_dive_segment_buhl(float* gas, int16_t start_depth, 
                    int8_t depth_rate, int16_t time);

        public:
            Tissues(float GFLo_In, float GFHi_In);

            void invoke_dive_segment(Segment segment);

            uint16_t get_ceiling();

            float get_otu();
            void set_otu(float new_otu);

            void set_GF_grad(uint16_t first_stop_depth);
            void reset_GF(uint16_t depth);

    };
}