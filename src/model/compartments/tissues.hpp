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
            std::vector<Cell*>* compartments;

            const float dt;

        public:
            Tissues(bool use_vpm, float GFLoIn, float GFHiIn, float sample_time);



    };
}

#endif //TISSUES_H