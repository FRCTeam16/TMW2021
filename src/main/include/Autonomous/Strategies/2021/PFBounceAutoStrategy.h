#pragma once
#include "../../Strategy.h"

#include "../../Steps/2021/PathFinderStep.h"


class PFBounceAutoStrategy : public StepStrategy {
public:
	PFBounceAutoStrategy(std::shared_ptr<World> world) {}

	virtual ~PFBounceAutoStrategy() {}

	void Init(std::shared_ptr<World> world) override {
        const degree_t yaw = 0_deg;

        auto path = new PathFinderStep({
            Target(0_ft, 2_in, 0.1, yaw),
            Target(0_ft, 6_in, 0.2, yaw),
            Target(0_ft, 2.5_ft, 0.4, yaw),

            // First point
            Target(-3.0_ft, 5_ft, 0.4, yaw),
            Target(-3.5_ft, 5_ft, 0.2, yaw),
            Target(-3.0_ft, 5_ft, 0.2, yaw),
            Target(3.5_ft, 7.5_ft, 0.4, yaw),

            Target(3.5_ft, 14_ft, 0.4, yaw),

            // Second point
            Target(-3.5_ft, 16.5_ft, 0.4, yaw),
            Target(3.5_ft, 19_ft, 0.4, yaw),
            Target(3.5_ft, 25.5_ft, 0.4, yaw),

            // Third point
            Target(-3.5_ft, 28_ft, 0.4, yaw),
            Target(0_ft, 30.5_ft, 0.4, yaw),
            Target(0_ft, 25.5_ft, 0.4, yaw)
        });
        steps.push_back(path);
    }

private:
};