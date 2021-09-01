/*
Header for dive segments
*/

#ifndef SEGMENTS_H
#define SEGMENTS_H

#include <vector>

#include "../compartment/tissues.hpp"

//Dive planning namespace
namespace Planner {
    //Structure for generic bottom segment
    struct BottomSegment {
        BottomSegment(int timeIn, int start_depthIn, int end_depthIn, std::vector<int> gasIn);
        const int time;
        const int start_depth;
        const int end_depth;
        const std::vector<int> gas;
        float rate();
    };

    //Inacts bottom profile on a set of tissues
    template<class cell>
    void invoke_profile(Body::Tissues<cell> *compartments, std::vector<BottomSegment*> *dive_profile); 

}


#endif //SEGMENTS_H
