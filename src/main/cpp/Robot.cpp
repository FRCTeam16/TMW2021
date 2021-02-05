#include "Robot.h"
#include "OI.h"
#include "Util/BSPrefs.h" 
#include "Util/UtilityFunctions.h"
#include "Subsystems/Drive/TMW2019SwerveWheel.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/commands/Scheduler.h>
#include <wpi/PortForwarder.h>

std::unique_ptr<OI> Robot::oi;
std::shared_ptr<DriveBase> Robot::driveBase;
std::shared_ptr<VisionSystem> Robot::visionSystem;
std::shared_ptr<Turret> Robot::turret;
std::shared_ptr<FeederArm> Robot::feederArm;
std::shared_ptr<ControlPanelSystem> Robot::controlPanelSystem;

void Robot::RobotInit() {
	std::cout << "Robot::RobotInit => \n";

	std::cout << "Reading properties\n";
	auto pref = BSPrefs::GetInstance();
	std::cout << "Sanity FLOFF: " << pref->GetDouble("FLOff", 0.0);
	std::cout << "Finished Reading properties\n";

	robotMap.reset(new RobotMap());
	oi.reset(new OI());
    driveBase.reset(new DriveBase());
    statusReporter->Launch();
    dmsProcessManager.reset(new DmsProcessManager(statusReporter));

	autoManager.reset(new AutoManager());

	RobotMap::gyro->ZeroYaw();
	// wpi::PortForwarder::GetInstance().Add(5801, "10.0.16.11", 5801);

	std::cout << "Robot::TeleopInit <=\n";
}

void Robot::DisabledInit() {
	turret->GetTurretRotation().DisableVisionTracking();
	visionSystem->DisableVisionTracking();
}

void Robot::DisabledPeriodic() {
	frc::Scheduler::GetInstance()->Run();
	InstrumentSubsystems();
	HandleGlobalInputs();	
}

void Robot::AutonomousInit() {
	cout << "AutonomousInit\n";
	RobotMap::gyro->ZeroYaw();
	world.reset(new World());
	autoManager->Init(world);
	InitSubsystems();
	feederArm->InitAuto();
	driveBase->InitAuto();
}
void Robot::AutonomousPeriodic() {
	frc::Scheduler::GetInstance()->Run();
	autoManager->Periodic(world);
	RunSubsystems();
}

void Robot::TeleopInit() {
	InitSubsystems();
	driveBase->InitTeleop();
    std::cout << "Robot::TeleopInit <=\n";
}

void Robot::TeleopPeriodic() {
	// std::cout << "TeleopPeriodic\n";
    double startTime = frc::Timer::GetFPGATimestamp();
	frc::Scheduler::GetInstance()->Run();
	
	double threshold = 0.1;	// Used as general joystick deadband default
	// const bool lockWheels = oi->DL6->Pressed();  Removed for auto testing
	const bool lockWheels = false;

	const OI::DPad dPad = oi->GetGamepadDPad();
	const bool startButtonPressed = oi->GPStart->Pressed();
	frc::SmartDashboard::PutBoolean("Start Button Pressed", startButtonPressed);

	HandleGlobalInputs();

	/**********************************************************
	 * Testing and Diagnostics
	**********************************************************/
	const bool dmsMode = oi->DL14->Pressed();
	dmsProcessManager->SetRunning(dmsMode);

	
	/**********************************************************
	 * Drive Control
	**********************************************************/
	double twistInput = oi->GetJoystickTwist(threshold);
	double start = frc::Timer::GetFPGATimestamp();

	// Lock angle
	if (oi->DL2->Pressed()) {
		driveBase->SetTargetAngle(0.0);
		twistInput = driveBase->GetTwistControlOutput();
	}
	if (dmsMode) {
		// DriveBase input handled via DMS->Run()
	} else {
		if (!lockWheels) {
			double yMove = -oi->GetJoystickY(threshold);
			double xMove = oi->GetJoystickX();
			bool useGyro = true;
			if (oi->DR4->Pressed()) {
				// robot centric
				// xMove = std::copysign(xMove*xMove, xMove);
				// twistInput *= 0.5;
				useGyro = false;
			}
			driveBase->Crab(
				twistInput,
				yMove,
				xMove,
				useGyro);
		} else {
			driveBase->Crab(0, 0, 0, true);
		}
	}
	

	double now = frc::Timer::GetFPGATimestamp();
	double driveBaseTime = (now-start) * 1000;
	SmartDashboard::PutNumber("DriveBaseRun", driveBaseTime);
	RunSubsystems();
	InstrumentSubsystems();

	double elapsed = (frc::Timer::GetFPGATimestamp() - startTime) * 1000.0;
	SmartDashboard::PutNumber("Teleop Period (ms)", elapsed);
	SmartDashboard::PutNumber("Non-DriveBase Time (ms)", (elapsed - driveBaseTime));
}	


void Robot::InitSubsystems() {
    std::cout << "Robot::InitSubsystems =>\n";
	// status & dms currently don't have init
	std::cout << "Robot::InitSubsystems <=\n";
}

void Robot::RunSubsystems() {
	// std::cout << "RunSubsystems() =>\n";
	double start = frc::Timer::GetFPGATimestamp();
	// double t1 = start;
    dmsProcessManager->Run();
	// double t2 = frc::Timer::GetFPGATimestamp();
	// std::cout << "Time DMS   : " << fabs(t2 - t1) << "\n";
	double now = frc::Timer::GetFPGATimestamp();
	SmartDashboard::PutNumber("Subsystem Times", (now-start) * 1000);
	// std::cout << "RunSubsystems() <=\n";
}

void Robot::InstrumentSubsystems() {
	autoManager->Instrument();
	if (true || runInstrumentation) {
		RobotMap::gyro->Instrument();
		driveBase->Instrument();
	}
}

void Robot::HandleGlobalInputs() {
	// Only run instrumentation when button is pressed to avoid
	// network latency overhead
	runInstrumentation = oi->DL7->Pressed();
}


void Robot::TestInit() {}
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif

