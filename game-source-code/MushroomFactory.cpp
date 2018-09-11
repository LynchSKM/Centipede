#include "MushroomFactory.h"

MushroomFactory::MushroomFactory(Grid grid):grid_{grid},maxCol_{37}, maxRow_{32},
                maxMushrooms_{300}
{
    //ctor
}
vector <shared_ptr<Mushroom>>MushroomFactory::generateMushrooms()
{
    vector<shared_ptr<Mushroom>> mushrooms;
    auto row = 0, col = 0;

    for(auto i = 0; i<maxMushrooms_;i++){
        row = rand()%maxRow_;
        col = rand()%maxCol_;

        it_ = gridPoints.find(Position(row,col));
        if (it_ != gridPoints.end())it_->second = true;
        else{
            auto mushroom_ptr = make_shared<Mushroom>(gridPointLink(Position(row,col)));
            mushrooms.push_back(mushroom_ptr);
        }
    }
    return mushrooms;
}

shared_ptr<Mushroom> MushroomFactory::generateAMushroom(Position position)
{
    auto mush_position = gridRowCol(position);
    auto mushroom_ptr = make_shared<Mushroom>(gridPointLink(mush_position));
    return mushroom_ptr;
}

void MushroomFactory::defineRowAndCol()
{
    auto x = 0.0f, y = 0.0f;
    for(auto i = 0; i < maxRow_; i++)
        for(auto j = 0; j < maxCol_; j++){
            x = (16*i)+8;
            y = (16*j)+24;

            auto temp_pair = pair<Position , bool>(Position{x,y}, false);
            gridPoints.insert(temp_pair);
        }
}

Position MushroomFactory::gridRowCol(Position position)
{
    auto x = round(((position.getX_pos())-8.0)/16.0);
    auto y = round(((position.getY_pos())-24.0)/16.0);
    return Position(x,y);
}

Position MushroomFactory::gridPointLink(Position position)
{
    auto x = round(position.getX_pos()*16 +8.0);
    auto y = round(position.getY_pos()*16 +24.0);
    return Position(x,y);
}

MushroomFactory::~MushroomFactory()
{
    //dtor
}
