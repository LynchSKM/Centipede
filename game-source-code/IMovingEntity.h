#ifndef IMOVINGENTITY_H
#define IMOVINGENTITY_H

#include "IEntity.h"
#include "ObjectType.h"
#include "Rectangle.h"
#include "POSITION.H"

/** \class IMovingEntity
*   \brief This is a Interface Class that inherits from the IEntity class. It
*   contains pure virtual functions that will be overridden by derived classes.
*   \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
*
*/

class IMovingEntity: public IEntity
{
    public:

        /** A pure virtual function that moves derived class objects.
        */
        virtual void move() = 0;

        /** \brief A pure virtual function that returns the direction of an object.
         * \return The direction of the object of type Direction of the enum class.
         */
        virtual Direction getDirection() const = 0;

        /** \brief A pure virtual function that sets the direction of an object.
         * \param direction of type Direction of the enum class.
         */
        virtual void setDirection(Direction direction) = 0;

        /** \brief Inherited from IEntity. A pure virtual function that returns a enum of ObjectType of
        *   a derived class object.
        *   \return An enum of the strongly typed enum class ObjectType.
        */
        virtual ObjectType getObjectType() const = 0;

        /** \brief Inherited from IEntity. A pure virtual function that returns a Position of the
        *   derived class object.
        *   \return Position of the derived class object containing its current position.
        */
        virtual Position getPosition() const = 0;

        /** \brief Inherited from IEntity. A pure virtual function that returns a Rectangle indicating
        *   the rectangular area covered by a derived class object.
        *   \return A Rectangle object of the type Rectangle struct.
        */
        virtual Rectangle getBoundaryBox() = 0;

        /** \brief Inherited from IEntity. A pure virtual function that queries if a derived class object
        *   is still alive or not.
        *   \return bool
        */
        virtual bool isAlive() const = 0;

        /** \brief Inherited from IEntity. A pure virtual function that sets the derived class
        *   object as not alive when killed.
        *   \return void
        */
        virtual void eliminated() = 0;
};

#endif // IMOVINGENTITY_H
