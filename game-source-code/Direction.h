#ifndef DIRECTION_H
#define DIRECTION_H

/** \enum Direction
 *  \brief A strongly typed enum class representing the directions game
 *  objects could be facing. Used in the game to indicate which direction
 *  game objects are facing.
 *  \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
 *  \version 3.0
 */

enum class Direction
{
    UP = 0, /**< Indicates the direction as up.*/
    DOWN,   /**< Indicates the direction as down.*/
    LEFT,   /**< Indicates the direction as left.*/
    RIGHT,  /**< Indicates the direction as right.*/
	NONE	/**< Indicates no direction.*/
};

#endif // DIRECTION_H
