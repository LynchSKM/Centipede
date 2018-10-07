#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H

#include "CentipedeSegment.h"
#include "MushroomFactory.h"
#include "Scorpion.h"
#include "Spider.h"
#include "StopWatch.h"

#include <vector>
#include <memory>
#include <ctime>
using std::vector;
using std::shared_ptr;
using std::make_shared;

/** \class EnemyFactory
 *  \brief This class is used to creates all the enemy objects of the game.
 *  It periodically creates Spider objects after a specified delay. It generates
 *  the initial Centipede train that is used in the beginning of the game. It can
 *  also generate a specified number CentipedeSegment of BodyType::HEAD periodically.
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
         *  \param number_of_heads is an int containing the number of heads to be generated.
         *  \return vector<shared_ptr<CentipedeSegment>>
         */
        vector <shared_ptr<CentipedeSegment>> generateCentipedeHeads(const int number_of_heads);

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

        /** \brief Returns the current delay of the timer.
         *  \return double
         */
        double getSpiderReleaseTime() const;

        /** \brief Sets the Spider release time delay.
         *  \param new_delay is a double containing the new delay for the Spider generation.
         */
        void setSpiderReleaseTime(double new_delay);

        /** \brief Returns the current delay of the timer.
         *  \return double
         */
        double getCentipedeHeadsReleaseTime() const;

        /** \brief Sets the Centipede heads release time delay.
         *  \param new_delay is a double containing the new delay for the Centipede
         *  heads generation.
         */
        void setCentipedeHeadsReleaseTime(double new_delay);

    private:
        const Grid grid_;
        bool isCentipedeGenerated_;
        bool isCentipedeHeadsGenerated_;
        bool isScorpionGenerated_;

        StopWatch SpiderTimer_;
        double timeSinceLastSpider_;
        double spiderReleaseTime_;

        StopWatch CentiHeadsTimer_;
        double timeSinceLastcentiHeads_;
        double centiHeadsReleaseTime_;
};

#endif // ENEMYFACTORY_H
