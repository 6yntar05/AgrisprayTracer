#pragma once
#include "poly/field.h"
#include "poly/utils/geo.h"

#include <vector>
#include <iomanip>
#include <iostream>
#include <cmath>
namespace agris::geo {

inline bool isBoundaryNotProhibit(Coordinate first, Coordinate second, Coordinate center, double droneRadius) {
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

struct Line {
	double angle;
	Coordinate begin;
	Coordinate end;
	std::vector<Coordinate> breaks;
};

class LinedField {
private:
	Field source;

	std::pair<Coordinate, Coordinate> corners;
	double lenght;
	double width;

public:
	std::vector<Line> lines;

	void makelines(double quantSize, double angle, double offset = 0.0) {
		Coordinate start{corners.first.latitude + offset, corners.first.longitude};
		double xstep = quantSize * std::cos(angle);
		double ystep = quantSize * std::sin(angle);

		for(double x = start.latitude, y=start.longitude; 
			x < corners.second.latitude && y < corners.second.longitude;
			x += xstep, y+=ystep){
				// Create a line segment from (x, y) to (x + xstep, y + ystep)
				Coordinate begin{x, y};
				Coordinate end{x + xstep, y + ystep};
				lines.push_back(Line{angle, begin, end, {}});
			}

		
		
	}

	LinedField(Field source)
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

/*
struct Quant {
    Coordinate coord;
	bool isOutside = false;
    bool isFilled  = false;
};

class QuanizedField {
  private:
	Field source;

	std::pair<Coordinate, Coordinate> corners;
	double lenght;
	double width;

  public:
    std::vector<std::vector<Quant>> quantized;

	void quantize(double quantSize, double droneRadius) {
		int x = lenght / quantSize, y = width / quantSize; // Resolution
		std::cout << "\tsize x: " << x << "; size y: " << y << '\n'; // test
		this->quantized.resize(y);

		for (int xi = 0; xi < x; xi++) { // Fill this->quantized field by lines:
			std::vector<Quant> line;

			for (int yi = 0; yi < y; yi++) { // Fill every line: // TODO: fix this shit
				float yRelative = (corners.second.latitude - corners.first.latitude) / double(y);
				float xRelative = (corners.second.longitude - corners.first.longitude) / double(x);

				Coordinate center {
					yRelative * double(yi) + corners.first.latitude + (yRelative / 2.0),
					xRelative * double(xi) + corners.first.longitude + (xRelative / 2.0)
				};

				std::cerr << "x|y: " << xi << ';' << yi << "; X|Y: " << center.latitude <<';'<< center.longitude << std::endl; // test

				double closestDistance = 228777;
				size_t closestIndex = 1;
				for (size_t i = 1; i < this->source.outerBoundary.size(); i++) {
					auto& coord = this->source.outerBoundary.at(i);
					double currentDistance = std::sqrt(
						std::pow(std::abs(center.latitude - coord.latitude), 2) +
						std::pow(std::abs(center.longitude - coord.longitude), 2)
					);
					if (currentDistance < closestDistance) {
						closestDistance = currentDistance;
						closestIndex = i;
					}
				}

				bool isOutside; // lenght between center and interpolated line of 2 geocoords < droneSize
				try {
					isOutside = isBoundaryNotProhibit(
						this->source.outerBoundary.at(closestIndex),
						this->source.outerBoundary.at(closestIndex+1),
						center, droneRadius
					) || isBoundaryNotProhibit(
						this->source.outerBoundary.at(closestIndex-1),
						this->source.outerBoundary.at(closestIndex),
						center, droneRadius
					);
				} catch (...) { isOutside = false; }
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
*/

} // namespace agris::geo