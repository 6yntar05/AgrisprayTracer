#pragma once
#include "poly/field.h"
#include "flight/mavlink.h"
#include "poly/utils/quantize.h"

#include <vector>

namespace agris {
namespace tracing {

struct QuantizationUnit {
    double size;
    geo::Coordinate certer;
};

} // namespace tracing

struct SprayParams {
  // Necessary:
    double rate;    // [?? per ??]

  // Optional:
    double speed;        // Speed affects spray rate, if sprayPower is unsupported [kmph]
    uint pwm;            // If supported [0 < analog value < maxPossiblePWM]
    uint maxPossiblePWM; // Max possible analog value for pwm [0 - no support]

    SprayParams(double rate, double speed, uint maxPossiblePWM = 4096) // Implies proportionality // TODO: lambda
    : rate(rate), speed(speed), maxPossiblePWM(maxPossiblePWM) {
        // Calculate pwm by speed and sprayrate
        this->pwm = 0;
        // TODO
    }

    SprayParams(double rate)
    : rate(rate), pwm(0), maxPossiblePWM(0) {
        // Calculate speed by spray rate
        this->speed = 0.0;
        // TODO
    }
};

struct TraceParams {
    // General:
    geo::Coordinate takeoffCoord;
    geo::Coordinate landingCoord = takeoffCoord;
    double altitude  = 100.0;
    double droneSize = 5.0;

    // Spray:
    SprayParams spray;
    double radius;  // [meters]
};

class Tracer {
    private:
    // Input data
    geo::Field field;
    TraceParams params;
    // Waypoints
    mavlink::FlightPlan plan;
    // Internal data
    geo::Coordinate begin;
    geo::QuanizedField quants;

    public:
    // Service
    Tracer(const geo::Field& field, const TraceParams& params);
    
    void trace() noexcept;
    mavlink::FlightPlan getFlightplan();

    // Updaters
    void updateFlightParams(const TraceParams& params);
    void updateFlightField(const geo::Field& field);
};

} // namespace agris