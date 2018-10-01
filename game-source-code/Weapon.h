#ifndef WEAPON_H
#define WEAPON_H

#include "StopWatch.h"
#include "PlayerBullet.h"
#include "POSITION.H"

#include <memory>
#include <vector>
using std::shared_ptr;
using std::vector;

/** \class Weapon
 *  \brief This is a class that models a weapon for the Player.
 *  \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
 *  \version 3.0
 */

class Weapon
{
    public:
        /** Default Constructor. Creates a Weapon object.
         */
        Weapon();

        /** \brief Creates player bullet at the specified position and returns them in a vector.
         *  \param grid is of type Grid and is taken by reference.
         *  \param start_position is of type Position.
         *  \return vector<shared_ptr<PlayerBullet>>
         */
        vector<shared_ptr<PlayerBullet>> fire(const Grid& grid, Position start_position);

        /** Default Destructor. Destroys a Weapon object.
         */
        ~Weapon();

    private:
        StopWatch reload_timer_;
        double timeSinceLastShoot_;
        double reload_time_;
};

#endif // WEAPON_H
