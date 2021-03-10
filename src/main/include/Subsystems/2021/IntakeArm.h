#pragma once

#include "Subsystems/SubsystemManager.h"
#include "RobotMap.h"

class IntakeArm: public SubsystemManager {
public:

	void Run() override
    {
        double speed = 0.0;
        if (intakeEnabled) {
            speed = (intakeReversed) ? -1 * intakeSpeed : intakeSpeed;
        }
        RobotMap::intakeMotor->Set(speed);
    }

    void EnableIntake(bool reversed = false) 
    { 
        intakeEnabled = true; 
        intakeReversed = reversed; 
    }

    void StopIntake() 
    { 
        intakeEnabled = false; 
    }

private:
    const double intakeSpeed = 1.0;
    bool intakeEnabled = false;
    bool intakeReversed = false;
};