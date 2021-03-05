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
        cout << "DetermineGalacticSearchPathStep ==> Run\n";
        // Do our scan work to determine which path
        auto visionInfo = Robot::visionSystem->GetLastVisionInfo();
        cout << "DetermineGalacticSearchPathStep ==> Vision : " << visionInfo << " :\n";


    
        auto x = visionInfo ->xOffset;
        auto y = visionInfo ->yOffset;

        if(x <= -5 && x >= -35) {
            if(x >= -14) {
                parent ->RedA();
                SmartDashboard::PutString("GalacticSearch", "RedA");
                cout << "RedA\n"; 
            }
            else {
                SmartDashboard::PutString("GalacticSearch", "RedB");
                parent -> RedB();
                cout << "RedB\n";
            }
        }
             
        else {
           
            if (x < 10){
                parent -> BlueA();
                SmartDashboard::PutString("GalacticSearch", "BlueA");
                cout << "BlueA\n";
            }

            else {
                parent -> BlueB();
                SmartDashboard::PutString("GalacticSearch", "BlueB");
                cout << "BlueB\n";
            }
        }
        
        


        
        return true;
    }

private:
    GalacticSearchAutoStrategy *parent; 
};