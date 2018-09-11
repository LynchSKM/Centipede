#ifndef MUSHROOM_H
#define MUSHROOM_H

#include "IEntity.h"
#include "Dimensions.h"

/** \class IEntity
*   \brief This is a Class containing pure virtual functions that
*   will be overridden.
*   \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
*   \version
*/
class Mushroom : public IEntity
{
    public:

        /** \brief creates a mushroom object, parameterized constructor.
         * \param is grid of type grid.
         */
        Mushroom(Position position);

        /** \brief destroys the mushroom object.
         */
        ~Mushroom();

        /** \brief Inherited from IEntity. A pure virtual function that returns a enum of ObjectType of
        *   a derived class object.
        *   \return An enum of the strongly typed enum class ObjectType.
        */
        virtual ObjectType getObjectType() const override;

        /** \brief Inherited from IEntity. A pure virtual function that returns a Position of the
        *   derived class object.
        *   \return Position of the derived class object containing its current position.
        */
        virtual Position getPosition() const override;

        /** \brief Inherited from IEntity. A pure virtual function that returns a Rectangle indicating
        *   the rectangular area covered by a derived class object.
        *   \return A Rectangle object of the type Rectangle struct.
        */
        virtual BoundaryBox getBoundaryBox() override;

        /** \brief Inherited from IEntity. A pure virtual function that queries if a derived class object
        *   is still alive or not.
        *   \return bool
        */
        virtual bool isAlive() const override;

        /** \brief Inherited from IEntity. A pure virtual function that sets the derived class
        *   object as not alive when killed.
        *   \return void
        */
        virtual void eliminated() override;

        /** \brief decrements the lives of the mushroom.
         */
        void decrementLives();

        /** \brief returns the health status of the mushroom.
         *  \return a bool stating whether the mushroom is poisoned or not.
         */
        bool isPoisoned() const;

        /** \brief poisons the mushroom by changing the isPoisoned private member
         *  to true.
         */
        void poison();

        /** \brief returns the number of remaining lives.
         *  \return number of lives of type int.
         */
        int getRemainingLives() const;


    private:
        Position position_;
        ObjectType objectType_;
        bool isPoisoned_;
        bool isAlive_;
        int numberOfLives_;

};

#endif // MUSHROOM_H
