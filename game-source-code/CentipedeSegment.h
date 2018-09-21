#ifndef CENTIPEDESEGMENT_H
#define CENTIPEDESEGMENT_H

#include "IMovingEntity.h"
#include "Dimensions.h"
#include "Grid.h"

#include <algorithm>
#include <vector>
using std::vector;

/** \class CentipedeSegment
*   \brief This is a Class that inherits from the IMovingEntity class. It
*   contains virtual functions that will be overridden by CentipedeSegment class.
*   \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
*   \version
*/

class CentipedeSegment : public IMovingEntity
{
    public:

        /** \enum BodyType
         *  \brief A strongly typed enum class representing the BodyType of the
         *  centipede.
         */
        enum class BodyType{
            HEAD = 0,/**< is coded as int of value 0. */
            BODY     /**< is coded as int of value 0. */
        };

        /** \brief Parameterized Constructor. Creates a centipede segment object.
         *  \param is a direction of type Direction enum class.
         *  \param is a bodytype of type BodyType enum class.
         *  \param is a objectType of type ObjectType enum class.
         *  \param is a position of type Position.
         *  \param is grid of type grid.
         */
        CentipedeSegment(const Grid& grid, BodyType bodytype, Position position, Direction cur_Direction);

        /** Virtual Destructor. Destroys a CentipedeSegment object.
         */
        virtual~CentipedeSegment();

        /** Inherited from IMovingEnity. A virtual function that moves a CentipedeSegment object.
         */
        virtual void move() override;

        /** \brief Inherited from IMovingEntity. A virtual function that
         *  returns the current direction of a CentipedeSegment object.
         *  \return Direction an enum of the enum class Direction.
         */
        virtual Direction getDirection() const override;

        /** \brief Inherited from IMovingEntity. A virtual function that sets
         *  the direction of a CentipedeSegment object.
         *  \param direction an enum of enum class Direction.
         */
        virtual void setDirection(Direction direction) override;

        /** \brief Inherited from IMovingEntity. A virtual function that returns
         *  a enum of ObjectType of a CentipedeSegment object.
         *  \return An enum of the strongly typed enum class ObjectType.
         */
        virtual ObjectType getObjectType() const override;

        /** \brief Inherited from IMovingEntity. A virtual function that returns
         * a centre position of the CentipedeSegment object.
         *  \return Position of the CentipedeSegment object containing its current position.
         */
        virtual Position getPosition() const override;

        /** \brief Inherited from IMovingEntity. A virtual function that returns
         *  a BoundaryBox indicating the rectangular area covered by a CentipedeSegment object.
         *  \return BoundaryBox object of the type BoundaryBox.
         */
        virtual BoundaryBox getBoundaryBox() override;

        /** \brief Inherited from IMovingEntity. A virtual function that queries
         *  if a CentipedeSegment object is still alive or not.
         *  \return bool
         */
        virtual bool isAlive() const override;

        /** \brief Inherited from IMovingEntity. A virtual function that sets the CentipedeSegment
         *  object as not alive when killed.
         *  \return void
         */
        virtual void eliminated() override;

        /** \brief Inherited from IMovingEntity. A virtual function that
         *  gets a constant copy of the CentipedeSegment object's number of lives left.
         *  \return int containing the number of lives.
         */
        virtual int getRemainingLives() const override;

        /** \brief Inherited from IMovingEntity. A virtual function that will be
         * used to bring the CentipedeSegment object back to life, if the remaining lives
         * are not zero.
         */
		virtual void reincarnate() override;

        /** \brief A function that changes the isPoisoned status of the object to true.
         */
        void poison();

        /** \brief A function that returns the previous direction of an object.
         *  \return The direction of the object of type Direction of the enum class.
         */
        Direction getPrevDirection() const;

        /** \brief A function that changes the direction of the object to Down, this
         *   is called when a collision is detected in front of an object.
         */
        void changeDirection();

        /** \brief A function that returns the body type of the centipede segment.
         *  \return The body type of the object of type BodyType of the enum class.
         */
        BodyType getBodyType() const;

        /** \brief A function that sets the body type of the centipede segment.
         *  \param body_type of type BodyType of the enum class.
         */
        void setBodyType(BodyType body_type);

        /** \brief A function that returns the rotation angle of the centipede segment.
         *  \return The rotation angle of type float.
         */
        float getRotationAngle() const;

        /** \brief A function that saves positions where the head of centipede
         * train had a collision.
         */
        void collisionAt(Position position);

        void clearHeadCollisions();
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
