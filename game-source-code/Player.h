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


/** \class Player
*   \brief This is a Player Class that inherits from the IMovingEntity class. It
*   contains virtual functions that have been overridden and new ones.
*
*   \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
*
*/
class Player : public IMovingEntity
{
    public:

        /** \brief Creates a player object parameterized constructor.
         * \param is grid of type grid.
         */
        Player(Grid grid);

        /**< \brief Destroys the player object */
        virtual ~Player();

        /** \brief Inherited from IMovingEntity. A pure virtual function that
        *    moves derived class objects.
        */
        virtual void move() override;

        /** \brief Inherited from IMovingEntity. A pure virtual function that
        *    returns a enum of ObjectType of a derived class object.
        *   \return An enum of the strongly typed enum class ObjectType.
        */
        virtual ObjectType getObjectType() const override;

        /** \brief Inherited from IMovingEntity. A pure virtual function that
        *    returns a Position of the derived class object.
        *   \return Position of the derived class object containing its current
        *    position.
        */
        virtual Position getPosition() const override;

        /** \brief Inherited from IMovingEntity. A pure virtual function that
        *   returns a Rectangle indicating the rectangular area covered by a
        *    derived class object.
        *   \return A Rectangle object of the type Rectangle struct.
        */
        virtual BoundaryBox getBoundaryBox() override;

        /** \brief Inherited from IMovingEntity. A pure virtual function that
        *    queries if a derived class object is still alive or not.
        *   \return bool
        */
        virtual bool isAlive() const override;

        /** \brief Inherited from IMovingEntity. A pure virtual function that
        *    sets the derived class object as not alive when killed.
        *   \return void
        */
        virtual void eliminated() override;

        /** \brief Inherited from IMovingEntity. A pure virtual function that
        *    returns the direction of an object.
         * \return The direction of the object of type Direction of the enum class.
         */
        virtual Direction getDirection() const override;

        /** \brief Inherited from IMovingEntity. A pure virtual function that
        *    sets the direction of an object.
         * \param direction of type Direction of the enum class.
         */
        virtual void setDirection(Direction direction) override;

        /** \brief gets a constant copy of the object's Number of lives.
         * \return an int a constant copy of the numberOfLives_.
         */
        int getRemainingLives() const;

        /** \brief Creates player bullets and stores them in a vector.
         * \return a vector of shared_ptr to IMovingEntity.
         */
        vector <shared_ptr<IMovingEntity>> shoot();

        /** \brief adds the given score to the player's current score.
         * \param score of type int.
         */
        void addScore(int score);

         /** \brief A function that creates a constant copy of the player's score
         *          and returns it.
         * \return an int, a constant copy of the score.
         */
        int getScore() const;

        /** \brief Decreases the number of lifes by one.
         */
		void reincarnate();


    private:

		ObjectType objectType_;
        int numberOfLives_;
        int score_ = 0;
        const Grid grid_;
        Position position_;
        Direction direction_;
};

#endif // PLAYER_H
