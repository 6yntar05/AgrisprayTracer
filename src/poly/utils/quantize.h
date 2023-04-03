#pragma once
#include "poly/field.h"
#include "poly/utils/geo.h"

#include <vector>
#include <iomanip>
#include <iostream>

namespace agris::geo {

struct Quant {
    Coordinate coord;
    bool isFilled = false;
};

class QuanizedField {
  private:
    std::vector<Quant> quantized;

  public:
    QuanizedField(Field field, double droneSize, double sprayRadius) {
        this->quantized = {};

        // Find corners to split field:
        auto corners = findCorners(field);
        std::cerr << "Verbose: field corners:\n" << std::setprecision(16)
			<< '['<<corners.first.latitude<<','<<corners.first.longitude
        	<< "] <-> ["<<corners.second.latitude<<','<<corners.second.longitude<<']' << std::endl;
		
		// Splitting:
		std::cerr << "\tDiagonal: \t" << geo::pointsDiff(corners.first, corners.second) * 1000.0
			<< "m\n\tLenght: \t" << geo::pointsDiff(corners.first, {corners.first.latitude, corners.second.longitude}) * 1000.0
			<< "m\n\tWidth: \t\t" << geo::pointsDiff(corners.first, {corners.second.latitude, corners.first.longitude}) * 1000.0 << "m\n";
		
		Coordinate testPoint = findPoint(
			corners.first,
			geo::pointsDiff(corners.first, {corners.first.latitude, corners.second.longitude}),
			geo::pointsDiff(corners.first, {corners.second.latitude, corners.first.longitude})
		);
		std::cerr << "Test: " << testPoint.latitude << ", " << testPoint.longitude << '\n';
    }
};

} // namespace agris::geo