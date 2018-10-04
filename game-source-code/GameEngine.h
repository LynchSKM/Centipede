#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "HighScoreManager.h"
#include "CollisionHandler.h"
#include "MushroomFactory.h"
#include "EnemyFactory.h"

#include "Player.h"
#include "CentipedeSegment.h"
#include "Scorpion.h"
#include "Spider.h"
#include "StopWatch.h"

#include <vector>
#include <memory>
#include <algorithm>
#include <ctime>
#include <tuple>

using std::tuple;
using std::vector;
using std::shared_ptr;
using std::make_shared;

/** \class GameEngine
 *  \brief Creates all the enemy objects of the game and Mushrooms.
 *  \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
 *  \version 3.0
 */
class GameEngine
{
    public:

        /** \brief Parameterized constructor. Creates an GameEngine object.
         *  \param grid of type Grid.
         */
        GameEngine(const Grid& grid);

        /** \brief Destroys a GameEngine object.
         */
        ~GameEngine();

        /** \brief Gets the input from keyboard.
         *  \param keyboard_inputs is a tuple<bool, bool, bool, bool, bool>
         *  containing the key pressed bool for left, right, up, down, and space
         *  keys events.
         */
        void getInputCommands(tuple<bool, bool, bool, bool, bool> keyboard_inputs);

        /** \brief Returns true or false depending on whether the Player shot a
         *  bullet.
         */
        bool isPlayerBulletFired() const;

        /** \brief Performs the level up logic. Which is just a delay used while
         *  the level up sound is played.
         */
        void levelUp();

        /** \brief Generates mushrooms at random positions.
         */
        void generateMushrooms();

        /** \brief Generates all the game moving enemy objects.
         */
        void generateGameEnemies();

        /** \brief Calls the respective functions to create the game logic.
         */
        void runGameLogic();

        /** \brief Sets number of lives to max of Mushroom's that are not dead yet.
         */
        bool isMushroomReincarnationComplete();

        /** \brief Queries if all the game stages have been completed.
         *  \return bool
         */
         bool allStagesComplete();

        /** \brief Returns a bool indicating whether the level has changed.
         *  \return bool
         */
         bool playerHasLevelledUp();

        /** \brief Reset the position of the player and generate a new Centipede train.
         */
        bool reincarnatePlayer();

        /** \brief Resets states of generated objects to false.
         */
        void reset();

        /** \brief A function that returns the parameters needed for rendering.
         *  The parameters are the vector containing all the game objects, the
         *  player's remaining lives, the player's score, the game high score
         *  the current game level and the max game level.
         *  \return tuple<vector<IEntity_ptr>&, int, int, tuple<int,int>>
         */
         tuple<const vector<IEntity_ptr>&, int, tuple<int, int>, tuple<int,int>> getRenderingParameters();

        /** \brief Returns the moving entities in the game.
         *  \return const vector<IMovingEntity_ptr>&
         */
         const vector<IMovingEntity_ptr>& getMovingEntities();

        /** \brief A function that returns the player's score and the high score.
         *  \return tuple<int, int>
         */
         tuple<int, int> getGameScores();

        /** \brief Returns the current game level and the max game level.
         *  \return tuple<int,int>
         */
         tuple<int,int> getGameLevel() const;

        /** \brief Returns details about the player's alive status, whether the
         *  high score was passed, and whether all the levels have been completed.
         *  \return tuple<bool, bool, bool>
         */
         tuple<bool, bool, bool> getGameStatus();

    private:
        const Grid grid_;
        shared_ptr<Player> player_;
        vector<IEntity_ptr> game_objects_;
        vector<IMovingEntity_ptr> moving_game_objects_;
        CollisionHandler collisionHandler_;
        MushroomFactory mushroomfactory_;
        EnemyFactory enemyFactory_;
        HighScoreManager highScoreManager_;

        bool resetLevel_                 = true;
        bool hasLevelledUp_              = true;
        bool AllGameStageComplete_       = false;
        bool debounceSpaceKey_           = false;
        bool bulletFired_                = false;

        int gameLevel_      = 1;
        const int maxLevel_ = 5;
        int high_score_     = 0;

        StopWatch mushroom_reincarnate_timer;
        double timeSinceLastMushroomRegen;

        /** \brief Generates a Centipede made up of centipede segments.
         */
        void generateNormalCentipede();

        /** \brief Generates centipede heads.
         *  \param numberOfHeads an int.
         */
        void generateCentipedeHeads(int numberOfHeads);

        /** \brief Generates a mushrooms at a given position.
         */
        void generateAMushroom();

        /** \brief Generates a scorpion at a random position.
         */
        void generateAScorpion();

        /** \brief Generates a spider periodically.
         */
        void generateASpider();

        /** \brief Moves all the game objects that can be moved.
         */
        void moveGameObjects();

        /** \brief Removes all moving entities from vector(s) where they exist,
         *  excluding the player.
         */
        void removeMovingEntities();

        /** \brief Removes all dead entities from vector(s) where they exist.
         */
        void removeDeadEntities();

        /** \brief Check for collisions between game entities.
         */
        void checkCollisions();

        /** \brief Updates the game's high score.
         */
        void updateScores();
};

/**\brief  container_erase_if - a function that erases elements in a container based on a
 * specified condition determined by the Predicate.
 *
 * \param container a std container passed by reference to be iterated through.
 * \param predicate can be a function that returns true or false.
 */
template<typename TypeContainer, typename PredicateT>
inline void container_erase_if(TypeContainer& container, const PredicateT& predicate)
{
    container.erase(remove_if(begin(container),
                              end(container), predicate),
                    end(container));
}//
#endif // GAMEENGINE_H
