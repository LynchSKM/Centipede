#ifndef SCREENSTATE_H
#define SCREENSTATE_H

/** \enum ScreenState
 *  \brief is a strongly typed enum class representing the different game
 *  screens that can be displayed.
 *  \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
 *  \version 3.0
 */

enum class ScreenState
{
    SPLASHSCREEN  = 0, /**< Represents the SplashScreen.*/
    GAMEWONSCREEN,     /**< Represents the GameWonScreen.*/
    GAMEOVERSCREEN,    /**< Represents the GameOverScreen.*/
    GAME_ACTIVE        /**< Represents the Game Active Screen.*/
};

#endif // SCREENSTATE_H

