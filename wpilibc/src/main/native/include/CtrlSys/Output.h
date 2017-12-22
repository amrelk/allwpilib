/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <support/mutex.h>

#include "Base.h"
#include "Controller.h"
#include "Notifier.h"
#include "PIDOutput.h"

namespace frc {

/**
 * SourceNode adapter for PIDOutput subclasses.
 *
 * Wraps a PIDOutput object in the SourceNode interface by calling PIDWrite() on
 * it at at a regular interval specified in the constructor. This is called in a
 * separate thread.
 */
template <typename SourceNode>
class Output : public Controller {
 public:
  Output(SourceNode& input, PIDOutput& output, double period = kDefaultPeriod);
  virtual ~Output() = default;

  void Enable() override;
  void Disable() override;

  void SetRange(double minU, double maxU);

 protected:
  virtual void OutputFunc();

  friend class OutputGroup;

 private:
  SourceNode& m_input;

  PIDOutput& m_output;
  double m_period;

  Notifier m_thread;
  wpi::mutex m_mutex;

  double m_minU = -1.0;
  double m_maxU = 1.0;
};

}  // namespace frc

#include "CtrlSys/Output.inc"
