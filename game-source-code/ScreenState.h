#ifndef SCREENSTATE_H
#define SCREENSTATE_H

/** \enum ScreenState
*   \brief is a strongly typed enum class representing the different game
*   screens that can be displayed.
*   \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
*   Version
*/

enum class ScreenState{
    SPLASHSCREEN  = 0, /**< is coded as int of value 0.*/
    GAMEWONSCREEN      /**< is coded as int of value 1.*/
    GAMEOVERSCREEN     /**< is coded as int of value 2.*/
    GAME_ACTIVE        /**< is coded as int of value 3.*/
};

#endif // SCREENSTATE_H

