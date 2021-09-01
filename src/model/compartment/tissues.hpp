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

//Namespace for the body of a diver
namespace Body {
    //Class for a set of tissue comparments
    template<class cell> class Tissues {
    private:
        //Vector holding the tissue compartments
        //Template use is so both Buhl and VPM classes can be used
        std::vector<cell*> compartments;

        //Gradient factor values
        float GF_grad;
        const float GFHi;
        const float GFLo;

        

        float pAmb = SEA_LEVEL_PAMB;

        
    public:
        //Deco stop status
        bool in_deco;
        bool first_stop;
        
        Tissues(float GFLoIn, float GFHiIn, float *gas_mix, float dtime);

        //Set ppN2 and ppHe for all tissues
        void set_partial_pressures(std::vector<float> new_pN2s, std::vector<float> new_pHes);

        //Dive segment
        void dive_segment(int time, int depth_rate);

        //Gets the current depth
        int get_depth();

        //Find the total ceiling
        int get_ceiling();

        //Round ceiling to multiple of 3
        int get_next_stop();

        void set_GF_grad(float first_stop_depth);

        //Return a {ppO2, ppHe} vector
        std::vector<int> get_gas_mix();

        //Changing gas mix - should be in {%O2, %He}
        void switch_gas(std::vector<int> new_gas);
    };
}

#endif //TISSUES_H