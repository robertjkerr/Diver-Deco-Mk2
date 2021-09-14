/*
Diver tracker - executes dive segments on a set of tissues
*/

#include "../algorithm/deco_algorithm.h"

namespace DecoModel {
    class Tracker {
        private:
            const float dt;

            std::vector<int> depth_profile;
            std::vector<int> ceiling_profile;

        public:
            Tracker();

            void construct_profile(std::vector<Segment*> segments); 
    };
}