#ifndef CENTIPEDESEGMENT_H
#define CENTIPEDESEGMENT_H

#include "IMovingEntity.h"
#include "Grid.h"

#include <algorithm>
#include <vector>
using std::vector;

/** \struct CentipedeSegmentDemensions
 *	\brief Contains information about a CentipedeSegment's height, width and speed.
 *  \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
 *	\version 3.0
 */
struct CentipedeSegmentDemensions
{
    const float height = 14.0;
    const float width  = 14.0;
    const float speed  = 1.0;
    const float speedY = 16.0;
};

/** \class CentipedeSegment
 *  \brief This is a class that inherits from the IMovingEntity class. It
 *  contains virtual functions that will be overridden by CentipedeSegment class.
 *  \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
 *  \version 3.0
 */

class CentipedeSegment : public IMovingEntity
{
    public:

        /** \enum BodyType
         *  \brief A strongly typed enum class representing the BodyType of the
         *  centipede.
         *	\author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
         *	\version 3.0
         */
        enum class BodyType
        {
            HEAD = 0,/**< Represents whether a CentipedeSegment is a head.*/
            BODY     /**< Represents whether a CentipedeSegment is a body.*/
        };

        /** \brief Parameterized Constructor. Creates a centipede segment object.
         *  \param grid is of type grid.
         *  \param bodytype is of type BodyType enum class.
         *  \param position is of type Position.
         *  \param cur_Direction is of type Direction enum class.
         */
        CentipedeSegment(const Grid& grid, BodyType bodytype, Position position, Direction cur_Direction);

        /** \brief Virtual Destructor. Destroys a CentipedeSegment object.
         */
        virtual~CentipedeSegment();

        /** \brief Inherited from IMovingEntity. A virtual function that moves a CentipedeSegment object.
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
         *  a centre position of the CentipedeSegment object.
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

        /** \brief Inherited from IMovingEntity. A virtual function that will not
         *	be implemented because CentipedeSegment objects have one life only.
         */
		virtual void reincarnate() override;

        /** \brief Inherited from IMovingEntity. A virtual function that will be
         *  used to return the poisoned status of the CentipedeSegment objects.
         *  \return bool stating whether the CentipedeSegment object is poisoned or not.
         */
        virtual bool isPoisoned() const override;

        /** \brief Inherited from IMovingEntity. A virtual function that will be
         *  used to poison a CentipedeSegment object by changing the poisoned status to true.
         */
        virtual void poison() override;

        /** \brief Inherited from IMovingEntity. A virtual function that will be
         *  used to return a CentipedeSegment object's hit points.
         */
        virtual int getHitPoints() const override;

        /** \brief A function that returns the previous direction of an object.
         *  \return The direction of the object of type Direction of the enum class.
         */
        Direction getPrevDirection() const;

        /** \brief A function that changes the direction of the object to Down, this
         *  is called when a collision is detected in front of an object.
         */
        void changeDirection();

        /** \brief A function that returns the body type of the centipede segment.
         *  \return The body type of the object of type BodyType of the enum class.
         */
        BodyType getBodyType() const;

        /** \brief A function that sets the body type of the centipede segment.
         *  \param body_type is of type BodyType of the enum class.
         */
        void setBodyType(BodyType body_type);

        /** \brief A function that returns the rotation angle of the centipede segment.
         *  \return The rotation angle of type float.
         */
        float getRotationAngle() const;

        /** \brief A function that saves positions where the head of centipede
         *  train had a collision.
         */
        void collisionAt(Position position, bool poisionedCollision);

        /** \brief A function that clears the vector of positions where the head of centipede
         *  train had a collision.
         */
        void clearHeadCollisions();

    private:
        Direction cur_Direction_;
        Direction prev_Direction_;
        BodyType bodytype_;
        Position position_;
        const Grid grid_;
        float rotationAngle_ = 0.0;
        bool isPoisoned_ = false;
        bool isPoisonedMovementComplete_ = false;
        bool alive_ = true;
        int moveDownCount_;
        bool changeWhenPoisoned_;
        bool centAtbottom_;
        vector<Position> head_collision_positions_;
        vector<bool> are_head_collision_positions_poisioned_;
        static struct CentipedeSegmentDemensions dimensions_;

        /** \brief Controls the movements of the centipede segment upon entry.
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
         *  where the head collided. If it has the changeDirection() function is called.
         */
        void checkHeadCollisions();

        /** \brief Moves the centipede segment accordingly when it is poisoned.
         */
        void isPoisonedMovement();
};

#endif // CENTIPEDESEGMENT_H
