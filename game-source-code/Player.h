#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <vector>

using std::shared_ptr;
using std::vector;

#include "IMovingEntity.h"
#include "Grid.h"
#include "Weapon.h"

/** \struct PlayerDimension
 *	\brief Contains information about a Player's height, width and speed.
 *  \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
 *	\version 3.0
 */
struct PlayerDimension
{
    const float height = 16.0;
    const float width  = 16.0;
    const float speed  = 1.0;
};

/** \class Player
 *  \brief This is a Player Class that inherits from the IMovingEntity class. It
 *  contains virtual functions that have been overridden. It models
 *	a Player object. A Player can move and can shoot bullets.
 *  \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
 *  \version 3.0
 */
class Player : public IMovingEntity
{
    public:

        /** \brief Parameterized constructor. Creates a Player object.
         *  \param grid is of type grid.
         */
        Player(const Grid& grid);

        /** \brief Virtual Destructor. Destroys a Player object.
		 */
        virtual ~Player();

        /** \brief Inherited from IMovingEntity. A virtual function that
         *  moves a Player object left, right, up or down in a 2D movement.
         */
        virtual void move() override;

        /** \brief Inherited from IMovingEntity. A virtual function that
         *  returns a enum of ObjectType::PLAYER.
         *  \return An enum of the strongly typed enum class ObjectType.
         */
        virtual ObjectType getObjectType() const override;

        /** \brief Inherited from IMovingEntity. A virtual function that
         *  returns a Position of the Player object.
         *  \return Position of the Player object containing its current position.
         */
        virtual Position getPosition() const override;

        /** \brief Inherited from IMovingEntity. A virtual function that
         *  returns a boundary box indicating the rectangular area covered by a
         *  Player object.
         *  \return BoundaryBox object of the type BoundaryBox.
         */
        virtual BoundaryBox getBoundaryBox() override;

        /** \brief Inherited from IMovingEntity. A virtual function that
         *  queries if a Player object is still alive or not.
         *  \return bool
         */
        virtual bool isAlive() const override;

        /** \brief Inherited from IMovingEntity. A virtual function that
         *  sets the Player as not alive when killed.
         *  \return void
         */
        virtual void eliminated() override;

        /** \brief Inherited from IMovingEntity. A virtual function that
         *  returns the direction of the Player.
         *  \return Direction of the Player of type Direction of the enum class.
         */
        virtual Direction getDirection() const override;

        /** \brief Inherited from IMovingEntity. A virtual function that
         *  sets the direction of the Player.
         *  \param direction of type Direction of the enum class.
         */
        virtual void setDirection(Direction direction) override;

        /** \brief Inherited from IMovingEntity. A virtual function that
         *  gets a constant copy of the Player object's number of lives left.
         *  \return int indicating the player's remaining lives.
         */
        int getRemainingLives() const override;

        /** \brief Inherited from IMovingEntity. A virtual function that will be
         *  used to bring the Player object back to life, if the remaining lives
         *  are not zero.
         */
		virtual void reincarnate() override;

        /** \brief Inherited from IMovingEntity. A virtual function that will be
         *  to return false for the poisoned status of a Player object.
         *  \return bool
         */
        virtual bool isPoisoned() const override;

        /** \brief Inherited from IMovingEntity. A virtual function that will not
         *  be implemented because a Player object cannot be poisoned.
         */
        virtual void poison() override;

        /** \brief Inherited from IMovingEntity. A virtual function that will be
         *  not be implemented as a Player doesn't have hit points.
         *  \return int
         */
        virtual int getHitPoints() const override;

        /** \brief Creates player bullets and returns them in a vector.
         *  \return vector<shared_ptr<PlayerBullet>>
         */
        vector<shared_ptr<PlayerBullet>> shoot();

        /** \brief Upgrades the Player's weapon.
         */
        void upgradePlayerWeapon();

        /** \brief Adds the given score to the player's current score.
         *  \param score of type int.
         */
        void addScore(int score);

        /** \brief A function that creates a constant copy of the player's score
         *  and returns it.
         *  \return int
         */
        int getScore() const;

        /** \brief Returns true if the player has collided with a deadly enemy.
         */
		bool isHit();

    private:

        int numberOfLives_;
        int score_ = 0;
        bool hasBeenHit_;
        const Grid grid_;
        Position position_;
        Direction direction_;
        Weapon weapon_;
        struct PlayerDimension dimensions_;
};

#endif // PLAYER_H
