#ifndef IENTITY_H
#define IENTITY_H

#include "ObjectType.h"
#include "BoundaryBox.h"
#include "POSITION.H"

/** \class IEntity
*   \brief This is a Interface Class containing pure virtual functions that
*   will be overridden by derived classes.
*   \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
*
*/

class IEntity
{
    public:
        /** \brief A pure virtual function that returns a enum of ObjectType of
        *   a derived class object.
        *   \return An enum of the strongly typed enum class ObjectType.
        */
        virtual ObjectType getObjectType() const = 0;

        /** \brief A pure virtual function that returns a Position of the
        *   derived class object.
        *   \return Position of the derived class object containing its current position.
        */
        virtual Position getPosition() const = 0;

        /** \brief A pure virtual function that returns a Rectangle indicating
        *   the rectangular area covered by a derived class object.
        *   \return A Rectangle object of the type Rectangle struct.
        */
        virtual BoundaryBox getBoundaryBox() = 0;

        /** \brief A pure virtual function that queries if a derived class object
        *   is still alive or not.
        *   \return bool
        */
        virtual bool isAlive() const = 0;

        /** \brief A pure virtual function that sets the derived class
        *   object as not alive when killed.
        *   \return void
        */
        virtual void eliminated() = 0;

        virtual ~IEntity(){};
};

#endif // IENTITY_H
