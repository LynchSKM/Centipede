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
 *  It generates PlayerBullet objects at a Position passed in after a certain
 *  reload time has elapsed.
 *  \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
 *  \version 3.0
 */

class Weapon
{
    public:
        /** \brief Default Constructor. Creates a Weapon object.
         */
        Weapon();

        /** \brief Creates player bullet at the specified position and returns them in a vector.
         *  \param grid is of type Grid and is taken by reference.
         *  \param start_position is of type Position and is the staring point of the bullet.
         *  \return vector<shared_ptr<PlayerBullet>>
         */
        vector<shared_ptr<PlayerBullet>> fire(const Grid& grid, Position start_position);

        /** \brief Returns the reload time of the weapon.
         */
        double getReloadTime() const;

        /** \brief Halves the reload time of the PlayerBullet.
         */
        void upgradeWeapon();

        /** \brief Resets the reload time to it default one.
         */
        void reset();

        /** \brief Default Destructor. Destroys a Weapon object.
         */
        ~Weapon();

    private:
        StopWatch reload_timer_;
        double timeSinceLastShoot_;
        double reload_time_;
        bool isWeaponUpgraded_;
};

#endif // WEAPON_H
