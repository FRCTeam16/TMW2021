#include "RobotMap.h"
#include "Gyro/PigeonBSGyro.h"
#include "Gyro/NavXBSGyro.h"

  shared_ptr<rev::CANSparkMax> RobotMap::driveBaseFrontLeftDrive;
  shared_ptr<WPI_TalonSRX> RobotMap::driveBaseFrontLeftSteer;
  shared_ptr<rev::CANSparkMax> RobotMap::driveBaseFrontRightDrive;
  shared_ptr<WPI_TalonSRX> RobotMap::driveBaseFrontRightSteer;
  shared_ptr<rev::CANSparkMax> RobotMap::driveBaseRearLeftDrive;
  shared_ptr<WPI_TalonSRX> RobotMap::driveBaseRearLeftSteer;
  shared_ptr<rev::CANSparkMax> RobotMap::driveBaseRearRightDrive;
  shared_ptr<WPI_TalonSRX> RobotMap::driveBaseRearRightSteer;

  shared_ptr<WPI_TalonFX> RobotMap::armMotor;
  shared_ptr<WPI_TalonFX> RobotMap::armMotorFollower;

  shared_ptr<rev::CANSparkMax> RobotMap::turretMotor;
  shared_ptr<rev::CANSparkMax> RobotMap::shooterMotor;
  shared_ptr<rev::CANSparkMax> RobotMap::shooterMotorFollower;
  shared_ptr<rev::CANSparkMax> RobotMap::feederMotor;

  shared_ptr<WPI_VictorSPX> RobotMap::intakeMotor;
  std::shared_ptr<BSGyro> RobotMap::gyro;
  
  std::shared_ptr<frc::Compressor> RobotMap::compressor;
  std::shared_ptr<frc::Solenoid> RobotMap::lidTop;
  std::shared_ptr<frc::Solenoid> RobotMap::climberLeftArm;
  std::shared_ptr<frc::Solenoid> RobotMap::climberRightArm;

  std::shared_ptr<frc::PowerDistributionPanel> RobotMap::powerDistributionPanel;


RobotMap::RobotMap() {
  driveBaseFrontLeftDrive.reset(new rev::CANSparkMax{1, rev::CANSparkMax::MotorType::kBrushless});
  driveBaseFrontRightDrive.reset(new rev::CANSparkMax{3, rev::CANSparkMax::MotorType::kBrushless});
  driveBaseRearLeftDrive.reset(new rev::CANSparkMax{5, rev::CANSparkMax::MotorType::kBrushless});
  driveBaseRearRightDrive.reset(new rev::CANSparkMax{7, rev::CANSparkMax::MotorType::kBrushless});

  driveBaseFrontLeftSteer.reset(new WPI_TalonSRX{2});
  driveBaseFrontRightSteer.reset(new WPI_TalonSRX{4});
  driveBaseRearLeftSteer.reset(new WPI_TalonSRX{6});
  driveBaseRearRightSteer.reset(new WPI_TalonSRX{8});

  // auto concreteGyro = std::unique_ptr<PigeonBSGyro>(new PigeonBSGyro(intakeMotor.get()));
  auto concreteGyro = std::unique_ptr<NavXBSGyro>(new NavXBSGyro(frc::I2C::Port::kMXP));
  gyro = std::move(concreteGyro); 

  compressor.reset(new frc::Compressor{0});
  compressor->SetClosedLoopControl(true);

  powerDistributionPanel.reset(new frc::PowerDistributionPanel{0});
}
