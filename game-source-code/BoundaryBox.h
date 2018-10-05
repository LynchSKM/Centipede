#ifndef BOUNDARYBOX_H
#define BOUNDARYBOX_H

#include "POSITION.H"

#include <cmath>
#include <tuple>
#include <vector>

using std::tuple;
using std::vector;
using std::begin;
using std::end;
const auto pi = std::atan(1)*4;

/** \class BoundaryBox
 *  \brief This class constructs a rectangle shape with the given the width, height,
 *	center and rotation angle if any. The construction requires the centre point
 *  of the rectangle shape to be given. The vertices of the boundary box are then
 *  calculated using the centre point and the rotation angle. These vertices are
 *  stored in a vector of type Position in the order upper left, upper right,
 *  bottom left, and bottom right.
 *	\author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
 *	\version 3.0
 */

class BoundaryBox
{
    public:
        /** \brief Parameterized Constructor. Creates a BoundaryBox object.
         * 	\param centre is of type Position and holds the centre position of the box.
         * 	\param width is of type float and holds the full width of the box.
         * 	\param height is of type float and holds the full height of the box.
         * 	\param rotationAngle is of type float and holds the rotated angle of the box, if any).
         */
        BoundaryBox(Position centre, float width, float height, float rotationAngle);

        /** \brief A function that returns the vertices of the boundary box in
         *  a vector of type Position. The order of the vertices is upper left,
         *  upper right, bottom left, and bottom right.
         *  \return vector<Position> containing the vertices of the boundary box.
         */
        vector <Position> getVertices() const;

        /** \brief Default Destructor. Destroys a Boundary box.
         */
        ~BoundaryBox();
    private:
        vector<Position> vertices_;
        float height_;
        float width_;
        float rotationAngle_;
        Position centre_;

        /** \brief Calculates the vertex of the boundary box.
         *  Given a radius from the centre point and the angle relative to
         * 	the centre point, a vertex can be calculated. These values are obtained by
         * 	constructing the rectangle shape at a rotation of zero degrees.
         *  \param radius is a float and contains the radius (half diagonal length) from centre.
         *  \param angle is a float and contains the angle a vertex is from the centre's axis.
         *  \return Position which is a vertex.
         */
        Position calculateVertex(float radius, float angle);

        /** \brief Takes in two sides of a right angled triangle and performs
         *  trig math to get a hypotenuse and angle between hypotenuse and adjacent.
         *  \param opposite is a float and contains the length of the opposite side.
         *  \param adjacent is a float and contains the length of the adjacent side.
         *  \return tuple<float, float> containing the angle and the hypotenuse.
         */
        tuple<float, float> pointModArg(float opposite, float adjacent);

        /** \brief Iterates through the vertices of a rotated boundary box.
         *  The order of the vertices being saved is necessary for other
         *  classes that require it. This function pushes the generated vertices
         *  into a vector in the vertex order: Upper Left, Upper Right, Bottom Left
         *  and Bottom Right.
         */
        void sortPoints();

        /** \brief Builds a boundary box around a centre point with the parameters
         *  taken in by the constructor. Creates vertices using the calculateVertex
		 *	function. The created vertices are then saved into the private member
		 *	vector vertices_ in the order specified. Gets called in the constructor to
		 *	immediately create the boundary box once all the parameters needed are saved.
         */
        void constructBoundaryBox();
};

#endif // BOUNDARYBOX_H
