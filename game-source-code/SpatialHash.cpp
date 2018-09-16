#include "SpatialHash.h"
#include <cmath>
#include <iostream>

SpatialHash::SpatialHash(const Grid& grid):grid_{grid}, cell_size_{80}
{
    //ctor
    buildMapKeys();
}

void SpatialHash::buildMapKeys()
{
    auto maxRow = static_cast<float>(std::floor(grid_.getHeight()/cell_size_));
    auto maxCol = static_cast<float>(std::floor(grid_.getWidth() /cell_size_));
    if((grid_.getHeight()/cell_size_)%cell_size_!=0)
        ++maxRow;
    if((grid_.getWidth()/cell_size_)%cell_size_!=0)
        ++maxCol;

    auto hash_id = 0;
    for(auto cell_id_row = 0; cell_id_row < maxRow; cell_id_row++){
        for(auto cell_id_col = 0; cell_id_col < maxCol; cell_id_col++){
            auto temp_pair = pair<int, vector<IEntity_ptr>>(hash_id, vector<IEntity_ptr>());
            game_object_table_.insert(temp_pair);
            ++hash_id;
        }
    }
}

void SpatialHash::generateSpatialHashTable(vector<IEntity_ptr>& game_objects)
{
    clearAll();
    for(auto& object : game_objects){
        // Save in map:
        saveLocations(object);
    }//for
    return;
}

vector<IEntity_ptr> SpatialHash::retrieveNearbyObjects(IEntity_ptr& object)
{
    vector<unsigned int> uniqueCells(5);
    vector<IEntity_ptr> nearbyObjects;
    auto game_object_locations = getObjectLocations(object);
    auto object_cell_locations = generateMapKeys(game_object_locations);

    // Remove duplicates:
    sort(object_cell_locations.begin(), object_cell_locations.end());

    auto iter_cell_locations = unique_copy(object_cell_locations.begin(),
                                           object_cell_locations.end(),
                                           uniqueCells.begin());
    // Resize vector:
    uniqueCells.resize(std::distance(uniqueCells.begin(), iter_cell_locations));

    // Search cells where object can be found:
    for(auto& cell : uniqueCells){
        auto iter_map = game_object_table_.find(cell);
        if(iter_map != game_object_table_.end()){
           for(auto& object_in_proximity : iter_map->second){
                if(object!=object_in_proximity)
                    nearbyObjects.push_back(object_in_proximity);
           }//for
        }//if
    }//for
    return nearbyObjects;
}

vector<Position> SpatialHash::getObjectLocations(IEntity_ptr& object)
{
    vector<Position> object_locations(5);
    auto iter_vec = object_locations.begin();
    (*iter_vec) = object->getPosition();

    for(auto& vertex : object->getBoundaryBox().getVertices()){
        ++iter_vec;
        (*iter_vec) = vertex;
    }//for
    return object_locations;
}

unsigned int SpatialHash::generateMapKey(const Position& position)
{   //uses column wise cell id iteration:
    auto x = static_cast<float>(std::floor(position.getX_pos()/cell_size_));
    auto y = static_cast<float>(std::floor(position.getY_pos()/cell_size_));
    int cell_id = ((x*(grid_.getHeight()/cell_size_)+y));
    return cell_id;
}

vector<unsigned int> SpatialHash::generateMapKeys(vector<Position>& positions)
{
    vector<unsigned int> object_cell_locations(5);
    auto iter_cell_loc = object_cell_locations.begin();

    for(auto& position : positions){
        (*iter_cell_loc) = generateMapKey(position);
        ++iter_cell_loc;
    }//for
    return object_cell_locations;
}

void SpatialHash::saveLocations(IEntity_ptr object)
{
    auto game_object_locations = getObjectLocations(object);
    auto object_cell_locations = generateMapKeys(game_object_locations);

    for(auto& cell : object_cell_locations){
        auto iter_map = game_object_table_.find(cell);
        if(iter_map!=game_object_table_.end()){
            auto iter_vec = find(begin(iter_map->second), end(iter_map->second), object);

            if(iter_vec == (iter_map->second).end())
                (iter_map->second).push_back(object);
        }//if
    }//for
    return;
}

void SpatialHash::clearAll()
{
    auto iter_map = game_object_table_.begin();
    auto iter_end = game_object_table_.end();
    for( ; iter_map!=iter_end; iter_map++){
       (iter_map->second).clear();
    }//for
    return;
}

SpatialHash::~SpatialHash()
{
    //dtor
}
