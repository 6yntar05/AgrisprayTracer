#pragma once
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>

namespace agris::geo {

struct Coordinate {
    double latitude;
    double longitude;
    //double altitude;
    //double heading;

    Coordinate() = default;
    Coordinate(double latitude, double longitude) : latitude(latitude), longitude(longitude) {}
};

using Boundary = std::vector<Coordinate>;

struct Field {
    //std::string_view name;
    Boundary outerBoundary;
    std::vector<Boundary> innerBoundaries; // Extra fragments; Will be considered during the tracing

    std::string toString() {
        std::stringstream stream;
        stream << "OuterBoundary -> LinearRing:\n" << std::setprecision(16);
        for (auto& i : this->outerBoundary) {
            stream << "\t Latitude: " << i.latitude << "; Longitude: " << i.longitude << '\n';
        }
        for (auto& Boundary : this->innerBoundaries) {
            stream << "InnerBoundary -> LinearRing:\n";
            for (auto& i : Boundary) {
                stream << "\t Latitude: " << i.latitude << "; Longitude: " << i.longitude << '\n';
            }
        }
        return std::move(stream).str();
    }
};

} // namespace agris::geo