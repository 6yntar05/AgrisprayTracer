#include "flight/mavlink.h"

#include <fstream>

namespace agris::mavlink {

// class flightPlan
std::string flightPlan::toString() {
    std::string code = fileHeader;
    for (size_t i = 0; i < plan.size(); i++) {
        waypoint point = plan.at(i);
        code += std::to_string(i) + '\t'                    // Index
            + std::to_string(point.currentWP) + '\t'        // Current WP
            + std::to_string(point.coordFrame) + '\t'       // Coord frame
            + std::to_string(point.command) + '\t'          // Command
            + std::to_string(point.param1) + '\t'           // 1
            + std::to_string(point.param2) + '\t'           // 2
            + std::to_string(point.param3) + '\t'           // 3
            + std::to_string(point.param4) + '\t'           // 4
            + std::to_string(point.param5) + '\t'           // 5/X/Latitude
            + std::to_string(point.param6) + '\t'           // 6/Y/Longitude
            + std::to_string(point.param7) + '\t'           // 7/Z/Altitude
            + std::to_string(point.autocontinue) + '\n';    // Autocontinue
    }
    return code;
}
void flightPlan::toFile(std::string path) {
    std::ofstream file(path);
    file << this->toString();
    file.close();
}

} // namespace agris::