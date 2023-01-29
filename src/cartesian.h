//
// Created by Boaretti on 9/1/2020.
//

#ifndef UNTITLED_CARTESIAN_H
#define UNTITLED_CARTESIAN_H

#include "axis.h"
#include <thread>         // std::thread

class cartesian {
private:
    axis X_axis;
    axis Y_axis;

public:
    cartesian(const axis &xAxis, const axis &yAxis);
    cartesian();
    virtual ~cartesian();

    int moveAxisToXY(int X_position, int Y_position);

    const axis &getXAxis() const;
    const axis &getYAxis() const;

    void setXAxis(const axis &xAxis);
    void setYAxis(const axis &yAxis);

    int getXAxis_position();
    int getYAxis_position();

    void setXAxis_position(int position);
    void setYAxis_position(int position);

    void moveToXYposition(int X_desired_position, int Y_desired_position);
    void printPosition(int value);

private:



};


#endif //UNTITLED_CARTESIAN_H
