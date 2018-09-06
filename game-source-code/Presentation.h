#ifndef PRESENTATION_H
#define PRESENTATION_H

#include <SFML/Graphics.hpp>

#include <vector>
#include <memory>

using std::vector;
using std::shared_ptr;

#include "IEntity.h"
#include "AssetManager.h"
#include "SplashScreen.h"

/** \class Presentation
 *  \brief Uses the SFML Graphics Library to draw all game objects on the screen.
 *  \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
 */

class Presentation
{
    public:
        /** \brief Parametrized Constructor. Creates a Presentation object.
         *  \param screen_width is the width of the screen.
         *  \param screen_height is the height of the screen.
         */
        Presentation(const unsigned int screen_width, const unsigned int screen_height);

        /** \brief Displays a Splashscreen at the beginning of the game.
         */
        void drawSplashScreen();

        /** \brief Displays a Game Over Screen at the end of the game.
         *  \param player_score is an int and contains the player's score.
         *  \param high_score is an int and contains the game's high score.
         */
        void drawGameOverScreen(const int player_score, const int high_score);

        /** \brief Displays a Game Won Screen at the end of the game.
         *  \param player_score is an int and contains the player's score.
         *  \param high_score is an int and contains the game's high score.
         */
        void drawGameWonScreen(const int player_score, const int high_score);

        /** \brief Displays the player's lives, current score and the high score
         * of the game.
         *  \param remaining_lives is an int representing the player's lives.
         *  \param player_score is an int that has the player's current score.
         *  \param high_score is an int that has the game's highest score.
         */
        void displayLives(const int remaining_lives, const int player_score,
                          const int high_score);

        /** \brief Draws all the game objects onto the screen. Including the player's
         *  score, lives and the game's highest score.
         * \param game_objects is a vector of IEntity containing all the game objects.
         * \param remaining_lives is an int and contains the number of lives.
         * \param player_score is an int that has the player's current score.
         * \param high_score is an int that has the game's highest score.
         */
        void renderWindow(vector<shared_ptr<IEntity>>& game_objects,
                          const int remaining_lives, const int player_score,
                          const int high_score);

        /** \brief Loads all the game's textures.
         *  \param game_assets is a vector of AssetManager
         */
        //void loadTextures(vector<AssetManager> game_assets);

        /** \brief Default Destructor. Destroys a Presentation object.
         */
        ~Presentation();

    private:
        sf::Color background_;
        sf::RenderWindow window_;
        sf::Font font_;
        sf::Sprite gameObjects_;
};

#endif // PRESENTATION_H
