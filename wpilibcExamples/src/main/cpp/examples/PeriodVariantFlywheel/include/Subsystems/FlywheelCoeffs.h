/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/controller/PeriodVariantKalmanFilterCoeffs.h>
#include <frc/controller/PeriodVariantLoop.h>
#include <frc/controller/PeriodVariantPlantCoeffs.h>
#include <frc/controller/StateSpaceControllerCoeffs.h>

frc::PeriodVariantPlantCoeffs<1, 1, 1> MakeFlywheelPlantCoeffs();
frc::StateSpaceControllerCoeffs<1, 1, 1> MakeFlywheelControllerCoeffs();
frc::PeriodVariantKalmanFilterCoeffs<1, 1, 1> MakeFlywheelObserverCoeffs();
frc::PeriodVariantLoop<1, 1, 1> MakeFlywheelLoop();