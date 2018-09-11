#include "Position.h"
#include <cmath>

Position::Position(float x, float y): xPos_{x}, yPos_{y}{

}

Position::~Position(){

}

void Position::setX_pos(float xPos){
    xPos_ = xPos;
}

void Position::setY_pos(float yPos){
    yPos_ = yPos;
}

float Position::getX_pos() const{
    return xPos_;
}

float Position::getY_pos() const{
    return yPos_;
}

Position Position::operator -(const Position& rhs){
    return Position(xPos_ - rhs.xPos_, yPos_ - rhs.yPos_);
}

bool Position::operator ==(const Position& rhs) const{
    return(xPos_ == rhs.xPos_ && yPos_ == rhs.yPos_);
}
bool Position::operator<(const Position& rhs) const
{
    auto distanceL = sqrt(pow(xPos_,2)+(yPos_,2));
    auto distanceR = sqrt(pow(rhs.xPos_,2)+(rhs.yPos_,2));

    return(distanceL < distanceR );
}
