#ifndef SEPARATINGAXISTHEOREM_H
#define SEPARATINGAXISTHEOREM_H

#include "POSITION.H"
#include "BoundaryBox.h"

#include <cmath>
#include <limits>
#include <algorithm>
#include <tuple>
#include <vector>

using std::tuple;
using std::vector;
using std::numeric_limits;
using std::min;
using std::max;

/** \class SeparatingAxisTheorem
 *  \brief This is a class used to determine overlap between BoundaryBox objects.
 *  This class makes use of the Separating Axis Theorem algorithm that checks for
 *  overlap between rectangles. Checks for overlap along all edges of the two
 *  BoundaryBox objects being checked.
 *  \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
 *  \version 3.0
 */

class SeparatingAxisTheorem
{
     public:
        /** \brief Takes in two BoundaryBox objects and checks whether they overlap.
         *  \param rect_A is of type BoundaryBox taken in by reference.
         *  \param rect_B is of type BoundaryBox taken in by reference.
         *  \return bool which is true if there's overlap and false otherwise.
         */
        bool checkOverlap(const BoundaryBox& rect_A, const BoundaryBox& rect_B);

        /** \brief Returns the minimum distances x and y to remove objects out of
         *  collision.
         * 	\param centre_1 is of type Position and is the centre of a BoundaryBox Shape.
         * 	\param centre_2 is of type Position and is the centre of a BoundaryBox Shape.
         * 	\return Position
         */
        Position getPenetrationDistance(Position& centre_1, Position& centre_2);

    private:
        vector<Position> axes_;
        vector<Position> vertices_rectA_;
        vector<Position> vertices_rectB_;
        float smallest_overlap_ = numeric_limits<float>::max();
        Position min_translation_vector_;

        /** \brief Generates the normals perpendicular to the edges of a Rectangle.
         *  The normals are stored in a vector of type Position. 
		 *	These normals are used as an axes for vector projection later on.
         */
        void generateAxes();

        /** \brief Performs the dot product between two points.
         *  \param pointA is of type Position.
         *  \param pointB is of type Position.
         *  \return float which is the scalar result of the dot product.
         */
        float dotProduct(const Position& pointA, const Position& pointB);

       /**  \brief Performs the normalization of an axis normal vector.
	    *	The unit vector is what gets returned.
        *   \param axis is of type Position.
        *   \return Position which is the normalized axis vector (unit vector).
        */
        Position normalizeAxis(const Position& axis);

        /** \brief Performs vector projection onto axes generated.
         *  \details The vertices of a Rectangle are projected onto an axis to
         *  determine where on the axis it is located. It returns the min and max
         *  projections of the Rectangle on the axis given.
         *  \param axis is of type Position.
         *  \param vertices is a vector of type Position.
         *  \return tuple<float,float> first float is the min projection of the Rectangle.
         *  Second float is the max projection of the Rectangle.
         */
        tuple<float, float> projectVectorsOntoAxis(const Position& axis,
                                                   vector<Position>& vertices);

        /** \brief Iterates through the axes generated and checks for overlap on each. 
		 *	Each BoundaryBox's vertices are projected onto an axis by
         *  using projectVectorsOntoAxis.
         *  If overlap occurs on each axis then true is returned, otherwise false.
         *  \return bool
         */
        bool checkProjectionsOverlap();

        /** \brief Clears all the vectors used as private members.
         */
        void clearAll();
};

#endif // SEPARATINGAXISTHEOREM_H
