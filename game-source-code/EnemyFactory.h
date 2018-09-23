#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H

#include <vector>
#include <memory>
#include "CentipedeSegment.h"
#include "MushroomFactory.h"
#include "Scorpion.h"

using std::vector;
using std::shared_ptr;
using std::make_shared;

/** \class EnemyFactory
 *  \brief creates all the enemy objects of the game
 *  \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
 *  \version
 */
class EnemyFactory
{
    public:

        /** \brief a parameterized constructor.
         * \param grid of type Grid.
         * \param
         */
        EnemyFactory(const Grid& grid);

        /** \brief destroys the enemy factory object.
         */
        ~EnemyFactory();

        /** \brief generates a centipede made up of centipede segments.
         * \return a vector of shared ptr to centipede segments.
         */
        vector <shared_ptr<CentipedeSegment>> generateNormalCentipede();

        /** \brief generates centipede heads.
         * \return a vector of shared ptr to centipede segments.
         */
        vector <shared_ptr<CentipedeSegment>> generateCentipedeHeads();

        /** \brief generates mushrooms at random positions.
         * \return a vector of shared ptr to mushrooms.
         */
        vector <shared_ptr<Mushroom>> generateMushrooms();

        /** \brief generates a mushrooms at a given position.
         * \param a position of type Position.
         * \return a shared ptr to a mushroom object.
         */
        shared_ptr<Mushroom> generateAMushroom(Position position);

        /** \brief generates a scorpion at a random position.
         * \return a shared ptr to a scorpion object.
         */
        vector <shared_ptr<Scorpion>> generateAScorpion();

        /** \brief Resets states of generated centipedes to false.
         */
         void reset();

    private:
        Grid grid_;
        int max_number_enemies_;
        bool isCentipedeGenerated_;
        bool isCentipedeHeadsGenerated_;
        bool isScorpionGenerated_;
        MushroomFactory mushroomfactory_;



};

#endif // ENEMYFACTORY_H
