/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "TimedRobot.h"

#include <stdint.h>

#include <HAL/HAL.h>

#include "Timer.h"
#include "Utility.h"
#include "WPIErrors.h"

using namespace frc;

void TimedRobot::StartCompetition() {
  RobotInit();

  // Tell the DS that the robot is ready to be enabled
  HAL_ObserveUserProgramStarting();

  m_expirationTime = Timer::GetFPGATimestamp() + m_period;
  UpdateAlarm();

  // Loop forever, calling the appropriate mode-dependent function
  while (true) {
    int32_t status = 0;
    uint64_t curTime = HAL_WaitForNotifierAlarm(m_notifier, &status);
    if (curTime == 0 || status != 0) break;

    m_expirationTime += m_period;

    UpdateAlarm();

    // Call callback
    LoopFunc();
  }
}

double TimedRobot::GetPeriod() const { return m_period; }

TimedRobot::TimedRobot(double period) : IterativeRobotBase(period) {
  int32_t status = 0;
  m_notifier = HAL_InitializeNotifier(&status);
  wpi_setErrorWithContext(status, HAL_GetErrorMessage(status));

  // HAL_Report(HALUsageReporting::kResourceType_Framework,
  //            HALUsageReporting::kFramework_Periodic);
  HAL_Report(HALUsageReporting::kResourceType_Framework,
             HALUsageReporting::kFramework_Iterative);
}

TimedRobot::~TimedRobot() {
  int32_t status = 0;

  HAL_StopNotifier(m_notifier, &status);
  wpi_setErrorWithContext(status, HAL_GetErrorMessage(status));

  HAL_CleanNotifier(m_notifier, &status);
}

void TimedRobot::UpdateAlarm() {
  int32_t status = 0;
  HAL_UpdateNotifierAlarm(
      m_notifier, static_cast<uint64_t>(m_expirationTime * 1e6), &status);
  wpi_setErrorWithContext(status, HAL_GetErrorMessage(status));
}
