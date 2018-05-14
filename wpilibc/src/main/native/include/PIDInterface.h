/*----------------------------------------------------------------------------*/
/* Copyright (c) 2016-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

namespace frc {

class PIDInterface {
  virtual void SetPID(double p, double i, double d) = 0;
  virtual double GetP() const = 0;
  virtual double GetI() const = 0;
  virtual double GetD() const = 0;

  virtual void SetSetpoint(double setpoint) = 0;
  virtual double GetSetpoint() const = 0;

  /**
   * Allows the control loop to run
   */
  virtual void Enable() = 0;

  /**
   * Stops the control loop from running until explicitly re-enabled by calling
   * enable()
   */
  virtual void Disable() = 0;

  virtual bool IsEnabled() const = 0;

  virtual void Reset() = 0;
};

}  // namespace frc
