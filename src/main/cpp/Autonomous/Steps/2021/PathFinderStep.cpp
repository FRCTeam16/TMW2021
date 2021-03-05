#include "Autonomous/Steps/2021/PathFinderStep.h"
#include "Robot.h"

bool PathFinderStep::Run(std::shared_ptr<World> world)
{
    // Check for end condition
    if (targets.empty() == 0)
    {
        return true;    // Finished with step
    }

    // Handle first run initialization
    // Move to constructor?
    if (!started) {
        currentTarget = targets.front();
        targets.pop();
        started = true;
    }

    // Fetch our current location on the field
    inch_t curX = Robot::localMap->GetX();
    inch_t curY = Robot::localMap->GetY();

    // Determine how far away from target we are
    inch_t dX = currentTarget.xpos - curX;
    inch_t dY = currentTarget.ypos - curY;
    inch_t distanceToTarget = inch_t{ sqrt(pow(dX.to<double>(), 2) + pow(dY.to<double>(), 2)) };

    // Check if we close enough to target to go to the next step
    if (distanceToTarget <= distance_threshold) {
        currentTarget = targets.front();
        targets.pop();
        return false;   // pickup next target next scan
    }

    // Calculate speed component parts
    double theta = atan2(dX.to<double>(), dY.to<double>());
    double ySpeed = (currentTarget.speed) * cos(theta);
    double xSpeed = (currentTarget.speed) * sin(theta);

    // TODO: Error correction

    // Perform drive
    Robot::driveBase->SetTargetAngle(currentTarget.angle);  // TODO: init only step pop
    const double twistOutput = Robot::driveBase->GetTwistControlOutput();
    crab->Update(
            (float) twistOutput,
            (float) ySpeed,
            (float) xSpeed,
            true);

}