#include "Position.h"

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

Position Position::operator -(Position& rhs){
    return Position(xPos_ - rhs.xPos_, yPos_ - rhs.yPos_);
}
