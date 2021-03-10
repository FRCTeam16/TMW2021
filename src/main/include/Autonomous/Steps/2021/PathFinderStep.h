#pragma once

#include "../../Step.h"
#include <units/length.h>
#include <units/angle.h>
#include <queue>
#include <deque>    

using namespace units::length; 
using namespace units::angle;
using namespace std;


class Target {
public:
    Target(inch_t xpos, inch_t ypos, double speed, degree_t robotAngle)
        : xpos(xpos), ypos(ypos), speed(speed), angle(robotAngle) {}
    inch_t xpos;
    inch_t ypos;
    double speed;
    degree_t angle;
};

class PathFinderStep : Step
{
public:
    PathFinderStep(initializer_list<Target> list)
    : targets(std::deque<Target>(list.begin(), list.end()))
    {
    }

    bool Run(std::shared_ptr<World> world) override;

private:
    bool started = false;
    queue<Target> targets;
    Target currentTarget {0_ft, 0_ft, 0, 0_deg};
    inch_t distance_threshold = 3.0_in;
};