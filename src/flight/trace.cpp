#define SIMPLETRACE

#include "flight/trace.h"
#include "flight/mavlink.h"
#include "poly/field.h"

#include <vector>

namespace agris {

// class tracer
tracer::tracer(const geo::field& field, const traceParams& params)
: field(field), params(params), quants(field, params.droneSize, params.radius) {
    this->trace();
}

void tracer::trace() noexcept {
    std::vector<mavlink::waypoint> newplan;

#ifdef SIMPLETRACE
    // Fly around the perimeter
    std::vector<geo::coordinate> bound = this->field.outerBoundary;
    for (size_t i = 0; i < bound.size(); i++) {
        geo::coordinate sourceCoordinate = bound.at(i);

        // Create points
        mavlink::waypoint point;
        if (i == 0) {
            // First point - takeoff + CurrentWP
            point = {
                MAV_CMD::MAV_CMD_NAV_TAKEOFF, 1, {},
                {}, {}, {}, {}, sourceCoordinate.latitude, sourceCoordinate.longitude, this->params.altitude
            };
            this->begin = geo::coordinate { sourceCoordinate.latitude, sourceCoordinate.longitude };
            newplan.push_back(point);
            point.command = MAV_CMD_DO_SPRAYER;
            point.param1 = 1;

        } else if (i+1 == bound.size()) {
            // Last point - landing
            point = {
                MAV_CMD::MAV_CMD_NAV_WAYPOINT, {}, {},
                {}, {}, {}, {}, sourceCoordinate.latitude, sourceCoordinate.longitude, this->params.altitude
            };
            newplan.push_back(point);
            point.command = MAV_CMD_DO_SPRAYER;
            point.param1 = 0;
            newplan.push_back(point);
            point = {
                MAV_CMD::MAV_CMD_NAV_LAND, {}, {},
                {}, {}, {}, {}, this->begin.latitude, this->begin.longitude, this->params.altitude
            };

        } else {
            // Route
            point = {
                MAV_CMD::MAV_CMD_NAV_WAYPOINT, {}, {},
                {}, {}, {}, {}, sourceCoordinate.latitude, sourceCoordinate.longitude, this->params.altitude
            };
        }

        // Write point to the newplan
        newplan.push_back(point);
    }
#endif

    // Rewrite plan
    this->plan.plan = newplan;
}

mavlink::flightPlan tracer::getFlightplan() {
    return plan;
}

// Updaters
void tracer::updateFlightParams(const traceParams& params) {
    this->params = params;
    this->trace();
}

void tracer::updateFlightField(const geo::field& field) {
    this->field = field;
    this->trace();
}

} // namespace agris