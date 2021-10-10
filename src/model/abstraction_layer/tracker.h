/*
Diver tracker - executes dive segments on a set of tissues
*/

#include "../algorithm/deco_algorithm.h"
#include "../tracking/gases.h"

namespace DecoModel {
    class Diver {
        private:
            Tissues* compartments;
            std::vector<Tank> tanks;

            void use_gas();

        public:
            Diver(bool vpm_flag, float gfhi, float gflo, float sample_time,
                std::vector<int*> gases, int breathing_rate);

            void invoke_dive_segment(Segment& segment);

            std::vector<DecoStop> get_deco_stops();

    };
}