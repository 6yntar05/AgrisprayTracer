#pragma once
#include <vector>
#include <string>

namespace agris {
namespace mavlink { // MavLink v? compatible data
enum mavCommand {
    // MavLink MAV_CMD: Partial implementation
    // https://github.com/ArduPilot/mavlink/blob/master/message_definitions/v1.0/common.xml
    TODO
};

struct waypoint {
    // ID <- index of waypoints
    mavCommand command;
    uint currentWP;
    uint coordFrame;
    double param1;
    double param2;
    double param3;
    double param4;
    double param5;
        double* latitude = &param5;
        double* x = &param5;
    double param6;
        double* longitude = &param6;
        double* y = &param6;
    double param7;
        double* altitude = &param7;
        double* z = &param7;
    bool autocontinue = true;
};

struct flightPlan {
    std::vector<waypoint> plan;

    static constexpr std::string fileHeader = "QGC WPL 110\n";
    std::string toString() {
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
    void toFile(std::string path) {
        // TODO
    }
};
} // namespace mavlink
} // namespace agris