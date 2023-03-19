#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <numbers>

#include "poly/field.h"

namespace agris::input {
    geo::field parseFile(const std::string path);
}