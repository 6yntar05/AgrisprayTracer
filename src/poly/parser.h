#pragma once
#include <string>
#include "poly/field.h"

namespace agris::input {

geo::field parseFile(const std::string path);

}