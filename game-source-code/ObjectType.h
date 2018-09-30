#ifndef OBJECTTYPE_H
#define OBJECTTYPE_H

/** \enum ObjectType
 *  \brief A strongly typed enum class representing the type of game objects.
 *  \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
 *  \version 3.0
 */

enum class ObjectType
{
    PLAYER,               /**< Represents a Player object.*/
    PLAYER_LASER_BULLET,  /**< Represents a PlayerBullet object.*/
    CENTIPEDE,            /**< Represents a CentipedeSegment object.*/
    MUSHROOM,             /**< Represents a Mushroom object.*/
    SCORPION,             /**< Represents a Scorpion object.*/
    SPIDER                /**< Represents a Spider object.*/
};

#endif // OBJECTTYPE_H
