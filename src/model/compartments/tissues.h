/*
Tissues class using Fortran Buhlmann backend
*/

#include "../types_constants/types.h"

namespace DecoModel {
    //******************************************
    // Interface for tissues classes
    //******************************************
    class Tissues {
        protected:
            float otu = 0;

        public:
            virtual void invoke_dive_segment(Segment) {};
            virtual uint16_t get_ceiling() = 0;

            float get_otu() {return otu;}
            void set_otu(float new_otu) {otu = new_otu;}

    };


    //******************************************
    // Class for set of Buhlmann tissues
    //******************************************
    class Buhlmann : public Tissues{
        private:
            float cell_pressures[NUM_INERT_GASES][NUM_COMPARTMENTS];

            float GF;
            float GF_grad;
            const float GFHi;
            const float GFLo;

            void invoke_dive_segment_buhl(float* gas, int16_t start_depth, 
                    int8_t depth_rate, int16_t time);

        public:
            Buhlmann(float GFLo_In, float GFHi_In);

            void invoke_dive_segment(Segment segment) override;
            uint16_t get_ceiling() override;

            void set_GF_grad(uint16_t first_stop_depth);
            void reset_GF(uint16_t depth);

    };

}