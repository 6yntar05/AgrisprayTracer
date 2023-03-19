#pragma once
#include "poly/field.h"
#include "flight/waypoints.h"

#include <vector>

namespace agris {
class simpleTrace {
    private:
    // Input data
    geo::field field;
    flightParams params;
    // Waypoints
    flightPlan plan;

    public:
    // Service
    simpleTrace(const geo::field& field, const flightParams& params)
        : field(field), params(params) { this->trace(); }
    
    void trace() {
        // TODO
        //field.outerBoundary
    }
    flightPlan getFlightplan() {
        return plan;
    }
    

    // Updaters
    void updateFlightParams(const flightParams& params) {
        this->params = params;
        this->trace();
    }
    void updateFlightField(const geo::field& field) {
        this->field = field;
        this->trace();
    }
};
} // namespace agris