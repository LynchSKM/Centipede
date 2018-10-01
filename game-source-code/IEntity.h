#ifndef IENTITY_H
#define IENTITY_H

#include "ObjectType.h"
#include "BoundaryBox.h"
#include "POSITION.H"

/** \class IEntity
 *  \brief This is a Interface Class containing pure virtual functions that
 *  will be overridden by derived classes.
 *  \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
 *  \version 3.0
 */

class IEntity
{
    public:
        /** \brief A pure virtual function that returns a enum of ObjectType of
         *  a derived class object.
         *  \return ObjectType enum of the strongly typed enum class ObjectType.
         */
        virtual ObjectType getObjectType() const = 0;

        /** \brief A pure virtual function that returns a Position of the
         *  derived class object.
         *  \return Position of the derived class object containing its current position.
         */
        virtual Position getPosition() const = 0;

        /** \brief A pure virtual function that returns a BoundaryBox indicating
         *  the rectangular area covered by a derived class object.
         *  \return BoundaryBox object of the type BoundaryBox.
         */
        virtual BoundaryBox getBoundaryBox() = 0;

        /** \brief A pure virtual function that queries if a derived class object
         *  is still alive or not.
         *  \return bool
         */
        virtual bool isAlive() const = 0;

        /** \brief A pure virtual function that sets the derived class object as
         *  not alive when killed.
         *  \return void
         */
        virtual void eliminated() = 0;

        /** \brief A pure virtual function that will be used to bring a derived
         *  class object back to life.
         *  \return void
         */
        virtual void reincarnate() = 0;

        /** \brief A pure virtual function that will be used to return the remaining
         *  lives of a derived class object.
         *  \return int containing the number of remaining lives.
         */
        virtual int getRemainingLives() const = 0;

        /** \brief A pure virtual function that will be used to return the poisoned
         *  status of the derived class objects.
         *  \return bool stating whether the derived class object is poisoned or not.
         */
        virtual bool isPoisoned() const = 0;

        /** \brief A pure virtual function that will be used to poison a
         *  derived class object by changing the poisoned status to true.
         */
        virtual void poison() = 0;

        /** \brief A pure virtual function that will be used to return a
         *  derived class object's hit points.
         */
        virtual int getHitPoints() const = 0;

        /** \brief A virtual destructor that destroys an IEntity object.
         */
        virtual ~IEntity(){};
};

#endif // IENTITY_H
