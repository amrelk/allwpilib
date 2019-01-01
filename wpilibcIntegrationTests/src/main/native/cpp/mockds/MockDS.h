/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2019 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <atomic>
#include <thread>

namespace frc {
class MockDS {
 public:
  MockDS() = default;
  ~MockDS() { stop(); }
  MockDS(const MockDS& other) = delete;
  MockDS& operator=(const MockDS& other) = delete;

  void start();
  void stop();

 private:
  std::thread m_thread;
  std::atomic_bool m_active{false};
};
}  // namespace frc
