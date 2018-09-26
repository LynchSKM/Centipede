#ifndef SCORPION_H
#define SCORPION_H

#include "IMovingEntity.h"
#include "Dimensions.h"
#include "Grid.h"

/** \class Scorpion
 *  \brief This is a class that inherits from the IMovingEntity class. It models
 *  a Scorpion object in the game. It contains virtual functions that
 *  will be overridden.
 *  \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
 *  \version 3.0
 */

class Scorpion : public IMovingEntity
{
    public:

        /** \brief Parameterized Constructor. Creates a Scorpion object.
         *  \param grid of type Grid.
         */
        Scorpion(const Grid& grid);

        /** Virtual Destructor. Destroys a Scorpion object.
         */
        virtual ~Scorpion();

        /** \brief Inherited from IMovingEntity. A virtual function that
         *  moves a scorpion object.
         */
        virtual void move() override;

        /** \brief Inherited from IMovingEntity. A virtual function that
         *  returns the direction of a scorpion object.
         *  \return Direction an enum of type enum class Direction.
         */
        virtual Direction getDirection() const override;

        /** \brief Inherited from IMovingEntity. A virtual function that sets
         *  the direction of a scorpion object.
         *  \param direction an enum of enum class Direction.
         */
        virtual void setDirection(Direction direction) override;

        /** \brief Inherited from IMovingEntity. A virtual function that returns a
         *  enum ObjectType::SCORPION of ObjectType of a scorpion object.
         *  \return ObjectType an enum of the strongly typed enum class ObjectType.
         */
        virtual ObjectType getObjectType() const override;

        /** \brief Inherited from IMovingEntity. A virtual function that returns
         *  a Position of the scorpion object.
         *  \return Position of the scorpion object.
         */
        virtual Position getPosition() const override;

        /** \brief Inherited from IMovingEntity. A virtual function that returns a BoundaryBox indicating
         *  the rectangular area covered by a scorpion object.
         *  \return BoundaryBox object of the type BoundaryBox.
         */
        virtual BoundaryBox getBoundaryBox() override;

        /** \brief Inherited from IMovingEntity. A virtual function that queries
         *  if a scorpion object is still alive or not.
         *  \return bool
         */
        virtual bool isAlive() const override;

        /** \brief Inherited from IMovingEntity. A virtual function that sets the Scorpion
         *  object as not alive when killed.
         *  \return void
         */
        virtual void eliminated() override;

        /** \brief Inherited from IMovingEntity. A virtual function that can be
         *  used to bring scorpion object back to life.
         *  \return void
         */
        virtual void reincarnate() override;

        /** \brief Inherited from IMovingEntity. A virtual function that
         *  will be used to return the remaining lives of a scorpion object.
         *  \return int containing the number of remaining lives.
         */
        virtual int getRemainingLives() const override;

        /** \brief Inherited from IMovingEntity. A virtual function that will be
         *  used to return the poisoned status of a scorpion object.
         *  \return bool stating whether the scorpion object is poisoned or not.
         */
        virtual bool isPoisoned() const override;

        /** \brief Inherited from IMovingEntity. A virtual function that will be
         *  used to poison a scorpion object by changing the poisoned status to true.
         */
        virtual void poison() override;

    private:

        const Grid grid_;
        Position position_;
        Direction direction_;
        bool isAlive_;

        /** \brief A function that decrements x axis of the object's position
         *  such that it moves left.
         */
        void moveLeft();

        /** \brief A function that increments x axis of the object's position.
         *  such that it moves right.
         */
        void moveRight();
};

#endif // SCOPION_H
