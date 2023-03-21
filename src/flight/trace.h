#pragma once
#include "poly/field.h"
#include "flight/mavlink.h"

#include <vector>

namespace agris {
namespace tracing {

struct quantizationUnit {
    double size;
    geo::coordinate certer;
};

} // namespace tracing

struct traceParams {
    float altitude  = 100.0;
    float speed     = 5.0;
    double radius   = 10.0;
    float servo     = 0.0;
    double droneSize= 5.0;
};

class simpleTrace {
    private:
    // Input data
    geo::field field;
    traceParams params;
    // Waypoints
    mavlink::flightPlan plan;
    // Internal data
    geo::coordinate begin;

    public:
    // Service
    simpleTrace(const geo::field& field, const traceParams& params);
    
    void trace();
    mavlink::flightPlan getFlightplan();

    // Updaters
    void updateFlightParams(const traceParams& params);
    void updateFlightField(const geo::field& field);
};

} // namespace agris