// This is a short example on the use of the Buhlmann class
// The tissues undergo a linear dive segment, and then the ceiling is printed

#include <iostream>
#include "src/model/compartments/tissues.h"
#include "src/model/algorithm/deco_algorithm.h"

using namespace DecoModel;

int main() {
    uint8_t gas[] = {20, 20};                 // {%O2, %He}
    uint16_t depth = 60, time = 45;           // 45 mins @ 60 metres
    int8_t rate = 0;                          // No depth change

    std::vector<uint8_t*> gases;
    gases.push_back(gas);

    Segment segment(depth, rate, time, gas);  // Create dive segment

    float GFHi = 0.8f, GFLo = 0.5f;
    Buhlmann tissues(GFHi, GFLo);             // Construct tissues

    tissues.invoke_dive_segment(segment);     // Invoke time at depth

    uint16_t ceiling;
    ceiling = tissues.get_ceiling();          // Calculate ascent ceiling

    std::cout << "Ceiling is:" << std::endl;
    std::cout << ceiling << std::endl;
    
    std::cout << "Stops are" << std::endl;

    std::vector<DecoStop> stops = get_deco_stops(tissues, depth, gases, 1);

    return 0;
}

