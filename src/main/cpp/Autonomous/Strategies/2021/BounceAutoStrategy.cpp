#include "Autonomous/Strategies/2021/BounceAutoStrategy.h"
#include "Autonomous/Steps/DriveToDistance.h"
#include "Autonomous/Steps/OpenDriveToDistance.h"
#include "Autonomous/Steps/SetGyroOffset.h"


BounceAutoStrategy::BounceAutoStrategy(std::shared_ptr<World> world) {
	std::cout << "--- Bounce Autonomous ---\n";
}

void BounceAutoStrategy::Init(std::shared_ptr<World> world) {
	std::cout << "BounceAutoStrategy::Init()\n";
	const double speed = 0.50;
	const double angle = 0.0;
    
	//steps.push_back(new OpenDriveToDistance(angle, 0.5, 0.0, 41.5, 1, 0.4));
	//steps.push_back(new DriveToDistance(angle, speed, -75_in, 26_in));
}