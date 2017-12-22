/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "CtrlSys/MotionProfile.h"

namespace frc {

/**
 * Provides trapezoidal velocity control.
 *
 * Constant acceleration until target (max) velocity is reached, sets
 * acceleration to zero for a calculated time, then decelerates at a constant
 * acceleration with a slope equal to the negative slope of the initial
 * acceleration.
 */
class TrapezoidProfile : public MotionProfile {
 public:
  TrapezoidProfile(double maxV, double timeToMaxV);
  virtual ~TrapezoidProfile() = default;

  virtual void SetGoal(double goal, double currentSource = 0.0);

  void SetMaxVelocity(double velocity);
  double GetMaxVelocity() const;
  void SetTimeToMaxV(double timeToMaxV);

 protected:
  virtual State UpdateSetpoint(double currentTime);

 private:
  double m_acceleration;
  double m_velocity;
  double m_profileMaxVelocity;
  double m_timeFromMaxVelocity;
  double m_timeToMaxVelocity;
  double m_sign;
};

}  // namespace frc
