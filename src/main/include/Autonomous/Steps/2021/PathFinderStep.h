#pragma once

#include "../../Step.h"

class PathFinderStep : Step
{
    PathFinderStep()
    {

    }

    bool Run(std::shared_ptr<World> world) override;
};