/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2019 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

package edu.wpi.first.networktables;

import org.junit.jupiter.api.Test;

class JNITest {
  @Test
  void jniLinkTest() {
    // Test to verify that the JNI test link works correctly.
    int inst = NetworkTablesJNI.getDefaultInstance();
    NetworkTablesJNI.flush(inst);
  }
}
