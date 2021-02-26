#pragma once

#include <units/length.h>
#include "EncoderWheel.h"
#include "RobotMap.h"
#include <cmath>

class LocalMap
{
public:

    inch_t GetX() const { return field_x; }

    inch_t GetY() const { return field_y; }

    void UpdateFieldPosition()
    {
        // TODO:

        // update map x,y
        double yaw = RobotMap::gyro->GetYaw();
        double curx = encoderWheel->GetX();
        double cury = encoderWheel->GetY();
        
        double diffx = curx - field_x;
        double diffy = cury - field_y;

        double absyaw = fabs(yaw);
        if (absyaw != 0 && absyaw != 90 && absyaw != 180)
        {
            double actual_x_diff = sin(yaw) * diffx;
            double acutal_y_diff = cos(yaw) * diffy;

            field_x += actual_x_diff;
            field_y += acutal_y_diff
        } 
        else if (fabs(yaw) == 90) {
            
        } else {
            field_x = curx;
            field_y = cury;
        }
        
    }
    

private:
    std::shared_ptr<EncoderWheel> encoderWheel;
    inch_t field_y = inch_t{0.0};
    inch_t field_x = inch_t{0.0};
};