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
    std::vector<std::vector<Quant>> quantized;

  public:
    QuanizedField(Field field, double quantSize) {
        this->quantized = {};

        // Find corners to split field:
        auto corners = findCorners(field);
        std::cerr << "Verbose: field corners:\n" << std::setprecision(16)
			<< '['<<corners.first.latitude<<','<<corners.first.longitude
        	<< "] <-> ["<<corners.second.latitude<<','<<corners.second.longitude<<']' << std::endl;
		
		// Prepairing to splitting:
		double lenght = geo::pointsDiff(corners.first, {corners.first.latitude, corners.second.longitude}) * 1000.0;
		double width  = geo::pointsDiff(corners.first, {corners.second.latitude, corners.first.longitude}) * 1000.0;
		std::cerr << "m\n\tLenght: \t" << lenght << "m\n\tWidth: \t\t" << width << "m\n"; // test
		
		Coordinate testPoint = findPoint( // test
			corners.first,
			geo::pointsDiff(corners.first, {corners.first.latitude, corners.second.longitude}),
			geo::pointsDiff(corners.first, {corners.second.latitude, corners.first.longitude})
		);
		std::cerr << "Test: " << testPoint.latitude << ", " << testPoint.longitude << '\n'; // test

		// Quantize:
		int x = lenght / quantSize, y = width / quantSize; // Resolution
		std::cout << "\tsize x: " << x << "; size y: " << y << '\n'; // test
		this->quantized.resize(x);

		for (int l = 0; l < x; l++) { // Fill this->quantized field by lines:
			std::vector<Quant> line;
			line.resize(y);
			for (int i = 0; i < y; i++) { // Fill every line:
				line.push_back({Coordinate{}, false}); // No-filled | Geo coords
			}

			this->quantized.push_back(line);
		}
    }
};

} // namespace agris::geo