#pragma once
#include "poly/field.h"
#include "poly/utils/geo.h"

#include <vector>
#include <iomanip>
#include <iostream>

namespace agris::geo {

inline bool foundIsOutside(Coordinate x, Coordinate y, Coordinate center, double droneRadius) {
	// Aboba
	return true;
};

struct Quant {
    Coordinate coord;
	bool isOutside = false;
    bool isFilled  = false;
};

class QuanizedField {
  private:
    std::vector<std::vector<Quant>> quantized;
	Field source;

	double lenght;
	double width;

  public:
	void quantize(double quantSize, double droneRadius) {
		int x = lenght / quantSize, y = width / quantSize; // Resolution
		std::cout << "\tsize x: " << x << "; size y: " << y << '\n'; // test
		this->quantized.resize(x);

		for (int l = 0; l < x; l++) { // Fill this->quantized field by lines:
			std::vector<Quant> line;
			line.resize(y);
			for (int i = 0; i < y; i++) { 	// Fill every line:
				Coordinate center {50.0, 50.0}; // TODO

				bool isOutside; // lenght between center and interpolated line of 2 geocoords < droneSize
				isOutside = foundIsOutside({49.9999, 49.9999}, {50.0001, 50.0001}, center, droneRadius); // TODO: closest coords

				line.push_back({ center, isOutside }); // Single quant
			}

			this->quantized.push_back(line);
		}
	}

    QuanizedField(Field source)
	: source(source) {
        // Find corners to split field:
        auto corners = findCorners(source);
        std::cerr << "Verbose: field corners:\n" << std::setprecision(16)
			<< '['<<corners.first.latitude<<','<<corners.first.longitude
        	<< "] <-> ["<<corners.second.latitude<<','<<corners.second.longitude<<']' << std::endl;
		
		// Prepairing to splitting:
		this->lenght = geo::pointsDiff(corners.first, {corners.first.latitude, corners.second.longitude}) * 1000.0;
		this->width  = geo::pointsDiff(corners.first, {corners.second.latitude, corners.first.longitude}) * 1000.0;
		std::cerr << "m\n\tLenght: \t" << lenght << "m\n\tWidth: \t\t" << width << "m\n"; // test
		
		Coordinate testPoint = findPoint( // test
			corners.first,
			geo::pointsDiff(corners.first, {corners.first.latitude, corners.second.longitude}),
			geo::pointsDiff(corners.first, {corners.second.latitude, corners.first.longitude})
		);
		std::cerr << "Test: " << testPoint.latitude << ", " << testPoint.longitude << '\n'; // test
    }
};

} // namespace agris::geo