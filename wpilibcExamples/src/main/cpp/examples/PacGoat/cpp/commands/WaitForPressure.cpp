/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2019 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/WaitForPressure.h"

#include "Robot.h"

WaitForPressure::WaitForPressure() { Requires(&Robot::pneumatics); }

// Make this return true when this Command no longer needs to run execute()
bool WaitForPressure::IsFinished() { return Robot::pneumatics.IsPressurized(); }
