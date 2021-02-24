#pragma once

#include "Autonomous/Step.h"
#include "Subsystems/Drive/FrontTwoAveragingDriveEncoderPIDSource.h"

class OpenDriveToDistance : public Step {
public:
  explicit OpenDriveToDistance(double _angle, double y, double x, double distance, double distanceThreshold,
    double rampUpTime = -1, double rampDownDist = -1,  double timeOut = -1);
  bool Run(std::shared_ptr<World> world) override;

  void SetRampMinSpeed(double rms) { rampMinSpeed = rms; }

private:
  const double angle;
  const double ySpeed;
  const double xSpeed;
  const double distance;
  const double distanceThreshold;
  const double rampUpTime;
  const double rampDownDist;
  double rampMinSpeed = -1.0;
  const double timeOut;
  double startTime = -1;

  std::unique_ptr<FrontTwoAveragingDriveEncoderPIDSource> encoder;
};
