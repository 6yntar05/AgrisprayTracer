#include <string>
#include <iomanip>
#include <limits>
#include <numbers>
#include <iostream>

#include "poly/field.h"
#include "poly/parser.h"

int main(int argc, char* argv[]) {
	if (argc <= 1) {
		std::cerr << "Put filepath to argument" << std::endl;
		exit(-1);
	}

	agris::geo::field field = agris::input::parseFile(argv[1]);
	std::cout << "OuterBoundary -> LinearRing:\n" << std::setprecision(16);
	for (auto& i : field.outerBoundary) {
		std::cout << "\t Latitude: " << i.latitude << "; Longitude: " << i.longitude << '\n';
	}
	for (auto& boundary : field.innerBoundaries) {
		std::cout << "InnerBoundary -> LinearRing:\n";
		for (auto& i : boundary) {
			std::cout << "\t Latitude: " << i.latitude << "; Longitude: " << i.longitude << '\n';
		}
	}
	return 0;
}