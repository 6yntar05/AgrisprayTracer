#include "flight/trace.h"
#include "flight/mavlink.h"
#include "poly/field.h"

#include <vector>

namespace agris {

// class simpleTrace
simpleTrace::simpleTrace(const geo::field& field, const traceParams& params)
    : field(field), params(params) { this->trace(); }

void simpleTrace::trace() {
    std::vector<mavlink::waypoint> newplan;

    // Fly around the perimeter
    std::vector<geo::coordinate> bound = this->field.outerBoundary;
    for (size_t i = 0; i < bound.size(); i++) {
        geo::coordinate sourceCoordinate = bound.at(i);

        // Create points
        mavlink::waypoint point;
        if (i == 0) {
            // First point - takeoff
            point = {
                MAV_CMD::MAV_CMD_NAV_TAKEOFF,
                {}, {}, {}, {}, {}, {},
                sourceCoordinate.latitude, sourceCoordinate.longitude
            };

        } else if (i == bound.size()) {
            // Last point - landing
            point = {
                MAV_CMD::MAV_CMD_NAV_LAND,
                {}, {}, {}, {}, {}, {},
                sourceCoordinate.latitude, sourceCoordinate.longitude
            };

        } else {
            // Route
            point = {
                MAV_CMD::MAV_CMD_NAV_WAYPOINT,
                {}, {}, {}, {}, {}, {},
                sourceCoordinate.latitude, sourceCoordinate.longitude
            };
        }

        // Write point to the newplan
        newplan.push_back(point);
    }

    // Rewrite plan
    this->plan.plan = newplan;
}

mavlink::flightPlan simpleTrace::getFlightplan() {
    return plan;
}

// Updaters
void simpleTrace::updateFlightParams(const traceParams& params) {
    this->params = params;
    this->trace();
}

void simpleTrace::updateFlightField(const geo::field& field) {
    this->field = field;
    this->trace();
}

} // namespace agris