#include <iostream>
#include <iomanip>

#include "poly/field.h"
#include "poly/parser.h"
#include "flight/trace.h"

int main(int argc, char* argv[]) {
	if (argc <= 1) {
		std::cerr << "Put filepath to argument" << std::endl;
		exit(-1);
	}
	// Print polygon content
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

	// Try to trace polygon for agricultural drone (Simple version for now)
	agris::traceParams params {
		/*alt(m)*/ 8.0, /*speed(knots)*/ 10.0, /*radius(m)*/ 10.0, /*servo(?)*/ 255.0
	};
	agris::simpleTrace tracer { field, params };

	agris::mavlink::flightPlan plan = tracer.getFlightplan();
	params.radius = 20.0;
	tracer.updateFlightParams(params);
	plan = tracer.getFlightplan();

	return 0;
}