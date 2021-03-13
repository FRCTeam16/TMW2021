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
        double curx = encoderWheel->GetX().to<double>();
        double cury = encoderWheel->GetY().to<double>();
        
        double theta = yaw * DEG_TO_RAD;
        double diffx = curx - field_x;
        double diffy = cury - field_y;

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
            double x = diffx;
            double y = diffy;
            double actual_x = (x * cos(theta)) - (y * sin(theta));
            double actual_y = (x * sin(theta)) + (y * cos(theta));

            field_x += inch_t{actual_x};
            field_y += inch_t{actual_y};
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