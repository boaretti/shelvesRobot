//
// Created by Boaretti on 9/1/2020.
//
#include <unistd.h>
#include <iostream>
#include "axis.h"

axis::axis() {}

axis::axis(const step_motor &motor, int position, int maxPosition, std::string label) : motor(motor), position(position),
                                                                     max_position(maxPosition), label(label) {
}

axis::~axis() {}

void axis::printPosition(){
	std::cout << "Position:. " << this->position << std::endl;

}

int axis::getPosition() const {
    return position;
}

void axis::setPosition(int position) {
    axis::position = position;
}

int axis::getMaxPosition() const {
    return max_position;
}

void axis::setMaxPosition(int maxPosition) {
    max_position = maxPosition;
}

int axis::moveToPosition(int position_mm)
{
	int differenceOfPosition = calculateMovimentMM(position_mm);
	std::cout << "Position Difference:." << this->label << " " << differenceOfPosition << std::endl;

	this->motor.move(differenceOfPosition);

    this->setPosition(position_mm);

    return 0;
}



int axis::calculateMovimentMM(int newPositionMM) {
	return ( newPositionMM - this->position );
}
