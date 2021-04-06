#include "Autonomous/Strategies/2021/SlalomAutoStrategy.h"
#include "Autonomous/Steps/DriveToDistance.h"
#include "Autonomous/Steps/OpenDriveToDistance.h"
#include "Autonomous/Steps/SetGyroOffset.h"


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
    
	bool startTurned = SmartDashboard::GetBoolean("Slalom90", false);
	if (startTurned) {
		steps.push_back(new SetGyroOffset(90.0));	
	}
	steps.push_back(new OpenDriveToDistance(angle, 0.7, 0.0, 28.5, 1, 0.4));
    //steps.push_back(new DriveToDistance(angle, speed, 0_in, 42_in));
	steps.push_back(new DriveToDistance(angle, speed, -70_in, 15_in));
	auto rdStep = new OpenDriveToDistance(angle, 0.95, 0.0, 170,1,0.4);
	rdStep->SetRampMinSpeed(0.5);
	steps.push_back(rdStep);
	//steps.push_back(new OpenDriveToDistance(angle, 0.6, 0.0, 121, 2, 0.25, 30));
	steps.push_back(new DriveToDistance(angle, speed, 67_in, 25_in));
	steps.push_back(new DriveToDistance(angle, speed, 0_in, 72_in));
	steps.push_back(new DriveToDistance(angle, speed, -58_in, 0_in));
	steps.push_back(new DriveToDistance(angle, speed, 0_in, -45_in));


	steps.push_back(new DriveToDistance(angle, speed, 72_in, -33_in));
	//steps.push_back(new DriveToDistance(angle, speed, 69_in, 0_in));
	steps.push_back(new OpenDriveToDistance(angle, -0.95, 0.0, 140.0 ,1,0.4));
	steps.push_back(new DriveToDistance(angle, speed, -70_in, -17_in));
	steps.push_back(new DriveToDistance(angle, speed, 0_in, -58_in));

	// auto step  = new OpenDriveToDistance(angle, 0.6, 0.0, 181, 2, 0.25, 30)
}