#ifndef GAMEWONSCREEN_H
#define GAMEWONSCREEN_H

#include <SFML/Graphics.hpp>
#include <string>

/**	\class GameWonScreen
 * 	\brief  A presentation layer class that uses the SFML library to display the player's
 * 	victory and a summary of the game scores.
 * 	\author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
 * 	\version 3.0
 */
class GameWonScreen
{
    public:
        /** \brief Default constructor that creates a GameWonScreen object.
         */
        GameWonScreen();

        /** \brief Displays the SplashScreen window.
         *  \param render_window is of type sf::RenderWindow.
         *  \param player_score is of type int. Holds the player's score.
         *  \param high_score is of type int. Holds the highest score achieved in the game.
         */
        void show(sf::RenderWindow& render_window, const int& player_score, const int& high_score);

        /** \brief Default destructor that deletes a GameWonScreen object.
         */
        ~GameWonScreen();

    private:
        sf::Texture gameWonTexture_;
        sf::Font font_;
};

#endif // GAMEWONSCREEN_H
