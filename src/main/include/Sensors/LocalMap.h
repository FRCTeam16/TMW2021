#pragma once

#include <units/length.h>
#include "EncoderWheel.h"
#include "RobotMap.h"
#include <cmath>

class LocalMap
{
public:
    LocalMap(std::shared_ptr<EncoderWheel> wheel) 
    : encoderWheel(wheel)
    {
    }

    inch_t GetX() const { return field_x; }

    inch_t GetY() const { return field_y; }

    void UpdateFieldPosition()
    {
        // update map x,y
        double yaw = RobotMap::gyro->GetYaw();
        inch_t curx = encoderWheel->GetX();
        inch_t cury = encoderWheel->GetY();
        
        inch_t diffx = curx - field_x;
        inch_t diffy = cury - field_y;
    
        double absyaw = fabs(yaw);        
        if (!AreSame(fmod(absyaw, 90.0), 0.0))
        {
            // general case
            inch_t actual_x_diff = sin(yaw) * diffx;
            inch_t acutal_y_diff = cos(yaw) * diffy;

            field_x += actual_x_diff;
            field_y += acutal_y_diff;
        } 
        else if (AreSame(absyaw,  90))
        {
            int mul = AreSame(yaw, -90) ? -1 : 1;
            field_x += (mul * diffy);
            field_y += (-1 * mul * diffx);
        } 
        else
        {
            // we are at 0 or +/- 180
            int mul = AreSame(yaw, -180) ? -1 : 1;
            field_x += (mul * diffx);
            field_y += (mul * diffy);
        } 
    }
    

private:
    std::shared_ptr<EncoderWheel> encoderWheel;
    inch_t field_y = inch_t{0.0};
    inch_t field_x = inch_t{0.0};

    bool AreSame(double a, double b, double epsilon = 0.01)
    {
        return fabs(a-b) < epsilon;
    }
};