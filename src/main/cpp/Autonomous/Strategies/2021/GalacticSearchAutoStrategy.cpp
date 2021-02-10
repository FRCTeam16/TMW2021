#include "Autonomous/Strategies/2021/GalacticSearchAutoStrategy.h"
#include "Autonomous/Steps/DriveToDistance.h"
#include "Autonomous/Steps/OpenDriveToDistance.h"
#include "Autonomous/Steps/SetGyroOffset.h"


GalacticSearchAutoStrategy::GalacticSearchAutoStrategy(std::shared_ptr<World> world) {
	std::cout << "--- GalacticSearch Autonomous ---\n";
}

void GalacticSearchAutoStrategy::Init(std::shared_ptr<World> world) {
	std::cout << "GalacticSearchAutoStrategy::Init()\n";
	const double speed = 0.50;
	const double angle = 0.0;
    
	//steps.push_back(new OpenDriveToDistance(angle, 0.5, 0.0, 41.5, 1, 0.4));
	//steps.push_back(new DriveToDistance(angle, speed, -75_in, 26_in));
}


GalacticSearchAutoStrategy::DetectedPath GalacticSearchAutoStrategy::DetectPath() { return kUnknown; }
void GalacticSearchAutoStrategy::RedA() {}
void GalacticSearchAutoStrategy::RedB() {}
void GalacticSearchAutoStrategy::BlueA() {}
void GalacticSearchAutoStrategy::BlueB() {}