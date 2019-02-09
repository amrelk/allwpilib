#!/usr/bin/env python3

import frccontrol as frccnt
import matplotlib.pyplot as plt
import numpy as np
import sys


class Drivetrain(frccnt.System):

    def __init__(self, dt):
        """Drivetrain subsystem.

        Keyword arguments:
        dt -- time between model/controller updates
        """
        state_labels = [("Left position", "m"), ("Left velocity", "m/s"),
                        ("Right position", "m"), ("Right velocity", "m/s")]
        u_labels = [("Left voltage", "V"), ("Right voltage", "V")]
        self.set_plot_labels(state_labels, u_labels)

        self.in_low_gear = False

        # Number of motors per side
        self.num_motors = 2.0

        # High and low gear ratios of drivetrain
        Glow = 11.0 / 60.0
        Ghigh = 11.0 / 60.0

        # Drivetrain mass in kg
        self.m = 52
        # Radius of wheels in meters
        self.r = 0.08255 / 2.0
        # Radius of robot in meters
        self.rb = 0.59055 / 2.0
        # Moment of inertia of the drivetrain in kg-m^2
        self.J = 6.0

        # Gear ratios of left and right sides of drivetrain respectively
        if self.in_low_gear:
            self.Gl = Glow
            self.Gr = Glow
        else:
            self.Gl = Ghigh
            self.Gr = Ghigh

        self.model = frccnt.models.drivetrain(frccnt.models.MOTOR_CIM,
                                              self.num_motors, self.m, self.r,
                                              self.rb, self.J, self.Gl, self.Gr)
        u_min = np.matrix([[-12.0], [-12.0]])
        u_max = np.matrix([[12.0], [12.0]])
        frccnt.System.__init__(self, self.model, u_min, u_max, dt)

        if self.in_low_gear:
            q_pos = 0.12
            q_vel = 1.0
        else:
            q_pos = 0.14
            q_vel = 0.95

        q = [q_pos, q_vel, q_pos, q_vel]
        r = [12.0, 12.0]
        self.design_dlqr_controller(q, r)

        qff_pos = 0.005
        qff_vel = 1.0
        self.design_two_state_feedforward([qff_pos, qff_vel, qff_pos, qff_vel],
                                          [12.0, 12.0])

        q_pos = 0.05
        q_vel = 1.0
        q_voltage = 10.0
        q_encoder_uncertainty = 2.0
        r_pos = 0.0001
        r_gyro = 0.000001
        self.design_kalman_filter([q_pos, q_vel, q_pos, q_vel], [r_pos, r_pos])


def main():
    dt = 0.00505
    drivetrain = Drivetrain(dt)
    drivetrain.export_cpp_coeffs("Drivetrain", "Subsystems/", True)

    if "--save-plots" in sys.argv or "--noninteractive" not in sys.argv:
        # plt.figure(1)
        # drivetrain.plot_pzmaps()
        pass
    if "--save-plots" in sys.argv:
        plt.savefig("drivetrain_pzmaps.svg")

    # Set up graphing
    l0 = 0.1
    l1 = l0 + 5.0
    l2 = l1 + 0.1
    t = np.linspace(0, l2 + 5.0, (l2 + 5.0) / dt)

    refs = []

    # Generate references for simulation
    for i in range(len(t)):
        if t[i] < l0:
            r = np.matrix([[0.0], [0.0], [0.0], [0.0]])
        elif t[i] < l1:
            r = np.matrix([[1.524], [0.0], [0.0], [0.0]])
        else:
            r = np.matrix([[0.0], [0.0], [0.0], [0.0]])
        refs.append(r)

    if "--save-plots" in sys.argv or "--noninteractive" not in sys.argv:
        plt.figure(2)
        drivetrain.plot_time_responses(t, refs)
    if "--save-plots" in sys.argv:
        plt.savefig("drivetrain_response.svg")
    if "--noninteractive" not in sys.argv:
        plt.show()


if __name__ == "__main__":
    main()
