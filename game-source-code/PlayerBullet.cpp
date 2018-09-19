#include "PlayerBullet.h"


PlayerBullet::PlayerBullet(Position position, Grid grid):position_{position},grid_{grid}
{   setDirection(Direction::UP);
    alive_ = true;
    objectType_ = ObjectType::PLAYER_LASER_BULLET;
}

void PlayerBullet::move()
{   struct PlayerBulletDimensions Dimension;

    auto newYPos = position_.getY_pos() - Dimension.speed;

    if(newYPos > 8.0f)position_.setY_pos(newYPos);
    else eliminated();
}

Direction PlayerBullet::getDirection() const
{
    return direction_;
}

void PlayerBullet::setDirection(Direction direction)
{
    direction_ = direction;
}

ObjectType PlayerBullet::getObjectType() const
{
    return objectType_;
}

Position PlayerBullet::getPosition() const
{
    return position_;
}

BoundaryBox PlayerBullet::getBoundaryBox()
{
    struct PlayerBulletDimensions Dimension;
    BoundaryBox box{position_,Dimension.width,Dimension.height,0.0f};
    return box;
}

bool PlayerBullet::isAlive() const
{
    return alive_;
}

void PlayerBullet::eliminated()
{
    alive_ = false;
}

PlayerBullet::~PlayerBullet()
{
    //dtor
}
