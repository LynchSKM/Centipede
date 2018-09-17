#ifndef PLAYERBULLET_H
#define PLAYERBULLET_H

#include "IMovingEntity.h"
#include "Dimensions.h"
#include "Grid.h"

/** \class PlayerBullet
*   \brief This is a Class that inherits from the IMovingEntity class. It
*   contains pure virtual functions that will be overridden by derived.
*   \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
*
*/

class PlayerBullet : public IMovingEntity
{
    public:


        /** \brief Creates a playerBullet object parameterized constructor.
         * \param is position of type Position.
         */
        PlayerBullet(Position position, Grid grid);

        /** Destroys the playerbullet object.
        */
        virtual ~PlayerBullet();
        /** A pure virtual function that moves derived class objects.
        */
        virtual void move() override;

        /** \brief A pure virtual function that returns the direction of an object.
         * \return The direction of the object of type Direction of the enum class.
         */
        virtual Direction getDirection() const override;

        /** \brief A pure virtual function that sets the direction of an object.
         * \param direction of type Direction of the enum class.
         */
        virtual void setDirection(Direction direction) override;

        /** \brief Inherited from IMovingEntity. A pure virtual function that returns a enum of ObjectType of
        *   a derived class object.
        *   \return An enum of the strongly typed enum class ObjectType.
        */
        virtual ObjectType getObjectType() const override;

        /** \brief Inherited from IMovingEntity. A pure virtual function that returns a Position of the
        *   derived class object.
        *   \return Position of the derived class object containing its current position.
        */
        virtual Position getPosition() const override;

        /** \brief Inherited from IMovingEntity. A pure virtual function that returns a Rectangle indicating
        *   the rectangular area covered by a derived class object.
        *   \return A Rectangle object of the type Rectangle struct.
        */
        virtual BoundaryBox getBoundaryBox() override;

        /** \brief Inherited from IMovingEntity. A pure virtual function that queries if a derived class object
        *   is still alive or not.
        *   \return bool
        */
        virtual bool isAlive() const override;

        /** \brief Inherited from IMovingEntity. A pure virtual function that sets the derived class
        *   object as not alive when killed.
        *   \return void
        */
        virtual void eliminated() override;

    private:
        bool alive_;
        ObjectType objectType_;
        Position position_;
        const Grid grid_;
        Direction direction_;

};

#endif // PLAYERBULLET_H
