#ifndef IMOVINGENTITY_H
#define IMOVINGENTITY_H

#include "IEntity.h"
#include "ObjectType.h"
#include "BoundaryBox.h"
#include "POSITION.H"
#include "Direction.h"

/** \class IMovingEntity
*   \brief This is a Interface Class that inherits from the IEntity class. It
*   contains pure virtual functions that will be overridden by derived classes.
*   \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
*   \version
*/

class IMovingEntity: public IEntity
{
    public:

        /** A pure virtual function that moves derived class objects.
         */
        virtual void move() = 0;

        /** \brief A pure virtual function that returns the direction of an object.
         * \return Direction an enum of the enum class Direction.
         */
        virtual Direction getDirection() const = 0;

        /** \brief A pure virtual function that sets the direction of an object.
         * \param direction an enum of enum class Direction.
         */
        virtual void setDirection(Direction direction) = 0;

        /** \brief Inherited from IEntity. A pure virtual function that returns a enum of ObjectType of
         *  a derived class object.
         *  \return An enum of the strongly typed enum class ObjectType.
         */
        virtual ObjectType getObjectType() const = 0;

        /** \brief Inherited from IEntity. A pure virtual function that returns a Position of the
         *  derived class object.
         *  \return Position of the derived class object containing its current position.
         */
        virtual Position getPosition() const = 0;

        /** \brief Inherited from IEntity. A pure virtual function that returns a BoundaryBox indicating
         *  the rectangular area covered by a derived class object.
         *  \return BoundaryBox object of the type BoundaryBox.
         */
        virtual BoundaryBox getBoundaryBox() = 0;

        /** \brief Inherited from IEntity. A pure virtual function that queries if a derived class object
         *  is still alive or not.
         *  \return bool
         */
        virtual bool isAlive() const = 0;

        /** \brief Inherited from IEntity. A pure virtual function that sets the derived class
         *  object as not alive when killed.
         *  \return void
         */
        virtual void eliminated() = 0;

        /** \brief Inherited from IEntity. A pure virtual function that will be
         *  used to bring derived class objects back to life.
         *  \return void
         */
        virtual void reincarnate() = 0;

        /** \brief Inherited from IMovingEntity. A pure virtual function that
         *  will be used to return the remaining lives of a derived class object.
         *  \return int containing the number of remaining lives.
         */
        virtual int getRemainingLives() const = 0;

        /** \brief A virtual destructor that destroys an IMovingEntity object.
         */
        virtual ~IMovingEntity(){};
};

#endif // IMOVINGENTITY_H
