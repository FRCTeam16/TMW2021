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
            Target(-3_ft,    5_ft, 0.5, yaw, 4_in),

            Target(-1_ft,     5_ft,   0.4, yaw, 3_in),
            Target(1.1_ft,   7.0_ft, 0.5, yaw, 3_in),

            Target(4.0_ft,  8_ft,   0.5, yaw, 3_in),
            Target(4.7_ft, 12.5_ft, 0.7, yaw, 4_in),

            // Second point
            Target(4.7_ft,   13.75_ft, 0.3, yaw, 3_in),
            Target(1_ft,     13.75_ft, 0.6, yaw, 3_in),
            Target(-3.25_ft,  14.25_ft, 0.7, yaw, 3_in),
    
            Target(4.0_ft,  14.75_ft, 0.7, yaw, 6_in),
            Target(4.75_ft,  20.00_ft, 0.7, yaw, 3_in),
            Target(4.75_ft,  22.25_ft, 0.5, yaw, 2_in),

            // Third point
            Target(-2.5_ft,  23.25_ft, 0.6, yaw, 4_in),
            Target(-3.0_ft,  23.25_ft, 0.6, yaw, 4_in),
            Target(-4_ft, 23.25_ft, 0.4, yaw, 3_in),

            // Exit
            // Starting to lose encoders here, so give it an extra boost
            Target(-0.5_ft, 24_ft, 0.6, yaw, 6_in),
            Target(0.0_ft, 30.0_ft, 0.5, yaw, 2_in),
        });
        steps.push_back(path);
    }

private:

};