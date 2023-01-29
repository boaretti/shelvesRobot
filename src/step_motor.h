//
// Created by Boaretti on 8/31/2020.
//

#ifndef HEADERS_STEP_MOTOR_H
#define HEADERS_STEP_MOTOR_H

#include "memGPIO.hpp"





class step_motor {
public:

    step_motor();

    step_motor(int enablePin, int stepPin, int dirPin, int faultPin, int stopPin, short isUsed, int speed, int factor,
               int stepsForRev, int rampTime, int rampLevels, memGPIO gpio);

    virtual ~step_motor();

    int getEnablePin() const;
    void setEnablePin(int enablePin);

    int getStepPin() const;
    void setStepPin(int stepPin);

    int getDirPin() const;
    void setDirPin(int dirPin);

    int getFaultPin() const;
    void setFaultPin(int faultPin);

    short getIsUsed() const;
    void setIsUsed(short isUsed);

    void initMotor();

    int move(int distance);



private:
    int enable_pin;
    int step_pin;
    int dir_pin;
    int fault_pin;
    int stop_pin;
    short is_used;

    int speed;
    int factor;
    int steps_for_rev;

    int ramp_time;
    int ramp_levels;

    int stepUsingRamp(int steps, int rampTime, int rampLevels, int initialDelaySeconds);
    memGPIO gpio;


};


#endif //UNTITLED_STEP_MOTOR_H
