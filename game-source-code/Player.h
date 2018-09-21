#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <vector>

using std::shared_ptr;
using std::vector;

#include "IMovingEntity.h"
#include "Grid.h"
#include "Dimensions.h"
#include "PlayerBullet.h"
#include "StopWatch.h"

/** \class Player
*   \brief This is a Player Class that inherits from the IMovingEntity class. It
*   contains virtual functions that have been overridden and new ones.
*
*   \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
*   \version
*/
class Player : public IMovingEntity
{
    public:

        /** \brief Parameterized constructor. Creates a Player object.
         *  \param grid is of type grid.
         */
        Player(const Grid& grid);

        /**< \brief Destroys the player object */
        virtual ~Player();

        /** \brief Inherited from IMovingEntity. A virtual function that
         *   moves a Player object.
         */
        virtual void move() override;

        /** \brief Inherited from IMovingEntity. A virtual function that
         *  returns a enum of ObjectType of the Player object.
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
         *  \return an int a constant copy of the numberOfLives_.
         */
        int getRemainingLives() const override;

        /** \brief Inherited from IMovingEntity. A virtual function that will be
         * used to bring the Player object back to life, if the remaining lives
         * are not zero.
         */
		virtual void reincarnate() override;

        /** \brief Creates player bullets and stores them in a vector.
         *  \return a vector of shared_ptr to IMovingEntity.
         */
        vector <shared_ptr<IMovingEntity>> shoot();

        /** \brief adds the given score to the player's current score.
         *  \param score of type int.
         */
        void addScore(int score);

        /** \brief A function that creates a constant copy of the player's score
         *  and returns it.
         *  \return an int, a constant copy of the score.
         */
        int getScore() const;

        /** \brief returns true if the player has collided with a deadly enemy.
         */
		bool isHit();

    private:

		ObjectType objectType_;
        int numberOfLives_;
        int score_ = 0;
        bool hasBeenHit_;
        const Grid grid_;
        StopWatch reload_timer;
        double timeSinceLastShoot;
        double reload_time;
        Position position_;
        Direction direction_;
};

#endif // PLAYER_H
