/*
Header for a logger class. Stores pressure data logged by tissues
*/

#ifndef LOGGER_H
#define LOGGER_H

#include "../types_constants/types.h"

namespace DecoModel {
    class Logger {
        private:
            std::vector<std::array<float, NUM_COMPARTMENTS>> N2_pres_log;
            std::vector<std::array<float, NUM_COMPARTMENTS>> He_pres_log;
            std::vector<float> otu_log;
            

        public:
            Logger();

            void log_buhl(void* tissues);
            //void log_vpm(void* tissues);
    };
}

#endif //LOGGER_H