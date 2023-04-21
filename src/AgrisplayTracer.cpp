#define TEST
#include <iostream>

#include "poly/field.h"
#include "poly/parser.h"
#include "flight/trace.h"
#include "flight/mavlink.h"

int main(int argc, char* argv[]) {
	if (argc <= 1 || argc > 3) {
		std::cerr << "Usage: ./AgrisprayTracer <INPUT PATH> [OUTPUT PATH]" << std::endl;
		exit(0);
	}
	// Parse .KML file // TODO: .poly parser
	agris::geo::Field field = agris::input::parseFile(argv[1]);
	std::cout << field.toString();

	// Try to trace polygon for agricultural drone (Simple version for now)
	agris::TraceParams params {
		field.outerBoundary.at(0),	// Takeoff coord
		field.outerBoundary.at(0),	// Landing coord
		20.0,	// Altitude
		6.0,	// Drone size
		16.0, 	// Field quant size
		90.0, 	// Angle
		8.0,	// Trace spray radius
		{{}}	// Spray params... Later
	};

	// Trace
	agris::Tracer tracer { field, params };
	agris::mavlink::FlightPlan plan = tracer.getFlightplan();

	// Print (& write) flightplan as .waypoints
#ifndef TEST
	std::cout << "Generated flightplan: \n" << plan.toString() << std::endl;
	if (argc >= 3)
		plan.toFile(argv[2]);
#endif
	return 0;
}