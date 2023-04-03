#pragma once
#include <string>
#include "poly/field.h"

namespace agris::input {

geo::Field parseFile(const std::string path);

}