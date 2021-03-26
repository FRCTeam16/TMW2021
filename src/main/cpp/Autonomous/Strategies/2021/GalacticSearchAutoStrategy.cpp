#include "Autonomous/Strategies/2021/GalacticSearchAutoStrategy.h"
#include "Autonomous/Steps/DriveToDistance.h"
#include "Autonomous/Steps/OpenDriveToDistance.h"
#include "Autonomous/Steps/SetGyroOffset.h"	
#include "Autonomous/Steps/2021/DetermineGalacticSearchPathStep.h"
#include "Robot.h"
#include "Autonomous/World.h"

#include "Autonomous/Steps/2021/ControlIntakeStep.h"


GalacticSearchAutoStrategy::GalacticSearchAutoStrategy(std::shared_ptr<World> world) {
	std::cout << "--- GalacticSearch Autonomous ---\n";
}

void GalacticSearchAutoStrategy::Init(std::shared_ptr<World> world) {
	std::cout << "GalacticSearchAutoStrategy::Init()\n";
	steps.push_back(new ControlIntakeStep(true));
	steps.push_back(new DetermineGalacticSearchPathStep(this, Robot::visionSystem));
}


GalacticSearchAutoStrategy::DetectedPath GalacticSearchAutoStrategy::DetectPath() { return kUnknown; }
void GalacticSearchAutoStrategy::RedA() {
/*
	auto timer = world->GetClock();
	double starttime = -1;

	if(starttime < 0) {
		starttime = timer;
		RobotMap :: intakeMotor -> (-1.0);
	}

	*/

	steps.push_back(new OpenDriveToDistance(0.0, 0.5, 0.15, 60,1,0.4 ));
	steps.push_back(new DriveToDistance(0,0.5,30_in,70_in));
	steps.push_back(new DriveToDistance(-64.0,0.5,-130_in,64_in));
	steps.push_back(new OpenDriveToDistance(-64,0.7,0,150,1,0.4));

}
void GalacticSearchAutoStrategy::RedB() {


	steps.push_back(new OpenDriveToDistance(0.0,0.5,0,60,0.4));
	steps.push_back(new DriveToDistance(0,0.5,60_in,60_in));
	steps.push_back(new DriveToDistance(0,0.5,-60_in,60_in));
	steps.push_back(new DriveToDistance(0,0.5,60_in,60_in));
	steps.push_back(new OpenDriveToDistance(0.0,0.7,0,120,2,0.25));

}
void GalacticSearchAutoStrategy::BlueA() {


	steps.push_back(new OpenDriveToDistance(0.0, 0.5,0,150,1,0.4 ));
	steps.push_back(new DriveToDistance(-64.0,0.5,-60_in,30_in));
	steps.push_back(new DriveToDistance(0,0.5,30_in,60_in));
	steps.push_back(new OpenDriveToDistance(0.0,0.7,0,60,2,0.25));


}
void GalacticSearchAutoStrategy::BlueB() {

	steps.push_back(new OpenDriveToDistance(0.0,0.5,0,150,0.4));
	steps.push_back(new DriveToDistance(0,0.5,-60_in,60_in));
	steps.push_back(new DriveToDistance(0,0.5,60_in,60_in));
	steps.push_back(new DriveToDistance(0,0.5,-60_in,60_in));
	steps.push_back(new OpenDriveToDistance(0.0,0.7,0,120,2,0.25));

}

void GalacticSearchAutoStrategy::StopPath() {
	steps.push_back(new ControlIntakeStep(false));
}