#ifndef LOGIC_H
#define LOGIC_H

#include "Grid.h"
#include "Presentation.h"
#include "ScreenState.h"
#include "StopWatch.h"
#include "GameEngine.h"

#include <memory>
#include <ctime>

using std::vector;
using std::shared_ptr;

/** \class Logic
 *  \brief This class performs the logic that defines how the game objects behave.
 *  \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
 *  \version 3.0
 */

class Logic
{
    public:
        /** \brief Default Logic constructor. An instance of the game is created
         *  and the game objects are initialized.
         */
        Logic();

        /** \brief Runs the game loop.
         */
        void run();

        /** \brief Default Destructor. Destroys an instance of the game.
         */
        ~Logic();

    private:
        const Grid grid_{592, 640};
        Presentation presentation_{grid_.getWidth(), grid_.getHeight()};
        GameEngine gameEngine_{grid_};
        AssetManager assetManager_;
        StopWatch game_timer_;
        ScreenState screen_state_;

        // Private functions:
        /** \brief Displays the splash screen at the start of the game.
         */
         void startUp();

        /** \brief Displays the splash screen at the start of the game.
         */
        void renderSplashScreen();

        /** \brief Tells presentation to process input from keyboard.
         */
        void getInputCommands();

        /** \brief Loads paths to the textures used by the game.
         */
        void loadAssets();

        /** \brief Gives Presentation a vector of game objects to be drawn.
         */
        void renderGameObjects();

        /** \brief Displays the game over screen when the player has lost the game.
         */
        void renderGameOverScreen();

        /** \brief Displays the game won screen when the player has won the game.
         */
        void renderGameWonScreen();

        /** \brief Runs the logic for the game.
         */
        void updateGame();

        /** \brief Plays sound for spider and scorpion as they move.
         */
        void updateMovingObjectsSound();

        /** \brief Checks whether the player's score has passed the current high
         * score and updates the high score if true.
         */
        void updateScores();

        /** \brief Removes all Centipede segments from vector(s) where they exist,
         *  reset the position of the player and generate a new Centipede train.
         */
        void reincarnatePlayer();

        /** \brief Resets reincarnate of the Mushroom objects in the game.
         */
        void reincarnateMushrooms();

        /** \brief Plays the levelUp sound if the player's level has advanced.
         */
        void levelUp();
};

#endif // LOGIC_H
