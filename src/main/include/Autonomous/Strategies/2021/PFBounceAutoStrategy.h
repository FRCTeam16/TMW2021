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
            Target(0_ft, 2_in, 0.1, yaw, 2_in),
            Target(0_ft, 6_in, 0.4, yaw, 2_in),
            Target(0_ft, 2.5_ft, 0.6, yaw, 2_in),

            // First point
            Target(-3.0_ft,  5_ft, 0.6, yaw, 3_in),
            Target(-3.25_ft, 5_ft, 0.4, yaw, 3_in),
            Target(-3.5_ft,  5_ft, 0.2, yaw),
            Target(-3_ft,    5_ft, 0.4, yaw, 4_in),

            Target(0_ft,    5_ft, 0.5, yaw, 4_in),
            Target(4.5_ft,  6.5_ft, 0.6, yaw, 5_in),
            Target(4.5_ft, 14_ft, 0.5, yaw, 3_in),

            // Second point
            Target(-3.0_ft,  14_ft, 0.6, yaw, 4_in),
            Target(-3.25_ft, 14_ft, 0.4, yaw, 3_in),
            Target(-3.5_ft,  14_ft, 0.2, yaw),
            Target(-3.25_ft, 14_ft, 0.4, yaw, 4_in),

            Target(4.5_ft, 15_ft, 0.4, yaw, 4_in),
            Target(4.5_ft, 22.5_ft, 0.4, yaw, 5_in),

            // Third point
            Target(-3.0_ft,  22.5_ft, 0.6, yaw, 4_in),
            Target(-3.25_ft, 22.5_ft, 0.4, yaw, 3_in),
            Target(-3.5_ft,  22.5_ft, 0.2, yaw),

            // Exit
            Target(0_ft, 23_ft, 0.3, yaw, 5_in),
            Target(0_ft, 25.0_ft, 0.4, yaw, 5_in),
            Target(0_ft, 30.5_ft, 0.4, yaw),
        });
        steps.push_back(path);
    }

private:
};