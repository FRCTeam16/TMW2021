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

    inch_t GetX() const { return field_x; }

    inch_t GetY() const { return field_y; }

    void UpdateFieldPosition()
    {
        // update map x,y
        double yaw = RobotMap::gyro->GetYaw();
        inch_t curx = encoderWheel->GetX();
        inch_t cury = encoderWheel->GetY();
        
        double theta = yaw * DEG_TO_RAD;
        inch_t diffx = curx - field_x;
        inch_t diffy = cury - field_y;

        if (false) {
            // dumb ignoring angle
            field_x += diffx;
            field_y += diffy;
        } else {
            /**
             * t = difference between angles
             * x' = x cos(t) - y sin(t)
             * y' = x sin(t) + y cos(t)
             */
            inch_t actual_x = (diffx * cos(theta)) - (diffy * sin(theta));
            inch_t actual_y = (diffx * sin(theta)) - (diffy * cos(theta));

            field_x += actual_x;
            field_y += actual_y;
        }
    }

    void Zero() {
        encoderWheel->Zero();
        field_y = inch_t{0.0};
        field_x = inch_t{0.0};
    }
    

private:
    const double DEG_TO_RAD = M_PI / 180.0;
    std::shared_ptr<EncoderWheel> encoderWheel;
    inch_t field_y = inch_t{0.0};
    inch_t field_x = inch_t{0.0};

    bool AreSame(double a, double b, double epsilon = 0.01)
    {
        return fabs(a-b) < epsilon;
    }
};