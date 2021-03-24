#include "Autonomous/Strategies/2021/BarrelRaceAutoStrategy.h"
#include "Autonomous/Steps/DriveToDistance.h"
#include "Autonomous/Steps/OpenDriveToDistance.h"
#include "Autonomous/Steps/SetGyroOffset.h"


BarrelRaceAutoStrategy::BarrelRaceAutoStrategy(std::shared_ptr<World> world) {
	std::cout << "--- BarrelRace Autonomous ---\n";
}

void BarrelRaceAutoStrategy::Init(std::shared_ptr<World> world) {
	std::cout << "BarrelRaceAutoStrategy::Init()\n";
	const double speed = 0.50;
	const double angle = 0.0;

	steps.push_back(new DriveToDistance(angle,speed,0_in,150_in));

	// Going around first point
	steps.push_back(new DriveToDistance(angle,speed,50_in,0_in));
	steps.push_back(new DriveToDistance(angle,speed,0_in,-45_in));
	steps.push_back(new DriveToDistance(angle,speed,-50_in,0_in));


	steps.push_back(new DriveToDistance(angle,speed,-60_in,150_in));
	steps.push_back(new DriveToDistance(angle,speed,-35_in,0_in));
	steps.push_back(new DriveToDistance(angle,speed,0_in,-40_in));
	steps.push_back(new DriveToDistance(angle,speed,35_in,0_in));
	steps.push_back(new DriveToDistance(angle,speed,90_in,90_in));
	steps.push_back(new DriveToDistance(angle,speed,-35_in,0_in));
	steps.push_back(new OpenDriveToDistance(angle,-0.7,0,240,1,0.4));

  
	//steps.push_back(new OpenDriveToDistance(angle, 0.5, 0.0, 41.5, 1, 0.4));
    //steps.push_back(new DriveToDistance(angle, speed, 0_in, 42_in));
}