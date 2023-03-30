#pragma once
#include "external/fastmavlink/mav_cmd.h"

#include <vector>
#include <string>

namespace agris::mavlink { // MavLink v? compatible data

struct waypoint {
    // ID <- index of waypoints
    MAV_CMD command = MAV_CMD_NAV_WAYPOINT;
    uint currentWP  = 0;
    uint coordFrame = 3;
    double param1 = 0.0;
    double param2 = 0.0;
    double param3 = 0.0;
    double param4 = 0.0;
    double param5 = 0.0; // x/Latitude
    double param6 = 0.0; // y/Longitude
    double param7 = 0.0; // z/Altitude
    bool autocontinue = true;
};

class flightPlan {
  private:
    /*static constexpr*/ std::string fileHeader = "QGC WPL 110\n";

  public:
    std::vector<waypoint> plan;

    std::string toString(uint precision = 14);
    void toFile(std::string path);
};

} // namespace agris::mavlink