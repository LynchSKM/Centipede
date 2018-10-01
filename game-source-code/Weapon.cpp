#include "Weapon.h"

Weapon::Weapon():
    timeSinceLastShoot_{0},
    reload_time_{0.175}
{
    reload_timer_.start();
}

vector<shared_ptr<PlayerBullet>> Weapon::fire(const Grid& grid, Position start_position)
{
    vector<shared_ptr<PlayerBullet>> bullets;
    reload_timer_.pause();
    auto time_elapsed = reload_timer_.getPauseTime();
    if((time_elapsed-timeSinceLastShoot_)>reload_time_)
    {
        bullets.push_back(std::make_shared<PlayerBullet>(start_position,grid));
        timeSinceLastShoot_ = time_elapsed;
        reload_timer_.resume();
    }
    return bullets;
}

Weapon::~Weapon()
{
    //dtor
}
