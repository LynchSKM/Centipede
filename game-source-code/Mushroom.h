#ifndef MUSHROOM_H
#define MUSHROOM_H

#include "IEntity.h"

/** \struct MushroomDimensions
 *	\brief Contains information about a Mushroom's height, and width.
 *  \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
 *	\version 3.0
 */
struct MushroomDimensions
{
    const float height = 15.0;
    const float width = 16.0;

};

/** \class Mushroom
 *  \brief This is a class that defines a Mushroom object. It contains virtual functions
 *  inherited from IEntity that will be overridden. A Mushroom object has four lives, and
 *  it can be poisoned.
 *  \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
 *  \version 3.0
 */
class Mushroom : public IEntity
{
    public:

        /** \brief Parameterized Constructor. Creates a Mushroom object.
         *  \param position the centre point where the Mushroom is located on the screen.
         */
        Mushroom(Position position);

        /** \brief Virtual Destructor. Destroys a Mushroom object.
         */
        virtual ~Mushroom();

        /** \brief Inherited from IEntity. A virtual function that returns a enum
         *  ObjectType::MUSHROOM of ObjectType of a object.
         *  \return ObjectType an enum of the strongly typed enum class ObjectType.
         */
        virtual ObjectType getObjectType() const override;

        /** \brief Inherited from IEntity. A virtual function that returns a Position of the
         *  Mushroom object.
         *  \return Position of the Mushroom object.
         */
        virtual Position getPosition() const override;

        /** \brief Inherited from IEntity. A virtual function that returns a BoundaryBox indicating
         *  the rectangular area covered by the Mushroom object.
         *  \return BoundaryBox object of the type BoundaryBox.
         */
        virtual BoundaryBox getBoundaryBox() override;

        /** \brief Inherited from IEntity. A virtual function that queries if a Mushroom object
         *  is still alive or not.
         *  \return bool
         */
        virtual bool isAlive() const override;

        /** \brief Inherited from IEntity. A virtual function that sets the Mushroom
         *  object as not alive when killed.
         *  \return void
         */
        virtual void eliminated() override;

        /** \brief Inherited from IEntity. A virtual function that will be used
         *  to set a Mushroom object's number lives to full.
         *  \return void
         */
        virtual void reincarnate() override;

        /** \brief Inherited from IEntity. A virtual function that will be used
         *  to return the remaining lives of a Mushroom object.
         *  \return int containing the number of remaining lives.
         */
        virtual int getRemainingLives() const override;

        /** \brief Inherited from IEntity. A virtual function that will be used
         *  to return the poisoned status of a Mushroom object.
         *  \return bool stating whether the Mushroom object is poisoned or not.
         */
        virtual bool isPoisoned() const override;

        /** \brief Inherited from IEntity. A virtual function that will be used
         *  to poison a Mushroom object by changing the poisoned status to true.
         */
        virtual void poison() override;

        /** \brief Inherited from IEntity. A virtual function that will be
         *  used to return a Mushroom object's hit points.
         *  \return int
         */
        virtual int getHitPoints() const override;

    private:
        Position position_;
        bool isPoisoned_;
        bool isAlive_;
        int numberOfLives_;
        static struct MushroomDimensions dimensions_;

        /** \brief Decrements the lives of the mushroom.
         */
        void decrementLives();
};

#endif // MUSHROOM_H
