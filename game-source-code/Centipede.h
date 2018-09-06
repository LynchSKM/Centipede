#ifndef CENTIPEDE_H
#define CENTIPEDE_H

#include "IMovingEntity.h"
#include "Dimensions.h"
#include "Grid.h"


class Centipede : public IMovingEntity
{
    public:

        enum class BodyType{
            HEAD = 0,
            BODY
        };
        Centipede(Direction cur_Direction, BodyType bodytype, ObjectType objectType,Position position,Grid grid);
        ~Centipede();


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

        /** \brief A function that changes the isPoisoned status of the object to true.
         */
        void poison();

        /** \brief A function that returns the previous direction of an object.
         * \return The direction of the object of type Direction of the enum class.
         */
        Direction getPrevDirection() const;

        /** \brief A function that changes the direction of the object to Down, this
        *   is called when a collision is detected in front of an object.
         */
        void changeDirection();


    private:
        Direction cur_Direction_;
        Direction prev_Direction_;
        BodyType bodytype_;
        ObjectType objectType_;
        Position position_;
        const Grid grid_;
        float rotationAngle_ = 0.0;
        bool isPosoned_ = false;
        bool alive_ = true;
        void moveUp(float newYPos);
        void moveDown(float newYPos);
        void moveLeft(float newXPos);
        void moveRight(float newXPos);
};

#endif // CENTEPEDE_H
