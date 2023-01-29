//============================================================================
// Name        : mythingCPP.cpp
// Author      : Fabio
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <thread>

#include "memGPIO.hpp"
#include "cartesian.h"
#include "axis.h"
#include "step_motor.h"
#include "step_motors_pin_definitions.h"
#include "motor_motion_definitions.h"
#include "axis_definitions.h"


int main() {


		memGPIO gpio;

		//MOTOR X
	    step_motor X_stepMotor(MOTOR_X_ENABLE_PIN, MOTOR_X_STEP_PIN, MOTOR_X_DIR_PIN, MOTOR_X_FAULT_PIN, X_AXIS_HOME_PIN, 1,
	                          MOTOR_X_SPEED_RPM, MOTOR_X_MODE_FACTOR, MOTOR_X_STEPS_REV(), RAMP_TIME_S, RAMP_LEVELS_N, gpio);

	    //MOTOR Y
	    step_motor Y_stepMotor(MOTOR_Y_ENABLE_PIN, MOTOR_Y_STEP_PIN, MOTOR_Y_DIR_PIN, MOTOR_Y_FAULT_PIN, Y_AXIS_HOME_PIN, 1,
	                          MOTOR_Y_SPEED_RPM, MOTOR_Y_MODE_FACTOR, MOTOR_Y_STEPS_REV(), RAMP_TIME_S, RAMP_LEVELS_N, gpio);


	    //CREATING THE AXIS ASSUMING IT IS ANYWHERE AXIS_X_MAX_MM, AXIS_X_MAX_MM AS WORST CASE
	    axis X_axis(X_stepMotor, AXIS_X_MAX_MM, AXIS_X_MAX_MM, AXIS_X_LABEL);
	    axis Y_axis(Y_stepMotor, AXIS_Y_MAX_MM, AXIS_Y_MAX_MM, AXIS_Y_LABEL );

	    cartesian XY_cartesian(X_axis,Y_axis);

	    std::cout << "X POS: " << XY_cartesian.getXAxis_position() <<
	    " Y POS: " << XY_cartesian.getYAxis_position() << std::endl;


	   // XY_cartesian.moveToXYposition(10,20);

	    std::cout << "X POS: " << XY_cartesian.getXAxis_position() <<
	              " Y POS: " << XY_cartesian.getYAxis_position() << std::endl;


}


