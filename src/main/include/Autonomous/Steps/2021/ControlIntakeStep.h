#include "../../Step.h"
#include "Robot.h"

class ControlIntakeStep : public Step {
public:
    ControlIntakeStep(bool enable = true, bool reverse = false)
        : enabled(enable), reversed(reverse)
    {
    }

    bool Run(std::shared_ptr<World> world) override
    {
        Robot::intakeArm->EnableIntake(reversed);
        return true;
    }

private:
    bool enabled = false;
    bool reversed = false;
};