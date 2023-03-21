#pragma once
#include "poly/field.h"
#include <cmath>
#include <numbers>

using namespace std::numbers;
namespace agris::geo {

constexpr double simplePointsDiff = 100.0;

inline double pointsDiff(const coordinate x, const coordinate y) {
    // gaversinuses
    double R = 6371;
    double lat = (y.latitude-x.latitude) * (pi/180);
    double lon = (y.longitude-x.longitude) * (pi/180);
    double rez = sin(lat/2) * sin(lat/2) + cos(x.latitude*(pi/180)) * cos(y.latitude*(pi/180)) * sin(lon/2) * sin(lon/2);
    double d = 2 * R * atan2(sqrt(rez), sqrt(1-rez));
    return d;
}

} // namespace agris::geo