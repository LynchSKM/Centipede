#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "POSITION.H"

/** \struct Rectangle
*   \brief is a struct that contains positions of all four corners of a rectangle
*   shape.
*   \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
*
*/

struct Rectangle{
    Position upperLeft;
    Position upperRight;
    Position bottomLeft;
    Position bottomRight;
};

#endif // RECTANGLE_H
