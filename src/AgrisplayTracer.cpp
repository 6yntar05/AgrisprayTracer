//#define TEST
#include <iostream>

#include "poly/field.h"
#include "poly/parser.h"
#include "flight/trace.h"
#include "flight/mavlink.h"

#ifdef TEST
#include <iomanip>
#include "poly/utils/geo.h"
#include "poly/utils/quantize.h"
#endif


int main(int argc, char* argv[]) {
	if (argc <= 1 || argc > 3) {
		std::cerr << "Usage: ./AgrisprayTracer <INPUT PATH> [OUTPUT PATH]" << std::endl;
		exit(0);
	}
	// Parse .KML file // TODO: .poly parser
	agris::geo::field field = agris::input::parseFile(argv[1]);
	std::cout << field.toString();

	// Try to trace polygon for agricultural drone (Simple version for now)
	agris::traceParams params { // Params for tracer
		{}, {}, {}, {}, {{}}, {}
	};
	// Create tracer
	agris::simpleTrace tracer { field, params };
	// Trace
	agris::mavlink::flightPlan plan = tracer.getFlightplan();
	// Update tracer params & retrace
	params.radius = 20.0;
	tracer.updateFlightParams(params);
	plan = tracer.getFlightplan();

	// Print (& write) flightplan as .waypoints
	std::cout << "Generated flightplan: \n" << plan.toString() << std::endl;
	if (argc >= 3)
		plan.toFile(argv[2]);
	
#ifdef TEST	// (internal utils for GUI and Tracer)
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