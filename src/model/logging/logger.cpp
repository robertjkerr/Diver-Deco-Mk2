/*
Methods for logger class
*/

#include "logger.h"
#include "../compartments/tissues.h"

namespace DecoModel {
    Logger::Logger() {}

    //******************************************
    // Logs data for Buhlmann cells
    //******************************************
    void Logger::log_buhl(void* tissues_in) {
        Tissues* tissues = (Tissues*) tissues_in; 
    }
}