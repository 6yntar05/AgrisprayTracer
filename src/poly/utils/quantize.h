#pragma once
#include "poly/field.h"

namespace agris::geo {

inline std::pair<coordinate, coordinate> findCorners(const field& poly) {
    coordinate minimal, maximal;
    bool isFirstIterate = true;

    for (const coordinate& coord : poly.outerBoundary) {
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