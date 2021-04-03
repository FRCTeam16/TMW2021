#pragma once

#include "../../Step.h"
#include <frc/Servo.h>

using namespace std;


class UnlatchArmStep : public Step
{
public:
    UnlatchArmStep() {
        servo.SetAngle(0);  // start position
    }

    bool Run(std::shared_ptr<World> world) override {
        std::cout << "UnlatchArmStep => Run()\n";
        if (firstRun) {
            firstRun = false;
            servo.SetAngle(180);
        }
        return true;
    }
private:
    frc::Servo servo {0};
    bool firstRun = true;
};
