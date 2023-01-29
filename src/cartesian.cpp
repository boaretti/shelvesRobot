//
// Created by Boaretti on 9/1/2020.
//
#include <unistd.h>
#include <iostream>
#include "cartesian.h"
#include "axis.h"
#include <thread>         // std::thread

cartesian::cartesian(const axis &xAxis, const axis &yAxis) : X_axis(xAxis), Y_axis(yAxis) {}

cartesian::cartesian() {}

cartesian::~cartesian() {

}

const axis &cartesian::getXAxis() const {
    return X_axis;
}

void cartesian::setXAxis(const axis &xAxis) {
    X_axis = xAxis;
}

const axis &cartesian::getYAxis() const {
    return Y_axis;
}

void cartesian::setYAxis(const axis &yAxis) {
    Y_axis = yAxis;
}

int cartesian::getXAxis_position(){
    return this->X_axis.getPosition();
}

int cartesian::getYAxis_position(){
    return this->Y_axis.getPosition();
}

void cartesian::setXAxis_position(int position){
    this->X_axis.setPosition(position);

}

void cartesian::setYAxis_position(int position){
    this->Y_axis.setPosition(position);
}

void cartesian::printPosition(int value){
	std::cout << "Position:. " << value << std::endl;

}

void cartesian::moveToXYposition(int X_desired_position, int Y_desired_position){
    //std::thread t1(&cartesian::setXAxis_position,this, X_desired_position);
    //std::thread t2(&cartesian::setYAxis_position,this, Y_desired_position);
    std::thread t3(&axis::moveToPosition,&X_axis, X_desired_position);
    std::thread t4(&axis::moveToPosition,&Y_axis, Y_desired_position);


    t3.join();
    t4.join();
}
