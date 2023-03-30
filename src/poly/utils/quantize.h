#pragma once
#include "poly/field.h"

#include <vector>

namespace agris::geo {

struct quant {
    coordinate coord;
    bool isFilled = false;
};

class quanizedField {
  private:
    std::vector<quant> quantized;

  public:
    quanizedField(field _field, double droneSize, double sprayRadius) {
        this->quantized = {};
    }
};

} // namespace agris::geo