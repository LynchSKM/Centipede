#ifndef PLAYERBULLET_H
#define PLAYERBULLET_H

#include "IMovingEntity.h"
#include "Grid.h"

/** \struct PlayerBulletDimensions
 *	\brief Contains information about a PlayerBullet's height, width and speed.
 *  \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
 *	\version 3.0
 */
struct PlayerBulletDimensions
{
    const float height = 12.0;
    const float width = 2.0;
    const float speed = 2.0;
};

/** \class PlayerBullet
 *  \brief This is a class that inherits from the IMovingEntity class. It models
 *  a Player's laser bullet object in the game. It contains virtual functions that
 *  will be overridden.
 *  \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
 *  \version 3.0
 */

class PlayerBullet : public IMovingEntity
{
    public:

        /** \brief Parameterized Constructor. Creates a PlayerBullet object.
         *  \param position of type Position contains the centre position.
         *  \param grid is of type const Grid and contains the screen's width and height.
         */
        PlayerBullet(Position position, const Grid& grid);

        /** Virtual Destructor. Destroys a PlayerBullet object.
         */
        virtual ~PlayerBullet();

        /** \brief Inherited from IMovingEntity. A virtual function that
         *  moves a PlayerBullet object.
         */
        virtual void move() override;

        /** \brief Inherited from IMovingEntity. A virtual function that
         *  returns the direction of a PlayerBullet object.
         *  \return Direction an enum of type enum class Direction.
         */
        virtual Direction getDirection() const override;

        /** \brief Inherited from IMovingEntity. A virtual function that sets
         *  the direction of a PlayerBullet object.
         *  \param direction an enum of enum class Direction.
         */
        virtual void setDirection(Direction direction) override;

        /** \brief Inherited from IMovingEntity. A virtual function that returns a
         *  enum ObjectType::PLAYER_LASER_BULLET of ObjectType of a PlayerBullet object.
         *  \return ObjectType an enum of the strongly typed enum class ObjectType.
         */
        virtual ObjectType getObjectType() const override;

        /** \brief Inherited from IMovingEntity. A virtual function that returns
         *  a Position of the PlayerBullet object.
         *  \return Position of the PlayerBullet object.
         */
        virtual Position getPosition() const override;

        /** \brief Inherited from IMovingEntity. A virtual function that returns
		 *	a BoundaryBox indicating the rectangular area covered by a PlayerBullet object.
         *  \return BoundaryBox object of the type BoundaryBox.
         */
        virtual BoundaryBox getBoundaryBox() override;

        /** \brief Inherited from IMovingEntity. A virtual function that queries
         *  if a PlayerBullet object is still alive or not.
         *  \return bool
         */
        virtual bool isAlive() const override;

        /** \brief Inherited from IMovingEntity. A virtual function that sets the derived class
         *  object as not alive when killed.
         *  \return void
         */
        virtual void eliminated() override;

        /** \brief Inherited from IMovingEntity. A virtual function that can be
         *  used to bring PlayerBullet object back to life.
         *  \return void
         */
        virtual void reincarnate() override;

        /** \brief Inherited from IMovingEntity. A virtual function that
         *  will be used to return the remaining lives of a PlayerBullet object.
         *  \return int indicating the number of remaining lives.
         */
        virtual int getRemainingLives() const override;

        /** \brief Inherited from IMovingEntity. A virtual function that will be
         *  to return false for the poisoned status of a PlayerBullet object.
         *  \return bool
         */
        virtual bool isPoisoned() const override;

        /** \brief Inherited from IMovingEntity. A virtual function that will not
         *  be implemented as a PlayerBullet cannot be poisoned.
         */
        virtual void poison() override;

        /** \brief Inherited from IMovingEntity. A virtual function that will be
         *  not be implemented as a PlayerBullet doesn't have hit points.
         */
        virtual int getHitPoints() const override;

    private:
        bool alive_;
        Position position_;
        const Grid grid_;
        Direction direction_;
        static struct PlayerBulletDimensions dimensions_;
};

#endif // PLAYERBULLET_H
