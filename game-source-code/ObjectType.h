#ifndef OBJECTTYPE_H
#define OBJECTTYPE_H

/** \enum ObjectType
*   \brief is a strongly typed enum class representing the type of game objects.
*   \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
*
*/

enum class ObjectType
{
    PLAYER = 0, /**< is coded as int of value 0.*/
    PLAYER_LASER_BULLET, /**< is coded as int of value 1.*/
    CENTIPEDE,  /**< is coded as int of value 2.*/
    MUSHROOM    /**< is coded as int of value 3.*/
};

#endif // OBJECTTYPE_H
