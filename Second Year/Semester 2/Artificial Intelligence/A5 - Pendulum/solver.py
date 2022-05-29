# -*- coding: utf-8 -*-
"""
In this file your task is to write the solver function!

"""


class Hedge:
    def __init__(self, lowerLimit, upperLimit, middleLimit):
        self.lowerLimit = lowerLimit
        self.upperLimit = upperLimit
        self.middleLimit = middleLimit

    def compute_membership_degree(self, angle):
        return max(0,
                   min((angle - self.lowerLimit) / (self.middleLimit - self.lowerLimit),
                       1,
                       (self.upperLimit - angle) / (self.upperLimit - self.middleLimit)))


def solver(thetaAngle, wAngularSpeed):
    """
    Parameters
    ----------
    thetaAngle : TYPE: float
        DESCRIPTION: the angle theta
    wAngularSpeed : TYPE: float
        DESCRIPTION: the angular speed omega

    Returns
    -------
    F : TYPE: float
        DESCRIPTION: the force that must be applied to the cart
    or

    None :if we have a division by zero

    """
    theta = {"NVB": Hedge(-50, -25, -40),
             "NB": Hedge(-40, -10, -25),
             "N": Hedge(-20, 0, -10),
             "ZO": Hedge(-5, 5, 0),
             "P": Hedge(0, 20, 10),
             "PB": Hedge(10, 40, 25),
             "PVB": Hedge(25, 50, 40)}

    membership_degrees_theta = compute_membership_degree(theta, thetaAngle)

    omega = {"NB": Hedge(-10, -3, -8),
             "N": Hedge(-6, 0, -3),
             "ZO": Hedge(-1, 1, 0),
             "P": Hedge(0, 6, 3),
             "PB": Hedge(3, 10, 8)}

    membership_degrees_omega = compute_membership_degree(omega, wAngularSpeed)

    force_table = {"PVB PB": "PVVB", "PVB P": "PVVB", "PVB ZO": "PVB", "PVB N": "PB", "PVB NB": "P",
                   "PB PB": "PVVB", "PB P": "PVB", "PB ZO": "PB", "PB N": "P", "PB NB": "Z",
                   "P PB": "PVB", "P P": "PB", "P ZO": "P", "P N": "Z", "P NB": "N",
                   "ZO PB": "PB", "ZO P": "P", "ZO ZO": "Z", "ZO N": "N", "ZO NB": "NB",
                   "N PB": "P", "N P": "Z", "N ZO": "N", "N N": "NB", "N NB": "NVB",
                   "NB PB": "Z", "NB P": "N", "NB ZO": "NB", "NB N": "NVB", "NB NB": "NVVB",
                   "NVB PB": "N", "NVB P": "NB", "NVB ZO": "NVB", "NVB N": "NVVB", "NVB NB": "NVVB"
                   }
    forces = {}
    for thetaValue in theta:
        for omegaValue in omega:
            force_value = min(membership_degrees_theta[thetaValue], membership_degrees_omega[omegaValue])
            new_force_key = thetaValue + " " + omegaValue
            if force_table[new_force_key] not in forces:
                forces[force_table[new_force_key]] = force_value
            elif forces[force_table[new_force_key]] < force_value:
                forces[force_table[new_force_key]] = force_value

    products = {"NVVB": -32, "NVB": -24, "NB": -16, "N": -8, "Z": 0, "P": 8, "PB": 16, "PVB": 24, "PVVB": 32}

    sum_of_forces = 0
    product = 0
    for force in forces:
        sum_of_forces += forces[force]
        product += forces[force] * products[force]

    if sum_of_forces != 0:
        final_force = product / sum_of_forces
    else:
        final_force = 0

    return final_force


def compute_membership_degree(values, x):
    membership_degrees = {}
    for element in values:
        membership_degrees[element] = 0
        if values[element].lowerLimit <= x <= values[element].upperLimit:
            membership_degrees[element] = values[element].compute_membership_degree(x)

    return membership_degrees
