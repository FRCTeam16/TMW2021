#pragma once

#include <units/length.h>
#include "EncoderWheel.h"
#include "RobotMap.h"
#include <cmath>

#define M_PI		3.14159265358979323846	/* pi */

class LocalMap
{
public:
    LocalMap(std::shared_ptr<EncoderWheel> wheel) 
    : encoderWheel(wheel)
    {
    }

    inch_t GetX() const { return inch_t(field_x); }

    inch_t GetY() const { return inch_t(field_y); }

    void UpdateFieldPosition()
    {
        // update map x,y
        const double encY = encoderWheel->GetY().to<double>();
        const double encX = encoderWheel->GetX().to<double>();

        double yaw = RobotMap::gyro->GetYaw();
        double diffx = encX - curx;
        double diffy = encY - cury;
        curx = encX;
        cury = encY;
        
        double theta = -yaw * DEG_TO_RAD;
        
        if (false) {
            // dumb ignoring angle
            // field_x += diffx;
            // field_y += diffy;
        } else {
            /**
             * t = difference between angles
             * x' = x cos(t) - y sin(t)
             * y' = x sin(t) + y cos(t)
             */
            double x = diffx;
            double y = diffy;
            double actual_x = (x * cos(theta)) - (y * sin(theta));
            double actual_y = (x * sin(theta)) + (y * cos(theta));

            field_x = field_x + actual_x;
            field_y = field_y + actual_y;
        }
    }

    void Zero() {
        encoderWheel->Zero();
        field_y = 0.0;
        field_x = 0.0;
        curx = 0.0;
        cury = 0.0;
    }
    

private:
    const double DEG_TO_RAD = M_PI / 180.0;
    std::shared_ptr<EncoderWheel> encoderWheel;
    double field_y = 0.0;
    double field_x = 0.0;
    double curx = 0.0;
    double cury = 0.0;

    bool AreSame(double a, double b, double epsilon = 0.01)
    {
        return fabs(a-b) < epsilon;
    }
};