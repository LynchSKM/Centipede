#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H

#include <SFML/Graphics.hpp>

/**	\class GameOverScreen
 *  \brief A presentation layer class that uses the SFML library to display that
 *  the game is over and a summary of the game scores.
 *  \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
 *	\version 3.0
 */

class GameOverScreen
{
    public:
        /** \brief Default constructor that creates a GameOverScreen object.
         */
        GameOverScreen();

        /** \brief Displays the Game Over window.
         *  \param render_window is of type sf::RenderWindow.
         *  \param player_score is of type int. Holds the player's score.
         *  \param high_score is of type int. Holds the highest score achieved in the game.
         */
        void show(sf::RenderWindow& render_window, const int& player_score, const int& high_score);

        /** \brief Default destructor that deletes a GameOverScreen object.
         */
        ~GameOverScreen();

    private:
        sf::Texture gameOverTexture_;
        sf::Font font_;
};

#endif // GAMEOVERSCREEN_H
