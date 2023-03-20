#include "flight/mavlink.h"

#include <sstream>
#include <fstream>

namespace agris::mavlink {

// class flightPlan
std::string flightPlan::toString(uint precision) {
    std::ostringstream stream;
    stream.precision(precision);
    stream << std::fixed; // Fixed precision
    stream << fileHeader;

    for (size_t i = 0; i < plan.size(); i++) {
        // Stream every point to MavLink waypoints
        waypoint point = plan.at(i);
        stream << i+1 << '\t'                 // Index
            << point.currentWP      << '\t' // Current WP
            << point.coordFrame     << '\t' // Coord frame
            << point.command        << '\t' // Command
            << point.param1         << '\t' // 1
            << point.param2         << '\t' // 2
            << point.param3         << '\t' // 3
            << point.param4         << '\t' // 4
            << point.param5         << '\t' // 5/X/Latitude
            << point.param6         << '\t' // 6/Y/Longitude
            << point.param7         << '\t' // 7/Z/Altitude
            << point.autocontinue   << '\n';// Autocontinue
    }

    return std::move(stream).str();
}
void flightPlan::toFile(std::string path) {
    std::ofstream file(path);
    file << this->toString();
    file.close();
}

} // namespace agris::