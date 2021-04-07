#pragma once

#include "../../Step.h"
#include <frc/Servo.h>

using namespace std;


class UnlatchArmStep : public Step
{
public:
    UnlatchArmStep() {
    }

    bool Run(std::shared_ptr<World> world) override {
        std::cout << "UnlatchArmStep => Run()\n";
        if (firstRun) {
            firstRun = false;
            RobotMap::latchServo->SetAngle(180);
        }
        return true;
    }
private:
    bool firstRun = true;
};
