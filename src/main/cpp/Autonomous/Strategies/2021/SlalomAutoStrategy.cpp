#include "Autonomous/Strategies/2021/SlalomAutoStrategy.h"
#include "Autonomous/Steps/DriveToDistance.h"
#include "Autonomous/Steps/OpenDriveToDistance.h"


SlalomAutoStrategy::SlalomAutoStrategy(std::shared_ptr<World> world) {
	// SlalomSimple();
	// Measure();
	std::cout << "--- Slalom Autonomous ---\n";
}

void SlalomAutoStrategy::Init(std::shared_ptr<World> world) {
	std::cout << "SlalomAutoStrategy::Init()\n";
	// AutoStartPosition startPosition = world->GetStartPosition();
	auto xmove = 62_in;
	auto ymove = 180_in; 
	const double speed = 0.50;
	const double angle = 0.0;
	steps.push_back(new OpenDriveToDistance(angle, 0.5, 0.0, 40.7, 1, 0.4));
	// steps.push_back(new DriveToDistance(angle, speed, 0_in, 40.7_in));
	steps.push_back(new DriveToDistance(angle, speed, -62_in, 36_in));
	steps.push_back(new DriveToDistance(angle, speed, 0_in, 140.7_in));
	//steps.push_back(new OpenDriveToDistance(angle, 0.6, 0.0, 121, 2, 0.25, 30));
	steps.push_back(new DriveToDistance(angle, speed, 62_in, 36_in));
	steps.push_back(new DriveToDistance(angle, speed, 0_in, 54.3_in));
	steps.push_back(new DriveToDistance(angle, speed, -62_in, 0_in));
	steps.push_back(new DriveToDistance(angle, speed, 0_in, -60_in));
	steps.push_back(new DriveToDistance(angle, speed, 62_in, 0_in));
	steps.push_back(new DriveToDistance(angle, speed, 0_in, -181_in));
	steps.push_back(new DriveToDistance(angle, speed, -62_in, 0_in));
	steps.push_back(new DriveToDistance(angle, speed, 0_in, -60_in));

	// auto step  = new OpenDriveToDistance(angle, 0.6, 0.0, 181, 2, 0.25, 30)
}