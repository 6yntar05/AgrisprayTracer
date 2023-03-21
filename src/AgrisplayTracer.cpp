#define TEST

#include <iostream>
#include <iomanip>

#include "poly/field.h"
#include "poly/parser.h"
#ifdef TEST
#include "poly/utils/geo.h"
#include "poly/utils/quantize.h"
#endif
#include "flight/trace.h"

int main(int argc, char* argv[]) {
	if (argc <= 1) {
		std::cerr << "Usage: ./AgrisprayTracer <INPUT PATH> [OUTPUT PATH]" << std::endl;
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

	std::cout << "Generated flightplan: \n"
		<< plan.toString() << std::endl;
	if (argc <= 2) 
		plan.toFile(argv[2]);
	
#ifdef TEST
	// Poly area corners
	const auto test = findCorners(field);
	std::cerr << std::setprecision(16)
		<< "FIRST: " << test.first.latitude << ", " << test.first.longitude
		<< "\nSECOND: " << test.second.latitude << ", " << test.second.longitude
		<< std::endl;

	// Area size in metters
	std::cerr << std::setprecision(16)
		<< "LONG: " << agris::geo::pointsDiff(test.first, {test.second.latitude, test.first.longitude}) * 1000.0 << " m\n"
		<< "WIDE: " << agris::geo::pointsDiff(test.first, {test.first.latitude, test.second.longitude}) * 1000.0 << " m"
		<< std::endl;
#endif

	return 0;
}