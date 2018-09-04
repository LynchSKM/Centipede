#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "IMovingEntity.h"
#include "Direction.h"
#include "Grid.h"

/** \class Player
*   \brief This is a Player Class that inherits from the IMovingEntity class. It
*   contains virtual functions that have been overridden.
*   \details
*   \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
*
*/
class Player : public IMovingEntity
{
    public:
        Player();
        ~Player();

        /** \brief Inherited from IMovingEntity. A pure virtual function that moves derived class objects.
        */
        virtual void move() override;

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
        virtual Rectangle getBoundaryBox() override;

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

        /** \brief
         * \param
         */
        void setDirection(Direction direction);

        /** \brief gets a constant copy of the object's direction
         * \return
         */
        int getRemainingLives() const;

        /** \brief
         * \return
         */
        std::vector <IMovingEntity> shoot();


    private:

        int numberOfLives_;
        auto score = 0;
        Grid grid_;
        Position position_;
        Direction direction_;
        struct Rectangle boundaryBox_;


};

#endif // PLAYER_H
