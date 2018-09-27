#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H

#include <vector>
#include <memory>
#include <ctime>
#include "CentipedeSegment.h"
#include "MushroomFactory.h"
#include "Scorpion.h"
#include "Spider.h"

using std::vector;
using std::shared_ptr;
using std::make_shared;

/** \class EnemyFactory
 *  \brief creates all the enemy objects of the game
 *  \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
 *  \version 3.0
 */
class EnemyFactory
{
    public:

        /** \brief Parameterized constructor.
         *  \param grid of type Grid.
         *  \param
         */
        EnemyFactory(const Grid& grid);

        /** \brief Destroys the enemy factory object.
         */
        ~EnemyFactory();

        /** \brief Generates a centipede made up of centipede segments.
         *  \return a vector of shared ptr to centipede segments.
         */
        vector <shared_ptr<CentipedeSegment>> generateNormalCentipede();

        /** \brief Generates centipede heads.
         *  \return a vector of shared ptr to centipede segments.
         */
        vector <shared_ptr<CentipedeSegment>> generateCentipedeHeads();

        /** \brief Generates mushrooms at random positions.
         *  \return a vector of shared ptr to mushrooms.
         */
        vector <shared_ptr<Mushroom>> generateMushrooms();

        /** \brief Generates a mushrooms at a given position.
         *  \param a position of type Position.
         *  \return a shared ptr to a mushroom object.
         */
        shared_ptr<Mushroom> generateAMushroom(Position position);

        /** \brief Generates a scorpion at a random position.
         *  \return vector<shared ptr<Scorpion>> to a scorpion object(s).
         */
        vector <shared_ptr<Scorpion>> generateAScorpion();

        /** \brief Generates a spider periodically.
         *  \return vector<shared ptr<Spider>> to a spider object(s).
         */
        vector <shared_ptr<Spider>> generateASpider();

        /** \brief Resets states of generated centipedes to false.
         */
         void reset();

    private:
        Grid grid_;
        int max_number_enemies_;
        bool isCentipedeGenerated_;
        bool isCentipedeHeadsGenerated_;
        bool isScorpionGenerated_;
        bool isSpiderGenerated_;
        MushroomFactory mushroomfactory_;



};

#endif // ENEMYFACTORY_H
