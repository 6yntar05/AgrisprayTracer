#pragma once
#include "poly/field.h"
#include "flight/mavlink.h"

#include <vector>

namespace agris {

struct traceParams {
    float altitude;
    float speed;
    double radius;
    float servo;
};

class simpleTrace {
    private:
    // Input data
    geo::field field;
    traceParams params;
    // Waypoints
    mavlink::flightPlan plan;

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