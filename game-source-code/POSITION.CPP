#include "Position.h"


    Position::Position(){

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
