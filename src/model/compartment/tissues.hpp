/*
Header for tissues class which represents a body
*/

#ifndef TISSUES_H
#define TISSUES_H

#include <vector>

#include "buhlmann.hpp"
#include "vpm.hpp"
#include "constants.hpp"

#define NUM_COMPARTMENTS 16

namespace Body {
    //Class for a set of tissue comparments
    template<class cell> class Tissues {
    private:
        //Vector holding the tissue compartments
        //Template use is so both Buhl and VPM classes can be used
        std::vector<cell*> compartments;

        //Gradient factor values
        float GFgrad;
        const float GFHi;
        const float GFLo;

        //Deco stop status
        bool in_deco;
        bool first_stop;

        float *gas;
        float pAmb = SEA_LEVEL_PAMB;

        
    public:
        Tissues(float GFLoIn, float GFHiIn, float *gas_mix, float dtime);

        void wait(int time);

        void change_depth(int new_depth, int rate);

        void set_partial_pressures(std::vector<float> new_pN2s, std::vector<float> new_pHes);

        int get_ceiling();

        int get_next_stop();
    };
}

#endif //TISSUES_H