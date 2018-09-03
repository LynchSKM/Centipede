#include "SeparatingAxisTheorem.h"

bool SeparatingAxisTheorem::checkOverlap(const Rectangle& rect_A, const Rectangle& rect_B)
{

    if(!axes_.empty()) clearAll();

    storeVertices(rect_A, vertices_rectA_);
    storeVertices(rect_B, vertices_rectB_);
    generateAxes();

    return checkProjectionsOverlap();
}

void SeparatingAxisTheorem::storeVertices(const Rectangle& rect, vector<Position>& vertices)
{
    vertices.push_back(rect.upperLeft);
    vertices.push_back(rect.upperRight);
    vertices.push_back(rect.bottomLeft);
    vertices.push_back(rect.bottomRight);

}

void SeparatingAxisTheorem::generateAxes(){
    //Rect A
    // UpperRight-UpperLeft
    axes_.push_back(vertices_rectA_.at(1)-vertices_rectA_.at(0));
    // UpperRight-BottomRight
    axes_.push_back(vertices_rectA_.at(1)-vertices_rectA_.at(3));

    //Rect B
    // UpperLeft-BottomLeft
    axes_.push_back(vertices_rectA_.at(0)-vertices_rectA_.at(2));
    // UpperLeft-UpperRight
    axes_.push_back(vertices_rectA_.at(0)-vertices_rectA_.at(1));

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
    float axis_magnitude = (std::pow(axis_x,2))+(std::pow(axis_y,2));

    for(const auto& vertex: vertices){
        float product = dotProduct(vertex, axis)/axis_magnitude;
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
        if (overlapOccured==false)
            return false;
    }//for axes

    return true;
}

void SeparatingAxisTheorem::clearAll()
{
    axes_.clear();
    vertices_rectA_.clear();
    vertices_rectB_.clear();
}
