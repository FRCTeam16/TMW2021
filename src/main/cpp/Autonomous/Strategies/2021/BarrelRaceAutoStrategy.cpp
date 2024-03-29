#include "Autonomous/Strategies/2021/BarrelRaceAutoStrategy.h"
#include "Autonomous/Steps/DriveToDistance.h"
#include "Autonomous/Steps/OpenDriveToDistance.h"
#include "Autonomous/Steps/SetGyroOffset.h"


BarrelRaceAutoStrategy::BarrelRaceAutoStrategy(std::shared_ptr<World> world) {
	std::cout << "--- BarrelRace Autonomous ---\n";
}

void BarrelRaceAutoStrategy::Init(std::shared_ptr<World> world) {
	std::cout << "BarrelRaceAutoStrategy::Init()\n";
	const double speed = 0.7;
	const double angle = 0.0;

	steps.push_back(new DriveToDistance(angle,0.7,0_in,155_in));

	// Going around first point
	steps.push_back(new DriveToDistance(angle,speed,50_in,0_in));
	steps.push_back(new DriveToDistance(angle,speed,0_in,-50_in));
	steps.push_back(new DriveToDistance(angle,speed,-40_in,0_in));

	// Going around second point
	steps.push_back(new DriveToDistance(angle,0.8,-23_in,175_in)); 
	steps.push_back(new DriveToDistance(angle,speed,-48_in,0_in));
	steps.push_back(new DriveToDistance(angle,speed,0_in,-50_in));
	steps.push_back(new DriveToDistance(angle,speed,30_in,0_in));

	// Going around third point
	steps.push_back(new DriveToDistance(angle,0.8,80_in,80_in));
	steps.push_back(new DriveToDistance(angle,speed,0_in, 55_in));
	steps.push_back(new DriveToDistance(angle,speed,-53_in,0_in));
	steps.push_back(new OpenDriveToDistance(angle,-0.95,0,240,1,0.4));


	// Brake
	steps.push_back(new DriveToDistance(angle, 0.5, 0_in, 10_in));
	steps.push_back(new DriveToDistance(angle, 0.0, 0_in, 0_in)); 

  
	//steps.push_back(new OpenDriveToDistance(angle, 0.5, 0.0, 41.5, 1, 0.4));
    //steps.push_back(new DriveToDistance(angle, speed, 0_in, 42_in));
}