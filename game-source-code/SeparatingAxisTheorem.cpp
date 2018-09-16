#include "SeparatingAxisTheorem.h"

bool SeparatingAxisTheorem::checkOverlap(const BoundaryBox& rect_A, const BoundaryBox& rect_B)
{

    if(!axes_.empty()) clearAll();
    vertices_rectA_ = rect_A.getVertices();
    vertices_rectB_ = rect_B.getVertices();

    generateAxes();

    return checkProjectionsOverlap();
}

Position SeparatingAxisTheorem::normalizeAxis(const Position& axis)
{
    float axis_x = axis.getX_pos(), axis_y = axis.getY_pos();
    float axis_magnitude = std::sqrt((std::pow(axis_x,2))+(std::pow(axis_y,2)));

    return (Position{axis_x/axis_magnitude, axis_y/axis_magnitude});
}


void SeparatingAxisTheorem::generateAxes(){
    //Rect A
    // UpperRight-UpperLeft
    auto axis = vertices_rectA_.at(1)-vertices_rectA_.at(0);
    axes_.push_back(normalizeAxis(axis));

    // UpperRight-BottomRight
    axis = vertices_rectA_.at(1)-vertices_rectA_.at(3);
    axes_.push_back(normalizeAxis(axis));

    //Rect B
    // UpperLeft-BottomLeft
    axis = vertices_rectA_.at(0)-vertices_rectA_.at(2);
    axes_.push_back(normalizeAxis(axis));

    // UpperLeft-UpperRight
    axis = vertices_rectA_.at(0)-vertices_rectA_.at(1);
    axes_.push_back(normalizeAxis(axis));
}

float SeparatingAxisTheorem::dotProduct(const Position& pointA, const Position& pointB)
{
    float dot_product = (pointA.getX_pos() * pointB.getX_pos())+(pointA.getY_pos() * pointB.getY_pos());
    return dot_product;
}

tuple<float, float> SeparatingAxisTheorem::projectVectorsOntoAxis(const Position& axis, vector<Position>& vertices)
{
    vector<Position> projected_vertices(4);
    auto iter_projected_vertex = begin(projected_vertices);

    float axis_x = axis.getX_pos(), axis_y = axis.getY_pos();
    float axis_magnitude_squared = (std::pow(axis_x,2))+(std::pow(axis_y,2));

    for(const auto& vertex: vertices){
        float product = dotProduct(vertex, axis)/axis_magnitude_squared;
        iter_projected_vertex->setX_pos(product*axis.getX_pos());
        iter_projected_vertex->setY_pos(product*axis.getY_pos());
        ++iter_projected_vertex;
    }//for vertex

    float minimumProjection = dotProduct(axis, projected_vertices.at(0));
    float maximumProjection = minimumProjection;

    // Perform dot product between vertices and axis:
    for(auto i=1u; i != projected_vertices.size(); i++){
        float projection = dotProduct(axis, projected_vertices.at(i));

        if (projection < minimumProjection) minimumProjection = projection;
        else if (projection > maximumProjection) maximumProjection = projection;
    }//for vertices

    // Return min and max projections onto axis:
    return {minimumProjection, maximumProjection};
}

bool SeparatingAxisTheorem::checkProjectionsOverlap(){
    // Get minimum and maximum projections onto normals:
    for(const auto& axis : axes_){
        // Project Rectangle A:
        auto[minimumProjectionA, maximumProjectionA] = projectVectorsOntoAxis(axis,
                                                                vertices_rectA_);
        // Project Rectangle B:
        auto[minimumProjectionB, maximumProjectionB] = projectVectorsOntoAxis(axis,
                                                                vertices_rectB_);

        // If both conditions are true there is overlap:
        bool overlapOccured = (minimumProjectionB <= maximumProjectionA && maximumProjectionB >= minimumProjectionA);
        if(overlapOccured==false)
            return false;
        else{
            float overlap = std::max(0.0f, std::min(maximumProjectionA, maximumProjectionB));
            overlap-= std::max(minimumProjectionA, minimumProjectionB);
            if(overlap < smallest_overlap_)
            {
                min_translation_vector_ = axis;
                smallest_overlap_ = overlap;
            }//if
        }//else
    }//for axes

    return true;
}
Position SeparatingAxisTheorem::getPenetrationDistance(Position& centre_1,
                                                       Position& centre_2)
{
  // Default is to ensure mtv points from rectA  to rectB:
  Position b_to_a = centre_2-centre_1;
  if(dotProduct(min_translation_vector_, b_to_a)>=0){
    auto x = -(min_translation_vector_.getX_pos());
    auto y = -(min_translation_vector_.getY_pos());
    min_translation_vector_.setX_pos(x);
    min_translation_vector_.setY_pos(y);
  }
  return(Position(min_translation_vector_.getX_pos()*smallest_overlap_,
                  min_translation_vector_.getY_pos()*smallest_overlap_));
}

void SeparatingAxisTheorem::clearAll()
{
    axes_.clear();
    vertices_rectA_.clear();
    vertices_rectB_.clear();
}
