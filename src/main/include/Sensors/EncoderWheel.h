#pragma once

#include <frc/Encoder.h>
#include <units/length.h>
#include <units/velocity.h>
#include <cmath>

#include "Util/BSPrefs.h"


#define M_PI		3.14159265358979323846	/* pi */


using namespace units::length; 
using namespace units::dimensionless;
using namespace units::velocity;

/*UNIT_ADD(velocity, inches_per_second, inches_per_second, ips,
    units::compound_unit<units::length::inch, inverse<units::time::seconds>>)
*/

class EncoderWheel
{
public:

    EncoderWheel(std::shared_ptr<frc::Encoder> xenc, std::shared_ptr<frc::Encoder> yenc)
        : xEncoder(xenc), yEncoder(yenc)
    {
        // DPP: 1/pulses_per_rot * circumference
        // circumference = 2PI * R in inches
        const double wheel_radius = 1.0;
        inch_t circumference = inch_t{ TWO_PI * wheel_radius };
        const double encoder_rate = 2048.0;

        scalar_t inv_pulses_per_rotation { 1. / encoder_rate };
        inch_t dpp =  inv_pulses_per_rotation * circumference;
        auto prefs = BSPrefs::GetInstance();

        xEncoder->SetDistancePerPulse(prefs->GetDouble("DriveEncoder.X.DPP", dpp.to<double>()));
        yEncoder->SetDistancePerPulse(prefs->GetDouble("DriveEncoder.Y.DPP", dpp.to<double>()));        
    }

    inch_t GetX() const {
        return inch_t{xEncoder->GetDistance()};
    }

    inch_t GetY() const {
        return inch_t{yEncoder->GetDistance()};
    }

    void Zero() {
        xEncoder->Reset();
        yEncoder->Reset();
    }

/*
TODO: fix macro for custom velocity
    inches_per_second_t GetXRate() const {
        return inches_per_second_t{xEncoder->GetRate()};
    }

    inches_per_second_t GetYRate() const {
        return inches_per_second_t{yEncoder->GetRate()};
    }
*/
private:
    constexpr static double TWO_PI = 2 * M_PI;
    std::shared_ptr<frc::Encoder> xEncoder;
    std::shared_ptr<frc::Encoder> yEncoder;
};