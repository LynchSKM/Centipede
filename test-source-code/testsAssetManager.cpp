#include "AssetManager.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>


TEST_CASE("Asset path and entity type set can be retrieved")
{

    AssetManager::AssetType assetType = AssetManager::AssetType::PLAYER;
    string assetPath = "Assets/PlayerAlt.png";
    AssetManager assetManager{assetType, assetPath };

    CHECK(assetManager.getAssetType() == assetType);
    CHECK(assetManager.getAssetPath() == assetPath);
}
