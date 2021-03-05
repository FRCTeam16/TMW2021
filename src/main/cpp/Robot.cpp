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
std::shared_ptr<EncoderWheel> Robot::encoderWheel;

void Robot::RobotInit() {
	std::cout << "Robot::RobotInit => \n";

	std::cout << "Reading properties\n";
	auto pref = BSPrefs::GetInstance();
	std::cout << "Sanity FLOFF: " << pref->GetDouble("FLOff", 0.0);
	std::cout << "Finished Reading properties\n";

	robotMap.reset(new RobotMap());
	oi.reset(new OI());
    driveBase.reset(new DriveBase());
	std::cout << "Robot::RobotInit after driveBase\n";
	visionSystem.reset(new VisionSystem());

	statusReporter.reset(new StatusReporter());
    statusReporter->Launch();
    dmsProcessManager.reset(new DmsProcessManager(statusReporter));

	std::cout << "- before automgr\n";
	autoManager.reset(new AutoManager());
	std::cout << "- before automgr\n";

	std::cout << "- before zeroyaw\n";
	RobotMap::gyro->ZeroYaw();
	std::cout << "- after zeroyaw\n";
	// wpi::PortForwarder::GetInstance().Add(5801, "10.0.16.11", 5801);

	SmartDashboard::PutBoolean("Slalom90", false);

	encoderWheel.reset(new EncoderWheel(RobotMap::driveEncoderX, RobotMap::driveEncoderY));
	SmartDashboard::PutString("GalacticSearch", "Unknown");

	std::cout << "Robot::RobotInit <=\n";
}

void Robot::DisabledInit() {
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
	visionSystem->Run();	//hack
	autoManager->Init(world);
	InitSubsystems();
	driveBase->InitAuto();
}
void Robot::AutonomousPeriodic() {
	frc::Scheduler::GetInstance()->Run();
	autoManager->Periodic(world);
	RunSubsystems();
}

void Robot::TeleopInit() {
	InitSubsystems();
	std::cout << "Robot::TelopInit => driveBase->Init";
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
	 * Driver Control
	**********************************************************/
	if  (  oi-> DR1 -> Pressed() ) {
		 RobotMap :: intakeMotor -> Set(1.0);
	}
	else if ( oi->DR2 -> Pressed() ) {
		RobotMap :: intakeMotor -> Set(-1.0);
		
	} else {
		RobotMap :: intakeMotor -> Set(0.0);
	}

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
	else if( oi->DL3-> Pressed()) {
		driveBase->SetTargetAngle(-90.0);
		twistInput = driveBase->GetTwistControlOutput();
		
	}

	else if( oi->DL4->Pressed()) {
		driveBase->SetTargetAngle(90.0);
		twistInput = driveBase->GetTwistControlOutput();
	}

	



	if (dmsMode) {
		// DriveBase input handled via DMS->Run()
	} else {
		if (!lockWheels) {
			double yMove = -oi->GetJoystickY(threshold);
			double xMove = oi->GetJoystickX();
			bool useGyro = true;

			if ( oi->DL1->Pressed()) {
				double x = fabs(xMove);
				double y = fabs(yMove);
				

				if( x < y) {
					xMove = 0;
				}
				else {
					yMove = 0;
				}
			}
	
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
	visionSystem->Init();
	std::cout << "Robot::InitSubsystems <=\n";
}

void Robot::RunSubsystems() {
	// std::cout << "RunSubsystems() =>\n";
	double start = frc::Timer::GetFPGATimestamp();
	visionSystem->Run();
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
		SmartDashboard::PutNumber("XEnc", encoderWheel->GetX().to<double>());
		SmartDashboard::PutNumber("YEnc", encoderWheel->GetY().to<double>());
	}
	SmartDashboard::GetBoolean("Slalom90", false);
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

