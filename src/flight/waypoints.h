#pragma once
#include <vector>

namespace agris {
struct waypoint {
    // TODO
};

struct flightPlan {
    waypoint takeoffPoint;
    std::vector<waypoint> flightPoints;
    waypoint takedownPoint;
};

struct flightParams {
    float altitude;
    float speed;
    double radius;
    float servo;
};
} // namespace agris