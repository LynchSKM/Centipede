#ifndef DIRECTION_H
#define DIRECTION_H

/** \enum Direction
 *  \brief A strongly typed enum class representing the directions game
 *  objects could be facing.
 *  \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
 *  \version 3.0
 */

enum class Direction
{
    UP = 0, /**< is coded as int of value 0.*/
    DOWN,   /**< is coded as int of value 1.*/
    LEFT,   /**< is coded as int of value 2.*/
    RIGHT,  /**< is coded as int of value 3.*/
	NONE	/**< is coded as int of value 4.*/
};

#endif // DIRECTION_H
