#include "AssetManager.h"

AssetManager::AssetManager(){
}//Default constructor

AssetManager::AssetManager(AssetType asset_type, string asset_path)
: assetType_{asset_type}, assetPath_{asset_path}
{
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
