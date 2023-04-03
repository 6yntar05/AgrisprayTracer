#pragma once
#include "poly/field.h"
#include <cmath>
#include <numbers>

using namespace std::numbers;
namespace agris::geo {

constexpr double simplePointsDiff = 100.0;
constexpr double R = 6371;

inline double pointsDiff(const Coordinate x, const Coordinate y) {                      // !
    // gaversinuses
    double lat = (y.latitude-x.latitude)   * (pi/180);
    double lon = (y.longitude-x.longitude) * (pi/180);
    double rez = (sin(lat/2) * sin(lat/2)) + (cos(x.latitude*(pi/180)) * cos(y.latitude*(pi/180)) * sin(lon/2) * sin(lon/2));
    return 2 * R * atan2(sqrt(rez), sqrt(1-rez));
}

inline Coordinate findPoint(const Coordinate coord, const double x, const double y) {   // !
    double latitude  = coord.latitude  + ((y) * (180 / pi) / R);
    double longitude = coord.longitude + ((x) * (180 / pi) / (R*cos(latitude * pi/180)));
    return {latitude, longitude};
}

inline std::pair<Coordinate, Coordinate> findCorners(const Field& poly) {
    Coordinate minimal, maximal;
    bool isFirstIterate = true;

    for (const Coordinate& coord : poly.outerBoundary) {
        if (isFirstIterate) {
            minimal = maximal = coord;
            isFirstIterate = false;
        }

        if (coord.latitude < minimal.latitude)
            minimal.latitude = coord.latitude;
        else if (coord.latitude > maximal.latitude)
            maximal.latitude = coord.latitude;

        if (coord.longitude < minimal.longitude)
            minimal.longitude = coord.longitude;
        else if (coord.longitude > maximal.longitude)
            maximal.longitude = coord.longitude;
    }

    return {minimal, maximal};
}

} // namespace agris::geo