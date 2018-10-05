#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <SFML/Graphics.hpp>

/** \class SplashScreen
 *  \brief  A presentation class that uses the SFML library to display playing
 *  instructions and the game's title.
 *  \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
 *  \version 3.0
 */
class SplashScreen
{
    public:
        /** \brief Default constructor that creates a SplashScreen object.
         */
        SplashScreen();

        /** \brief Displays the SplashScreen window.
         *  \param render_window is of type sf::RenderWindow.
         */
        void show(sf::RenderWindow& render_window);

        /** \brief Default destructor that destroys a SplashScreen object.
         */
        ~SplashScreen();

    private:
        sf::Texture splashScreenTexture_;
        sf::Font splashScreenFont_;
};

#endif // SPLASHSCREEN_H
