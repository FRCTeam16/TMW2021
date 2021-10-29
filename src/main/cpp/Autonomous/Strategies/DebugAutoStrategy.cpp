#include "Autonomous/Strategies/DebugAutoStrategy.h"
#include "Autonomous/Steps/ConcurrentStep.h"
#include "Autonomous/Steps/Delay.h"
#include "Autonomous/Steps/SetGyroOffset.h"
#include "Autonomous/Steps/ConcurrentStep.h"
#include "Autonomous/Steps/ClosedLoopDrive2.h"
#include "Autonomous/Steps/DriveToBump.h"
#include "Autonomous/Steps/Rotate.h"
#include "Autonomous/Steps/RotateUntilPast.h"
#include "Autonomous/Steps/TimedDrive.h"
#include "Autonomous/Steps/SetGyroOffset.h"
#include "Autonomous/Steps/VisionControlledDrive.h"
#include "Autonomous/Steps/DriveToTarget.h"
#include "Autonomous/Steps/StopAtTarget.h"
#include "Autonomous/Steps/OpenDriveToDistance.h"
#include "Autonomous/Steps/SetVisionLight.h"
#include "Autonomous/Steps/StopAtTargetCount.h"
#include "Autonomous/Steps/SelectVisionPipeline.h"
#include "Autonomous/Steps/AlignToTarget.h"

#include "Autonomous/Steps/DriveToDistance.h"
#include "Autonomous/Steps/AckermanDriveToAngle.h"

#include "Autonomous/Steps/2020/EnableIntake.h"
#include "Autonomous/Steps/2020/EnableShooter.h"
#include "Autonomous/Steps/2020/EnableFeeder.h"
#include "Autonomous/Steps/2020/EnableVisionTracking.h"
#include "Autonomous/Steps/2020/SetFeederArmPosition.h"
#include "Autonomous/Steps/2020/SetTurretPosition.h"

#include "Autonomous/Steps/2021/PathFinderStep.h"
#include "Autonomous/Steps/2021/UnlatchArmStep.h"

#include <units/length.h>

DebugAutoStrategy::DebugAutoStrategy(std::shared_ptr<World> world) {
	// DebugSimple();
	// Measure();
	std::cout << "--- DEBUG Autonomous ---\n";

	steps.push_back(new UnlatchArmStep());
	steps.push_back(new Delay(.75));
	steps.push_back(new TimedDrive(0.0, 0.3, 0.0, 1.0));

	// degree_t robot_yaw = -2.0_deg;
	// double speed = 0.2;
	
	//steps.push_back(new SetGyroOffset(90.0));
	
	// auto step = new PathFinderStep({
	// 	Target(0_ft, 5_ft, speed, robot_yaw),
	// 	Target(-5_ft, 5_ft, speed, robot_yaw),
	// 	Target(-5_ft, 0_ft, speed, robot_yaw),
	// 	Target(0_ft, 0_ft, speed, robot_yaw)
	// });
	// steps.push_back(new Rotate(robot_yaw.to<double>()));
	// steps.push_back(step);
}
	

void DebugAutoStrategy::Init(std::shared_ptr<World> world) {
	std::cout << "DebugAutoStrategy::Init()\n";
	// AutoStartPosition startPosition = world->GetStartPosition();
	auto xmove = 62_in;
	const int ymove = 180;
	const double speed = 0.50;
	const double angle = -90.0;
	// steps.push_back(new OpenDriveToDistance(angle, 0.5, 0.0, 40.7, 1, 0.3));
}

void DebugAutoStrategy::DebugSimple() {
	const double firstAngle = 45.0;
	steps.push_back(new ConcurrentStep({
		new Rotate(firstAngle),
		new SetTurretPosition(-111),
		new EnableIntake(true),
		new EnableShooter(false)
	}));
	steps.push_back(new DriveToDistance(firstAngle, 0.3, 0_in, 81_in));
	auto driveToBar = new DriveToDistance(firstAngle, 0.2, 0_in, 7_in);
	driveToBar->SetUseGyro(false);
	steps.push_back(new ConcurrentStep({
		driveToBar,
		new EnableVisionTracking(true),
		new EnableShooter(true)
	}));
	steps.push_back(driveToBar);
	const double secondAngle = 30.0;
	steps.push_back(new ConcurrentStep({
		new DriveToDistance(secondAngle, 0.2, -50_in, 110_in),
		new EnableFeeder(true)			
	}));
}

void DebugAutoStrategy::Measure() {
	steps.push_back(new DriveToDistance(0.0, 0.3, 0_in, 60_in));

	// const units::degree_t zero(0);
	// const units::degree_t fortyFive(45.0);

	// auto step = new AckermanDriveToAngle(units::degree_t(0), 0.2, 1.0, units::degree_t(45),units::degree_t(3.0), units::second_t(5.0));
	// auto step = new AckermanDriveToAngle(0, 0.2, 1, 45);
	// steps.push_back(step);

	
}
