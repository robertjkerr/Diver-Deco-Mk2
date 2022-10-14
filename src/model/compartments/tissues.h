/*
Tissues class using Fortran Buhlmann backend
*/

#include "../types_constants/types.h"

namespace DecoModel {
    //******************************************
    // Interface for tissues classes
    //******************************************
    class Tissues {

        public:
            virtual void invoke_dive_segment(Segment) {};
            virtual uint16_t get_ceiling() = 0;


    };


    //******************************************
    // Class for set of Buhlmann tissues
    //******************************************
    class Buhlmann : public Tissues{
        private:
            // Partial pressures of dissolved gases. Each row is an inert gas
            //  and each column is the partial pressure for the columnth tissue
            float cell_pressures[NUM_INERT_GASES][NUM_COMPARTMENTS];

            // Gradient factor and its gradient from high to low
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