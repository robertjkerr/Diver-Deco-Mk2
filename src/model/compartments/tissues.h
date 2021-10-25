/*
Header for type for all compartments
*/

#ifndef TISSUES_H
#define TISSUES_H

#include "../logging/logger.h"
#include "../types_constants/types.h"
#include "vpm.h"

namespace DecoModel {
    class Tissues {
        private:
            //Compartments are kept in Tissues objs to make copying easier
            std::vector<Cell> compartments;
            bool vpm_flag;

            const float GFHi;
            const float GFLo;
            float GF_grad;

            //Oxygen toxicity unit count
            float otu = 0;

            //Logger data
            bool log_flag = false;
            Logger* logger;

            

        public:
            Tissues(bool vpm_flag, float GFLoIn, float GFHiIn);

            int get_ceiling();

            void invoke_dive_segment(Segment& segment);

            void set_otu(float new_otu);

            void switch_log_state(bool new_state);

            void attach_logger(Logger* logger_ptr);

            std::vector<Cell> get_compartments();

            float get_otu();
            
            void set_GF_grad(int first_stop_depth);
            
            void reset_GF(int depth);
    };
}

#endif //TISSUES_H