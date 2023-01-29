//
// Created by Boaretti on 8/31/2020.
//

#include <unistd.h>
#include <iostream>
#include "step_motor.h"
#include "motor_motion_definitions.h"
#include "step_motors_pin_definitions.h"
#include "memGPIO.hpp"
#include <math.h>

int step_motor::getEnablePin() const {
    return enable_pin;
}

void step_motor::setEnablePin(int enablePin) {
    enable_pin = enablePin;
}

int step_motor::getStepPin() const {
    return step_pin;
}

void step_motor::setStepPin(int stepPin) {
    step_pin = stepPin;
}

int step_motor::getDirPin() const {
    return dir_pin;
}

void step_motor::setDirPin(int dirPin) {
    dir_pin = dirPin;
}

int step_motor::getFaultPin() const {
    return fault_pin;
}

void step_motor::setFaultPin(int faultPin) {
    fault_pin = faultPin;
}

short step_motor::getIsUsed() const {
    return is_used;
}

void step_motor::setIsUsed(short isUsed) {
    is_used = isUsed;
}

step_motor::step_motor() {


}



step_motor::~step_motor() {
}

int step_motor::stepUsingRamp(int steps, int rampTime, int rampLevels, int initialDelaySeconds)
{

    return 0;
}

step_motor::step_motor(int enablePin, int stepPin, int dirPin, int faultPin, int stopPin, short isUsed, int speed, int factor,
                       int stepsForRev, int rampTime, int rampLevels, memGPIO gpio) : enable_pin(enablePin), step_pin(stepPin),
                                                                        dir_pin(dirPin), fault_pin(faultPin), stop_pin(stopPin),
                                                                        is_used(isUsed), speed(speed), factor(factor),
                                                                        steps_for_rev(stepsForRev), ramp_time(rampTime),
                                                                        ramp_levels(rampLevels), gpio(gpio)
{

	gpio.setDirKernelPinNumber(this->dir_pin, GPIO_OUTPUT);
	gpio.setDirKernelPinNumber(this->step_pin, GPIO_OUTPUT);
	gpio.setDirKernelPinNumber(this->enable_pin, GPIO_OUTPUT);

	gpio.setDirKernelPinNumber(this->stop_pin, GPIO_INPUT);

	gpio.setValueKernelPinNumber(this->enable_pin, MOTOR_ENABLED);
	sleep(2);
	gpio.setValueKernelPinNumber(this->enable_pin, MOTOR_DISABLED);
	sleep(2);


}

int step_motor::move(int distance)
{
	int steps = STEPS_FOR_MM() * distance;

	int stepsToChangeDelay = 0;
	int stepsCount = 0;
	int stepsOnRamp = 0;

	//int (*pSensor)() = args->pSensor;
	double initialDelaySeconds = (( (double)60 / MOTOR_Y_SPEED_RPM ) / MOTOR_Y_STEPS_REV());
	double delaySecondsThread = (double)( initialDelaySeconds * this->ramp_levels );
	//double delaySecondsThread = (double)( (( (double) 60 / MOTOR_X_SPEED_RPM / MOTOR_X_STEPS_REV ) * this->ramp_levels ));
	//double initialDelaySeconds = (double)( (( static_cast<double>(60 / MOTOR_X_SPEED_RPM ) / MOTOR_X_STEPS_REV ) * this->ramp_levels ));

	//printf("arguments: StepPin: %d  Steps: %d  RampTime: %d  Levels: %d\n", motor.step_pin, steps,rampTime, rampLevels);

	std::cout << "Steps: " << steps << " RampTime: " << this->ramp_time << " RampLevels: " << this->ramp_levels << std::endl;

	//gpio_set_value(this->enable_pin, MOTOR_ENABLED);
	while ( (steps != 0) && ((abs(steps) > 0) ))
	{

		if ( (this->is_used) && ( steps != 0)  )
		{
			//steps > 0 ? gpio_set_value(this->dir_pin, LOW) : gpio_set_value(this->dir_pin, HIGH);
			steps > 0 ? steps-- : steps++;
			//gpio_set_value(motor.step_pin, HIGH);
			usleep(4);
			//gpio_set_value(motor.step_pin, LOW);
			usleep(4);
			usleep((int) ( (delaySecondsThread * ONE_SECOND_US ) ) );
			stepsToChangeDelay++;
			stepsCount++;
		}

		if (abs(steps) > stepsCount ) //  RAMP-UP
		{
			//TRIGGER TO CHANGE THE DELAY
			if (((stepsToChangeDelay * delaySecondsThread) > static_cast<double>( static_cast<double>(this->ramp_time / this->ramp_levels))) && (delaySecondsThread > ( initialDelaySeconds)) )
			{
				delaySecondsThread = delaySecondsThread - ( initialDelaySeconds ); //RAMP-UP
				stepsOnRamp = stepsOnRamp + stepsToChangeDelay; // MESURING THE RAMP-UP
				stepsToChangeDelay = 0;
			}
		}else // WE ARE NOW ON THE MIDDLE OF THE MOVEMENT
		{
			if (abs(steps) <= stepsOnRamp ) // NUMBER OF STEP REACHED THE POINT FOR RAMP-DOWN
			{
				if (((stepsToChangeDelay * delaySecondsThread) > (double)( (double)this->ramp_time / this->ramp_levels))  )
				{
					delaySecondsThread = delaySecondsThread + ( initialDelaySeconds ); // RAMP-DOWN
					stepsToChangeDelay = 0;
				}

			}else
			{
				// MORE THEN THE MIDDLE BUT NOT IN THE END FOR RAMP DOWN....KEEP WALKING JHONNY

			}
		}


	}
	//gpio_set_value(this->enable_pin, MOTOR_DISABLED);
	std::cout << "Steps: " << steps << " RampTime: " << this->ramp_time << " RampLevels: " << this->ramp_levels << std::endl;


	return 0;
}

void step_motor::initMotor() {




}
