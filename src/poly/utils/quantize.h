#pragma once
#include "poly/field.h"
#include "poly/utils/geo.h"

#include <vector>
#include <iomanip>
#include <iostream>
#include <cmath>
namespace agris::geo {

inline bool isBoundaryProhibit(Coordinate first, Coordinate second, Coordinate center, double droneRadius) {
	// Canonical equation of a straight line
	double m = (second.longitude - first.longitude) /
			  //----------------------------------
			   (second.latitude - first.latitude);		// angle ratio
			
	double b = first.longitude - (m * first.latitude);	// y-offset

	double d = std::abs((m*center.latitude) - center.longitude + b) /
			  //-------------------------------------------
			   				sqrt( pow(m, 2.0) + 1.0 );		// center to enge distance
	
	d *= 100000.0; // accuracy warning

	if (d > droneRadius)
		return true;
	return false;
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

	std::pair<Coordinate, Coordinate> corners;
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
				Coordinate center {
					((corners.second.latitude - corners.first.latitude) / double(y))*double(i)
						+ corners.first.latitude + (quantSize / 2.0),
					((corners.second.longitude - corners.first.longitude) / double(x))*double(l)
						+ corners.first.longitude + (quantSize / 2.0)
				};
				std::cerr << "x|y: " << l << ';' << i << "; X|Y: " << center.latitude <<';'<< center.longitude << std::endl; // test

				bool isOutside; // lenght between center and interpolated line of 2 geocoords < droneSize
				isOutside = isBoundaryProhibit({58.22, 84.74}, {58.23, 84.75}, center, droneRadius); // TODO: closest coords

				line.push_back({ center, isOutside }); // Single quant
			}

			this->quantized.push_back(line);
		}
	}

    QuanizedField(Field source)
	: source(source), corners(findCorners(source)) {
        std::cerr << "Verbose: field corners:\n" << std::setprecision(16)
			<< '['<<corners.first.latitude<<','<<corners.first.longitude
        	<< "] <-> ["<<corners.second.latitude<<','<<corners.second.longitude<<']' << std::endl;
		
		// Prepairing to splitting:
		this->lenght = geo::pointsDiff(corners.first, {corners.first.latitude, corners.second.longitude}) * 1000.0;
		this->width  = geo::pointsDiff(corners.first, {corners.second.latitude, corners.first.longitude}) * 1000.0;
		std::cerr << "m\n\tLenght: \t" << lenght << "m\n\tWidth: \t\t" << width << "m\n"; // test
    }
};

} // namespace agris::geo