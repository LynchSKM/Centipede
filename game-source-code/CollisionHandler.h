#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "IEntity.h"
#include "SpatialHash.h"
#include "SeparatingAxisTheorem.h"
#include "CentipedeSegment.h"
#include "Mushroom.h"
#include "Player.h"
#include "Dimensions.h"
#include "ObjectType.h"

#include <algorithm>
#include <vector>
#include <memory>

using std::find;
using std::copy_if;
using std::count_if;
using std::begin;
using std::end;
using std::vector;
using std::shared_ptr;

/**\class CollisionHandler
*  \brief  A Logic Layer class that determines whether collisions have occurred
*   between game objects.
*  \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
*  \version
*/
class CollisionHandler
{
    public:

        /** \brief Parameterized Constructor. Constructs a CollisionHandler object.
         *  \param grid is of type Grid and contains the screen width and height.
         */
        CollisionHandler(const Grid& grid);

        /** \brief Checks for collisions between the game objects that are still alive.
         *
         *  \param game_objects is a vector of shared pointers of type IEntity.
         */
        void checkCollisions(vector<IEntity_ptr>& game_objects);

        /** \brief Returns the points the player has obtained from killing game enemies.
         *  \return int
         */
        int getPointsObtained();

        ~CollisionHandler();
    private:
        SeparatingAxisTheorem sat_algorithm_;
        SpatialHash spatial_hash_;
        int points_obtained_;

        /**\brief Returns the number of objects of the specified object type in the
         *  range given.
         * \param game_objects_begin is a iterator to a vector of shared pointers of type IEntity.
         * \param game_objects_end is a iterator to a vector of shared pointers of type IEntity.
         * \param object_type is of type enum class ObjectType.
         * \return int containing the number of objects.
         */
        int countObjects(vector<IEntity_ptr>::iterator game_objects_begin,
                         vector<IEntity_ptr>::iterator game_objects_end,
                         ObjectType object_type);

        /**\brief Copies the objects from a vector of the specified object type in the
         *  range given to another vector.
         * \param game_objects_begin is a iterator to a vector of shared pointers of type IEntity.
         * \param game_objects_end is a iterator to a vector of shared pointers of type IEntity.
         * \param object_type is of type enum class ObjectType.
         * \return vector<IEntity_ptr> containing the copied objects based on the object type.
         */
        vector<IEntity_ptr> copyObjects(vector<IEntity_ptr>::iterator game_objects_begin,
                                        vector<IEntity_ptr>::iterator game_objects_end,
                                        ObjectType object_type);

        /** \brief Checks whether a player bullet collides with every other game object near it
         * except for a centipede segment. If collisions occur both call their respective eliminated()
         * functions. Mushroom will decrement its number of lives while others will set alive status false.
         * \param player_bullets is a vector of shared pointers to IEnity objects of ObjectType::PLAYER_LASER_BULLET.
         */
        void playerBulletCollidesWithEnemies(vector<IEntity_ptr>& player_bullets);

        /** \brief Checks collisions between the player bullet and a Centipede segment near it.
         * If collisions occur, bot set their alive status false. The next body segment becomes a
         * new Centipede HEAD.
         * \param player_bullets is a vector of shared pointers to IEnity objects of ObjectType::PLAYER_LASER_BULLET.
         * \param centipede is a vector of shared pointers to IEnity objects of ObjectType::CENTIPEDE.
         */
        void playerBulletCollidesWithCentipede(vector<IEntity_ptr>& player_bullets,
                                               vector<IEntity_ptr>& centipede);

        /** \brief Checks collisions between a centipede and a mushroom.
         * If a collision occurs, the Centipede segment goes down and changes direction.
         * \param centipede is a vector of shared pointers to IEnity objects of ObjectType::CENTIPEDE.
         */
        void centipedeCollidesWithMushroom(vector<IEntity_ptr>& centipede);

        /** \brief Checks collisions between a player and other game objects.
         * If a collision occurs, with a Mushroom the player's direction is set to NONE.
         * If it's anything other than a mushroom the player loses a life.
         * \param player is a shared pointer to an IEnity object of ObjectType::PLAYER.
         */
        void playerCollidesWithObjects(vector<IEntity_ptr>& player);

};

#endif // COLLISIONHANDLER_H
