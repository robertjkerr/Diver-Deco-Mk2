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

            //Returns depth ceiling
            uint16_t get_ceiling();

            //Inacts a linear dive segment on body
            void invoke_dive_segment(Segment segment);

            float get_otu();
            void set_otu(float new_otu);

            //Data logging methods
            void attach_logger(Logger* logger_ptr);
            void start_logging();
            void stop_logging();

            //Returns the array of tissue compartments
            std::vector<Cell> get_compartments();
            
            // Gradient factor methods 
            void set_GF_grad(uint16_t first_stop_depth);
            void reset_GF(uint16_t depth);
    };
}

#endif //TISSUES_H