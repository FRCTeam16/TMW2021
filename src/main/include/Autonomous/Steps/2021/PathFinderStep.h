#pragma once

#include "../../Step.h"
#include <units/length.h>
#include <queue>

using namespace units::length; 
using namespace std;


class Target {
public:
    inch_t xpos;
    inch_t ypos;
    double speed;
    double angle;
};

class PathFinderStep : Step
{
public:
    PathFinderStep(queue<Target> _targets) : targets(_targets)
    {
    }

    bool Run(std::shared_ptr<World> world) override;

private:
    bool started = false;
    queue<Target> targets;
    Target currentTarget;
    inch_t distance_threshold = 3.0_in;
};