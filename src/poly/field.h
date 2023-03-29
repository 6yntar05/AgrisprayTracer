#pragma once
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>

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

    std::string toString() {
        std::stringstream stream;
        stream << "OuterBoundary -> LinearRing:\n" << std::setprecision(16);
        for (auto& i : this->outerBoundary) {
            stream << "\t Latitude: " << i.latitude << "; Longitude: " << i.longitude << '\n';
        }
        for (auto& boundary : this->innerBoundaries) {
            stream << "InnerBoundary -> LinearRing:\n";
            for (auto& i : boundary) {
                stream << "\t Latitude: " << i.latitude << "; Longitude: " << i.longitude << '\n';
            }
        }
        return std::move(stream).str();
    }
};

} // namespace agris::geo