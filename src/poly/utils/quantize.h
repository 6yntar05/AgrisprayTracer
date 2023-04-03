#pragma once
#include "poly/field.h"
#include "poly/utils/geo.h"

#include <vector>
#include <iostream>

namespace agris::geo {

struct quant {
    coordinate coord;
    bool isFilled = false;
};

class quanizedField {
  private:
    std::vector<quant> quantized;

  public:
    quanizedField(field field, double droneSize, double sprayRadius) {
        this->quantized = {};

        // Find corners to split field:
        auto corners = findCorners(field);

        std::cout << '['<<corners.first.latitude<<','<<corners.first.longitude
          << "] <-> ["<<corners.second.latitude<<','<<corners.second.longitude<<']' << std::endl;
    }
};

} // namespace agris::geo