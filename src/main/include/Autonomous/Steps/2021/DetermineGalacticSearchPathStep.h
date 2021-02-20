#pragma once

#include "../../Step.h"
#include "../../Strategies/2021/GalacticSearchAutoStrategy.h"
#include "Robot.h"

class DetermineGalacticSearchPathStep : public Step {
public:

    DetermineGalacticSearchPathStep(GalacticSearchAutoStrategy *parent)
        : parent(parent)
    {
    }

    bool Run(std::shared_ptr<World> world) override
    {
        // Do our scan work to determine which path
        auto visionInfo = Robot::visionSystem->GetLastVisionInfo();
    
        auto x = visionInfo ->xOffset;
        auto y = visionInfo ->yOffset;

        if(x <= -5 && x >= -35) {
            if(x >= -14) {
                parent ->RedA();
            }
            else {
                parent -> RedB();
            }
        }
             
        else {
           
            if (x < 10){
                parent -> BlueA();
            }

            else {
                parent -> BlueB();
            }
        }
        
        


        parent->RedA();
        return false;
    }

private:
    GalacticSearchAutoStrategy *parent; 
};