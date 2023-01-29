//
// Created by Boaretti on 9/1/2020.
//

#ifndef UNTITLED_AXIS_H
#define UNTITLED_AXIS_H

#include "step_motor.h"

class axis {
public:
    axis();
    virtual ~axis();

    axis(const step_motor &motor, int position, int maxPosition, std::string label);

    int moveToPosition(int position_mm);

    int getPosition() const;
    void setPosition(int position);

    int getMaxPosition() const;
    void setMaxPosition(int maxPosition);
    void printPosition();

protected:
    step_motor motor;
    int calculateMovimentMM(int newPositionMM);

private:
    int position;
    int max_position;
    std::string label;


};


#endif //UNTITLED_AXIS_H
