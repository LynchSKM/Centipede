#ifndef SPIDER_H
#define SPIDER_H

#include "IMovingEntity.h"
#include "Dimensions.h"
#include "ObjectType.h"
#include "Grid.h"

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
         *  \return Direction an enum of the enum class Direction.
         */
        virtual Direction getDirection() const override;

        /** \brief Inherited from IMovingEntity. A virtual function that sets the
         *  direction of a Spider object.
         *  \param direction an enum of enum class Direction.
         */
        virtual void setDirection(Direction direction) = 0;

        /** \brief Inherited from IMovingEntity. A virtual function that returns
         *  a enum of ObjectType::SPIDER.
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

        /** \brief Inherited from IMovingEntity. A virtual function that will be
         *  used to bring a Spider object back to life.
         *  \return void
         */
        virtual void reincarnate() override;

        /** \brief Inherited from IMovingEntity. A virtual function that
         *  will be used to return the remaining lives of a Spider object.
         *  \return int containing the number of remaining lives.
         */
        virtual int getRemainingLives() const override;

        /** \brief Inherited from IMovingEntity. A virtual function that will be
         *  used to return the poisoned status of a Spider object.
         *  \return bool stating whether a Spider object is poisoned or not.
         */
        virtual bool isPoisoned() const override;

        /** \brief Inherited from IMovingEntity. A virtual function that will be
         *  used to poison a Spider object by changing the poisoned status to true.
         */
        virtual void poison() override;

    private:
        const Grid grid_;
        Position position_;
        Direction direction_;
        bool isAlive_;
        static struct SpiderDimensions dimensions_;
};

#endif // SPIDER_H
