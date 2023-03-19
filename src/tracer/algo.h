#pragma once
#include "poly/field.h"

namespace agris {
struct flightPlan {

};

struct flightParams {
    float altitude;
    float speed;
    double radius;
    float servo;
};

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
        : field(field), params(params) {}
    
    void trace() {
        plan = {};
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