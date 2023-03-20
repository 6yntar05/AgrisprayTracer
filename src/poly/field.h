#pragma once
#include <vector>
//#include <string>

namespace agris::geo {

struct coordinate {
    double latitude;
    double longitude;
    //double altitude;
    //double heading;
};

using boundary = std::vector<coordinate>;

struct field {
    //std::string_view name;
    boundary outerBoundary;
    std::vector<boundary> innerBoundaries; // Extra fragments; Will be considered during the tracing
};

} // namespace agris::geo