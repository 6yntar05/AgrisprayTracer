#define SIMPLETRACE

#include "flight/trace.h"
#include "flight/mavlink.h"
#include "poly/field.h"

#include <vector>

namespace agris {

// class Tracer
Tracer::Tracer(const geo::Field& field, const TraceParams& params)
: field(field), params(params), lines(field) {
    this->lines.makelines(params.angle, params.angle);

    //this->trace();
}

void Tracer::trace() noexcept {
    std::vector<mavlink::Waypoint> newplan;

#ifdef SIMPLETRACE
    // Fly around the perimeter
    std::vector<geo::Coordinate> bound = this->field.outerBoundary;
    for (size_t i = 0; i < bound.size(); i++) {
        geo::Coordinate sourceCoordinate = bound.at(i);

        // Create points
        mavlink::Waypoint point;
        if (i == 0) {
            // First point - takeoff + CurrentWP
            point = {
                MAV_CMD::MAV_CMD_NAV_TAKEOFF, 1, {},
                {}, {}, {}, {}, sourceCoordinate.latitude, sourceCoordinate.longitude, this->params.altitude
            };
            this->begin = geo::Coordinate { sourceCoordinate.latitude, sourceCoordinate.longitude };
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

mavlink::FlightPlan Tracer::getFlightplan() {
    return plan;
}

// Updaters
void Tracer::updateFlightParams(const TraceParams& params) {
    this->params = params;
    this->trace();
}

void Tracer::updateFlightField(const geo::Field& field) {
    this->field = field;
    this->trace();
}

} // namespace agris