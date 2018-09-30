#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H

#include "CentipedeSegment.h"
#include "MushroomFactory.h"
#include "Scorpion.h"
#include "Spider.h"

#include <vector>
#include <memory>
#include <ctime>
using std::vector;
using std::shared_ptr;
using std::make_shared;

/** \class EnemyFactory
 *  \brief Creates all the enemy objects of the game and Mushrooms.
 *  \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
 *  \version 3.0
 */
class EnemyFactory
{
    public:

        /** \brief Parameterized constructor. Creates an EnemyFactory object.
         *  \param grid of type Grid.
         */
        EnemyFactory(const Grid& grid);

        /** \brief Destroys a EnemyFactory object.
         */
        ~EnemyFactory();

        /** \brief Generates a Centipede made up of centipede segments.
         *  \return vector<shared_ptr<CentipedeSegment>>
         */
        vector <shared_ptr<CentipedeSegment>> generateNormalCentipede();

        /** \brief Generates centipede heads.
         *  \return vector<shared_ptr<CentipedeSegment>>
         */
        vector <shared_ptr<CentipedeSegment>> generateCentipedeHeads();

        /** \brief Generates mushrooms at random positions.
         *  \return vector<shared_ptr<Mushroom>>
         */
        vector <shared_ptr<Mushroom>> generateMushrooms();

        /** \brief Generates a mushrooms at a given position.
         *  \param position is of type Position.
         *  \return shared_ptr<Mushroom>
         */
        shared_ptr<Mushroom> generateAMushroom(Position position);

        /** \brief Generates a scorpion at a random position.
         *  \return vector<shared ptr<Scorpion>>
         */
        vector <shared_ptr<Scorpion>> generateAScorpion();

        /** \brief Generates a spider periodically.
         *  \return vector<shared ptr<Spider>>
         */
        vector <shared_ptr<Spider>> generateASpider();

        /** \brief Resets states of generated objects to false.
         */
         void reset();

    private:
        const Grid grid_;
        int max_number_enemies_;
        bool isCentipedeGenerated_;
        bool isCentipedeHeadsGenerated_;
        bool isScorpionGenerated_;
        bool isSpiderGenerated_;
        MushroomFactory mushroomfactory_;
};

#endif // ENEMYFACTORY_H
