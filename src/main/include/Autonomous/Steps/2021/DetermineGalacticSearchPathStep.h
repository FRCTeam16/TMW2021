#pragma once

#include "../../Step.h"
#include "../../Strategies/2021/GalacticSearchAutoStrategy.h"
#include "Robot.h"


class DetermineGalacticSearchPathStep : public Step {
public:

    DetermineGalacticSearchPathStep(GalacticSearchAutoStrategy *parent,  std::shared_ptr<VisionSystem> visionSystem)
        : parent(parent), visionSystem(visionSystem)
    {
    }

    bool Run(std::shared_ptr<World> world) override
    {
        const bool hasParent = parent != nullptr;

        if (hasParent) cout << "DetermineGalacticSearchPathStep ==> Run\n";
        // Do our scan work to determine which path
        auto visionInfo = visionSystem->GetLastVisionInfo();
        if (hasParent) cout << "DetermineGalacticSearchPathStep ==> VisionInfo : " << visionInfo << " :\n";


    
        auto x = visionInfo ->xOffset;
        auto y = visionInfo ->yOffset;

        //parent ->RedA();
        //return true;

        if(x <= 10 && x >= -30) {
            if(x >= -10) {
                if (hasParent) {
                    parent ->RedA();
                    cout << "RedA\n"; 
                }
                SmartDashboard::PutString("GalacticSearch", "RedA");
            }
            else {
                SmartDashboard::PutString("GalacticSearch", "RedB");
                if (hasParent) {
                    parent -> RedB();
                    cout << "RedB\n";
                }
            }
        }     
        else {
            if (x > 18){
                if (hasParent) {
                    parent -> BlueA();
                    cout << "BlueA\n";
                }
                SmartDashboard::PutString("GalacticSearch", "BlueA");
                
            }

            else {
                if (hasParent) {
                    parent -> BlueB();
                    cout << "BlueB\n";
                }
                SmartDashboard::PutString("GalacticSearch", "BlueB");
            }
        }
        
        

        if (hasParent) parent->StopPath();
        return true;
    }

private:
    GalacticSearchAutoStrategy *parent;
    std::shared_ptr<VisionSystem> visionSystem;
};