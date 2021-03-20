#include "Autonomous/Steps/2021/PathFinderStep.h"
#include "Robot.h"

bool PathFinderStep::Run(std::shared_ptr<World> world)
{
    // Check for end condition
    if (targets.empty() && finishedPath)
    {
        std::cout << "Pathfinder empty, exiting";
        return true;    // Finished with step
    }

    // Handle first run initialization
    // Move to constructor?
    if (!started) {
        std::cout << "Pathfinder -> first time through\n";
        currentTarget = targets.front();
        Robot::driveBase->SetTargetAngle(currentTarget.angle.to<double>()); 
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

    std::cout << "Currnt: (" << curX << " | " << curY << ")\n";
    std::cout << "Target: (" << currentTarget.xpos << " | " << currentTarget.ypos << ")\n";
    std::cout << "Distance to target: " << distanceToTarget << "\n";

    // Check if we close enough to target to go to the next step
    if (distanceToTarget <= currentTarget.distance_threshold) {
        std::cout << "PathFinderStep met threshold";

        if (targets.empty()) {
            finishedPath = true;
        } else {
            currentTarget = targets.front();
            Robot::driveBase->SetTargetAngle(currentTarget.angle.to<double>()); 
            targets.pop();
            finishedPath = false;
        }
        return false;   // pickup next target next scan
    }

    // Calculate speed component parts
    double theta = atan2(dX.to<double>(), dY.to<double>());
    double ySpeed = (currentTarget.speed) * cos(theta);
    double xSpeed = (currentTarget.speed) * sin(theta);

    // TODO: Error correction

    // Perform drive
    const double twistOutput = Robot::driveBase->GetTwistControlOutput();
    crab->Update(
            (float) twistOutput,
            (float) ySpeed,
            (float) xSpeed,
            true);
    return false;

}