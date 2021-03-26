#pragma once

#include <iostream>

#include <frc/TimedRobot.h>
#include <frc/DigitalInput.h>

#include "ctre/Phoenix.h"
#include "rev/CANSparkMax.h"

#include "RobotMap.h"
#include "Subsystems/Drive/DriveBase.h"
#include "OI.h"
#include "DMS/DmsProcessManager.h"
#include "DMS/StatusReporter.h"
#include "Subsystems/Vision/VisionSystem.h"
#include "Subsystems/Turret/Turret.h"
#include "Autonomous/World.h"
#include "Autonomous/AutoManager.h"
#include "Subsystems/FeederArm/FeederArm.h"
#include "Poses/ShotPoses.h"
#include "Subsystems/Color/ControlPanelSystem.h"
#include "Sensors/EncoderWheel.h"
#include "Subsystems/2021/IntakeArm.h"

#include "Sensors/EncoderWheel.h"
#include "Sensors/LocalMap.h"

#include "Autonomous/Steps/2021/DetermineGalacticSearchPathStep.h"


class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;

  void DisabledInit() override;
  void DisabledPeriodic() override;

  void AutonomousInit() override;
  void AutonomousPeriodic() override;

  void TeleopInit() override;
  void TeleopPeriodic() override;

  void TestInit() override;
  void TestPeriodic() override;

  // Subsystems
  static std::shared_ptr<DriveBase> driveBase;
  static std::unique_ptr<OI> oi;
  static std::shared_ptr<VisionSystem> visionSystem;
  static std::shared_ptr<Turret> turret;
  static std::shared_ptr<FeederArm> feederArm;
  static std::shared_ptr<ControlPanelSystem> controlPanelSystem;
  static std::shared_ptr<EncoderWheel> encoderWheel;
  static std::shared_ptr<IntakeArm> intakeArm;
  static std::unique_ptr<LocalMap> localMap;


private:
  void InitSubsystems();
  void RunSubsystems();
  void InstrumentSubsystems();
  void HandleGlobalInputs();

  std::unique_ptr<RobotMap> robotMap;
  std::shared_ptr<StatusReporter> statusReporter;
  std::unique_ptr<DmsProcessManager> dmsProcessManager;
  std::unique_ptr<AutoManager> autoManager;
  
  std::shared_ptr<World> world;
  bool runInstrumentation = false;  // whether to run subsystem instrumentation

  // Operator input flags
  frc::DigitalInput toggleArmBreakModeButton{0};  

  // Debug
  DetermineGalacticSearchPathStep *determineGalacticSearchPathStep;
};
