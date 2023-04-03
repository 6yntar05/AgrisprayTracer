#pragma once
#include "poly/field.h"
#include "flight/mavlink.h"
#include "poly/utils/quantize.h"

#include <vector>

namespace agris {
namespace tracing {

struct quantizationUnit {
    double size;
    geo::coordinate certer;
};

} // namespace tracing

struct sprayParams {
  // Necessary:
    double rate;    // [?? per ??]

  // Optional:
    double speed;        // Speed affects spray rate, if sprayPower is unsupported [kmph]
    uint pwm;            // If supported [0 < analog value < maxPossiblePWM]
    uint maxPossiblePWM; // Max possible analog value for pwm [0 - no support]

    sprayParams(double rate, double speed, uint maxPossiblePWM = 4096) // Implies proportionality // TODO: lambda
    : rate(rate), speed(speed), maxPossiblePWM(maxPossiblePWM) {
        // Calculate pwm by speed and sprayrate
        this->pwm = 0;
        // TODO
    }

    sprayParams(double rate)
    : rate(rate), pwm(0), maxPossiblePWM(0) {
        // Calculate speed by spray rate
        this->speed = 0.0;
        // TODO
    }
};

struct traceParams {
    // General:
    geo::coordinate takeoffCoord;
    geo::coordinate landingCoord = takeoffCoord;
    double altitude  = 100.0;
    double droneSize = 5.0;

    // Spray:
    sprayParams spray;
    double radius;  // [meters]
};

class tracer {
    private:
    // Input data
    geo::field field;
    traceParams params;
    // Waypoints
    mavlink::flightPlan plan;
    // Internal data
    geo::coordinate begin;
    geo::quanizedField quants;

    public:
    // Service
    tracer(const geo::field& field, const traceParams& params);
    
    void trace() noexcept;
    mavlink::flightPlan getFlightplan();

    // Updaters
    void updateFlightParams(const traceParams& params);
    void updateFlightField(const geo::field& field);
};

} // namespace agris