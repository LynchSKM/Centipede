#include "BoundaryBox.h"

BoundaryBox:: BoundaryBox(Position centre, float width, float height, float rotationAngle):
    centre_(centre), width_{width}, height_{height}, rotationAngle_{rotationAngle}
{
    constructBoundaryBox();
}

vector<Position> BoundaryBox::getVertices() const{
    return vertices_;
}

Position BoundaryBox::calculateVertex(float radius, float angle){
    float x = centre_.getX_pos() + radius*std::cos(angle+(rotationAngle_*pi/180.0f));
    float y = centre_.getY_pos() - radius*std::sin(angle+(rotationAngle_*pi/180.0f));
    return Position{x,y};
}

tuple<float, float> BoundaryBox::pointModArg(float opposite, float adjacent){
    auto angle = std::atan(opposite/adjacent);
    auto radius = opposite/std::sin(angle);
    return {angle, radius};
}

void BoundaryBox::sortPoints(){
    auto temp_vertex = vertices_;
    vertices_.clear();

    auto iter_yMin = begin(temp_vertex);
    auto iter_yMax = begin(temp_vertex);
    auto iter_xMin = begin(temp_vertex);
    auto iter_xMax = begin(temp_vertex);

    for(auto iter_vertex = temp_vertex.begin()+1; iter_vertex!=end(temp_vertex); iter_vertex++){

        auto x = iter_vertex->getX_pos();
        auto y = iter_vertex->getY_pos();

        if(x < iter_xMin->getX_pos()){
            iter_xMin = iter_vertex;
        }
        else if(x > iter_xMax->getX_pos()){
            iter_xMax = iter_vertex;
        }//if

        if(y < iter_yMin->getY_pos()){
            iter_yMin = iter_vertex;
        }
        else if(y > iter_yMax->getY_pos()){
            iter_yMax = iter_vertex;
        }//if
    }//for

     vertices_.push_back(*iter_xMin);
     vertices_.push_back(*iter_yMin);
     vertices_.push_back(*iter_yMax);
     vertices_.push_back(*iter_xMax);
}

void BoundaryBox::constructBoundaryBox(){
    // Upper LEFT point and Lower Left
    auto [angle, radius] = pointModArg(width_/2.0, height_/2.0);
    angle+=pi/2;
    auto temp_Vertex1 = calculateVertex(radius, angle);
    auto temp_Vertex4 = calculateVertex(radius, angle+pi);

    // Upper RIGHT point and Lower Right
    auto [angle_1, radius_1] = pointModArg(height_/2.0, width_/2.0);

    auto temp_Vertex2 = calculateVertex(radius_1, angle_1);
    auto temp_Vertex3 = calculateVertex(radius_1, angle_1+pi);

    /* Order of points in vector
      upperLeft
      upperRight
      bottomLeft
      bottomRight
    */

    if(rotationAngle_==0){
        vector<Position> temp {temp_Vertex1, temp_Vertex2, temp_Vertex3, temp_Vertex4};
        vertices_ = temp;

    }//if
    else if (rotationAngle_==-90 || rotationAngle_ == 270){
        vector<Position> temp {temp_Vertex3, temp_Vertex1, temp_Vertex4, temp_Vertex2};
        vertices_ = temp;

    }//else if
    else if (rotationAngle_ == 90 || rotationAngle_ == -270){
        vector<Position> temp {temp_Vertex2, temp_Vertex4, temp_Vertex1, temp_Vertex3};
        vertices_ = temp;

    }//else if
     else if (rotationAngle_ == -180 || rotationAngle_ == 180){
        vector<Position> temp {temp_Vertex4, temp_Vertex3, temp_Vertex2, temp_Vertex1};
        vertices_ = temp;

    }//else if
    else{
        vector<Position> temp {temp_Vertex1, temp_Vertex2, temp_Vertex3, temp_Vertex4};
        vertices_ = temp;
        sortPoints();
    }//else

}

BoundaryBox::~BoundaryBox()
{
    //dtor
}
