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
    simpleTrace(const geo::field& field, const traceParams& params)
        : field(field), params(params) { this->trace(); }
    
    void trace() {
        this->plan = {};
        // TODO
        //field.outerBoundary
    }
    mavlink::flightPlan getFlightplan() {
        return plan;
    }
    

    // Updaters
    void updateFlightParams(const traceParams& params) {
        this->params = params;
        this->trace();
    }
    void updateFlightField(const geo::field& field) {
        this->field = field;
        this->trace();
    }
};
} // namespace agris