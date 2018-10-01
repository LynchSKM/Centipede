#include "PlayerBullet.h"

struct PlayerBulletDimensions PlayerBullet::dimensions_;

PlayerBullet::PlayerBullet(Position position, const Grid& grid):
    position_{position},
    grid_{grid},
    alive_{true},
    direction_{Direction::UP}
{

}

void PlayerBullet::move()
{
    auto newYPos = position_.getY_pos() - dimensions_.speed;
    auto half = 2.0f;
    if(newYPos > (dimensions_.height/half)) position_.setY_pos(newYPos);
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
    return ObjectType::PLAYER_LASER_BULLET;
}

Position PlayerBullet::getPosition() const
{
    return position_;
}

BoundaryBox PlayerBullet::getBoundaryBox()
{
    BoundaryBox box{position_, dimensions_.width, dimensions_.height,0.0f};
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

void PlayerBullet::reincarnate()
{

}

int PlayerBullet::getRemainingLives() const
{
    if(isAlive()) return 1;
    return 0;
}

bool PlayerBullet::isPoisoned() const
{
    return false;
}

void PlayerBullet::poison()
{
    return;
}

int PlayerBullet::getHitPoints() const
{
    return 0;
}

PlayerBullet::~PlayerBullet()
{
    //dtor
}
