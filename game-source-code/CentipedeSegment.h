#ifndef CENTIPEDESEGMENT_H
#define CENTIPEDESEGMENT_H

#include "IMovingEntity.h"
#include "Dimensions.h"
#include "Grid.h"

#include <vector>
using std::vector;

/** \class CentipedeSegment
*   \brief This is a Class that inherits from the IMovingEntity class. It
*   contains pure virtual functions that will be overridden by derived.
*   \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
*   \version
*/

class CentipedeSegment : public IMovingEntity
{
    public:

        /** \brief is a strongly typed enum class representing the BodyType of the
         *  centipede.
         */
        enum class BodyType{
            HEAD = 0,/**< is coded as int of value 0. */
            BODY     /**< is coded as int of value 0. */
        };

        /** \brief Creates a centipede segment object parameterized constructor.
         * \param is a direction of type Direction enum class.
         * \param is a bodytype of type BodyType enum class.
         * \param is a objectType of type ObjectType enum class.
         * \param is a position of type Position.
         * \param is grid of type grid.
         */
        CentipedeSegment(Grid grid, BodyType bodytype, Position position, Direction cur_Direction);

        /** Destroys the CentipedeSegment object.
        */
        virtual~CentipedeSegment();

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

        /** \brief A function that returns the body type of the centipede segment.
         * \return The body type of the object of type BodyType of the enum class.
         */
        BodyType getBodyType() const;

        /** \brief A function that sets the body type of the centipede segment.
         *  \param body_type of type BodyType of the enum class.
         */
        void setBodyType(BodyType body_type);

        /** \brief A function that returns the rotation angle of the centipede segment.
         * \return The rotation angle of type float.
         */
        float getRotationAngle() const;

        /** \brief A function that saves positions where the head of centipede
         * train had a collision.
         */
        void collisionAt(Position position);

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
        bool isAtCellCentre_;
        vector<Position> head_collision_positions_;

        /** \brief controls the movements of the centipede segment upon entry.
         */
        bool isEntryMovement();

        /** \brief A function that decrements y axis of the object's position.
         */
        void moveUp();

        /** \brief A function that increments y axis of the object's position.
         */
        void moveDown();

        /** \brief A function that decrements x axis of the object's position.
         */
        void moveLeft();

        /** \brief A function that increments x axis of the object's position.
         */
        void moveRight();

        /** \brief Determines whether the CentipedeSegment has reached a position
         * where the head collided. If it has the changeDirection() function is called.
         */
        void checkHeadCollisions();

};

#endif // CENTIPEDESEGMENT_H
