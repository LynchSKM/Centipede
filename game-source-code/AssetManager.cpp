#include "AssetManager.h"

map<AssetManager::AssetType, vector<unsigned int>> AssetManager::texture_details_;
map<AssetManager::AssetType, Direction> AssetManager::texture_direction_;

AssetManager::AssetManager()
{

}//Default constructor

AssetManager::AssetManager(AssetType asset_type, string asset_path)
: assetType_{asset_type}, assetPath_{asset_path}
{

}

tuple<vector<unsigned int>, Direction> AssetManager::getTextureDetails() const
{
    vector<unsigned int> details;
    auto direction = Direction::NONE;
    auto iter_found = texture_details_.find(assetType_);
    if(iter_found != texture_details_.end())
    {
        auto iter_direc = texture_direction_.find(assetType_);
        details   = iter_found->second;
        direction = iter_direc->second;
    }

    return {details, direction};
}
void AssetManager::captureDetails(AssetType type_asset, int rows_in_image,
                                  int columns_in_image, Direction direction)
{
    vector<unsigned int> temp_details;
    temp_details.push_back(rows_in_image);
    temp_details.push_back(columns_in_image);

    auto temp_pair = pair<AssetType, vector<unsigned int>>(type_asset, temp_details);
    auto temp_pair_direc = pair<AssetType, Direction>(type_asset, direction);

    texture_details_.insert(temp_pair);
    texture_direction_.insert(temp_pair_direc);
}

void AssetManager::loadTextureDetails()
{
    auto rows_in_image = 1;
    auto columns_in_image = 1;
    auto direction = Direction::NONE;
    auto temp_index = static_cast<int>(AssetType::PLAYER);

    for(auto i = temp_index; i<temp_index+2; i++)
    {
        captureDetails(static_cast<AssetType>(i), rows_in_image, columns_in_image,
                       direction);
    }

    rows_in_image++;
    columns_in_image = 8;
    temp_index = static_cast<int>(AssetType::CENTIPEDE);
    direction = Direction::LEFT;
    for(auto i = temp_index; i<temp_index+2; i++)
    {
        captureDetails(static_cast<AssetType>(i), rows_in_image, columns_in_image,
                       direction);
        columns_in_image/=2.0f;
        direction = Direction::NONE;
    }

    rows_in_image--;
    columns_in_image = 4;
    temp_index = static_cast<int>(AssetType::SCORPION);
    direction = Direction::LEFT;
    for(auto i = temp_index; i<temp_index+2; i++)
    {
        captureDetails(static_cast<AssetType>(i), rows_in_image, columns_in_image,
                       direction);
        columns_in_image*=2.0f;
        rows_in_image++;
        direction = Direction::NONE;
    }
}

AssetManager::AssetType AssetManager::getAssetType() const{
	return assetType_;
}

string AssetManager::getAssetPath() const{
	return assetPath_;
}

vector<AssetManager> AssetManager::getAssetInfo(){
	vector<string> file_paths = {"Assets/Font.ttf",
                                "Assets/shoot.wav",
                                "Assets/mushroom_regenerate.wav",
                                "Assets/scorpion_move.wav",
                                "Assets/spider_move.wav",
								"Assets/PlayerAlt.png",
								"Assets/bullet.png",
								"Assets/Centipede.png",
								"Assets/Mushroom.png",
								"Assets/Scorpion.png",
								"Assets/spider_and_score.png"
								};

	vector<AssetManager> assets;
    for(auto i = 0u; i != file_paths.size(); i++)
    {
        AssetManager asset_temp{static_cast<AssetType>(i), file_paths.at(i)};
        assets.push_back(asset_temp);
    }

    return assets;
}
