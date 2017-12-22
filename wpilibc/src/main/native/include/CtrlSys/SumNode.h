/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <limits>
#include <memory>
#include <tuple>

#include <support/mutex.h>

namespace frc {

/**
 * Takes an arbitrary list of input nodes and outputs the sum of their
 * outputs.
 */
template <typename SourceNode, typename... SourceNodes>
class SumNode {
 public:
  SumNode(SourceNode& input, bool positive, SourceNodes&&... inputs);

  double GetOutput();

  void SetContinuous(bool continuous = true);
  void SetInputRange(double minimumInput, double maximumInput);

  void SetTolerance(double tolerance, double deltaTolerance);
  bool InTolerance() const;

 private:
  /**
   * First argument is input node.
   * Second argument is whether to add or subtract its output.
   */
  std::tuple<SourceNode, bool, SourceNodes...> m_inputs;

  double m_currentResult = 0.0;
  double m_lastResult = 0.0;

  bool m_continuous = false;
  double m_minimumInput = 0.0;
  double m_maximumInput = 0.0;

  double m_tolerance = std::numeric_limits<double>::infinity();
  double m_deltaTolerance = std::numeric_limits<double>::infinity();

  mutable wpi::mutex m_mutex;
};

}  // namespace frc

#include "CtrlSys/SumNode.inc"
