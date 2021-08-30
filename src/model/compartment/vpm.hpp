/*
Varying Permeability Model extension to Buhlmann model
*/

#ifndef VPM_H
#define VPM_H

#include "buhlmann.hpp"

//Namespace for VPM model
namespace ModelVPM {
    //The VPM is an extension of the Buhlann model so inheritance can be used
    class VPMCell : public ModelBuhlmann::BuhlmannCell {
    private:

    public:

    };
}


#endif //VPM_H