#include "MushroomFactory.h"

MushroomFactory::MushroomFactory(Grid& grid):grid_{grid},maxCol_{31}, maxRow_{37},
                maxMushrooms_{200}
{
    //ctor
    // Build map:
    defineRowAndCol();
}
vector <shared_ptr<Mushroom>>MushroomFactory::generateMushrooms()
{
    vector<shared_ptr<Mushroom>> mushrooms;
    auto x = 0, y = 0;
    auto numMushrooms_ = rand()%maxMushrooms_ +50;
    for(auto i = 0; i<numMushrooms_;i++){
        x = rand()%maxRow_;
        y = rand()%maxCol_;
        if(!isCellOccupied(x,y)){
            auto mushroom_ptr = make_shared<Mushroom>(gridPointLink(Position(x,y)));
            mushrooms.push_back(mushroom_ptr);
        }//if
    }//for
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
    for(auto i = 0; i < maxRow_; i++)
        for(auto j = 0; j < maxCol_; j++){
            auto cellID = (maxRow_*(i+1) + (j+1));
            auto tempId = pair<int,bool>(cellID,false);
            cell_ID_List_.insert(tempId);
        }//for
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
bool MushroomFactory::isCellOccupied(int x, int y)
{
    auto cellID = (maxRow_*(x+1) + (y+1));
    auto cell_itr = cell_ID_List_.find(cellID);
    if(cell_itr != cell_ID_List_.end()){
        if(cell_itr->second) return cell_itr->second;
        else cell_itr->second = true;
    }//if
    return false;
}

MushroomFactory::~MushroomFactory()
{
    //dtor
}
