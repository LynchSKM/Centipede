#ifndef SPIDER_H
#define SPIDER_H

#include "IMovingEntity.h"
#include "ObjectType.h"
#include "Grid.h"

/** \struct SpiderDimensions
 *	\brief Contains information about a Spider's height, width and speed.
 *  \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
 *	\version 3.0
 */
struct SpiderDimensions
{
    const float height = 16.0;
    const float width = 30.0;
    const float speed = 0.8;
};

/** \class Spider
 *  \brief This is a class that inherits from the IMovingEntity class. It models
 *  a Spider object in the game. It contains virtual functions that
 *  will be overridden.
 *  \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
 *  \version 3.0
 */

class Spider : public IMovingEntity
{
    public:
        /** \brief Parameterized Constructor. Creates a Spider object.
         *  \param grid is of type Grid and contains screen width and height.
         */
        Spider(const Grid& grid);

        /** \brief Virtual Destructor. Destroys a Spider object.
         */
        virtual ~Spider();

        /** \brief Inherited from IMovingEntity. A virtual function that moves
         *  a Spider object.
         */
        virtual void move() override;

        /** \brief Inherited from IMovingEntity. A virtual function that returns
         *  the direction of a Spider object.
         *  \return Direction an enum of type enum class Direction.
         */
        virtual Direction getDirection() const override;

        /** \brief Inherited from IMovingEntity. A virtual function that sets the
         *  direction of a Spider object.
         *  \param direction an enum of enum class Direction.
         */
        virtual void setDirection(Direction direction)override;

        /** \brief Inherited from IMovingEntity. A virtual function that returns
         *  an enum of ObjectType::SPIDER.
         *  \return ObjectType an enum of the strongly typed enum class ObjectType.
         */
        virtual ObjectType getObjectType() const override;

        /** \brief Inherited from IMovingEntity. A virtual function that returns
         *  a Position of a Spider object.
         *  \return Position of a Spider object.
         */
        virtual Position getPosition() const override;

        /** \brief Inherited from IMovingEntity. A virtual function that returns a
         *  BoundaryBox indicating the rectangular area covered by a Spider object.
         *  \return BoundaryBox object of the type BoundaryBox.
         */
        virtual BoundaryBox getBoundaryBox() override;

        /** \brief Inherited from IMovingEntity. A virtual function that queries
         *  if a Spider object is still alive or not.
         *  \return bool
         */
        virtual bool isAlive() const override;

        /** \brief Inherited from IMovingEntity. A virtual function that sets
         *  a Spider object as not alive when killed.
         *  \return void
         */
        virtual void eliminated() override;

        /** \brief Inherited from IMovingEntity. A virtual function that will not
         *  be implemented because a Spider only has one life.
         *  \return void
         */
        virtual void reincarnate() override;

        /** \brief Inherited from IMovingEntity. A virtual function that
         *  will be used to return the remaining lives of a Spider object.
         *  \return int indicating the number of remaining lives.
         */
        virtual int getRemainingLives() const override;

        /** \brief Inherited from IMovingEntity. A virtual function that will be
         *  to return false for the poisoned status of a Spider object.
         *  \return bool
         */
        virtual bool isPoisoned() const override;

        /** \brief Inherited from IMovingEntity. A virtual function that will not
         *  be implemented because a Spider cannot be poisoned.
         */
        virtual void poison() override;

        /** \brief Inherited from IMovingEntity. A virtual function that will be
         *  used to return a Spider object's hit points.
         */
        virtual int getHitPoints() const override;

    private:
        const Grid grid_;
        Position position_;
        Direction major_direction_;
        Direction movementDirection_;
        bool isAlive_;
        bool turningPointAvailable_;
        double slope_;
        Position turningPoint_;
        static struct SpiderDimensions dimensions_;

        /** \brief A function that modifies the position of the object such that the
         * 	object moves up.
         */
        void moveUp();

        /** \brief A function that modifies the position of the object such that the
         * 	object moves down.
         */
        void moveDown();

        /** \brief Generates the next turning point and gets the slope of the line
         * 	to that point.
         */
        void CalculateSlope();
};

#endif // SPIDER_H
