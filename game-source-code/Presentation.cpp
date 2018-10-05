#include "Presentation.h"

Presentation::Presentation(const unsigned int screen_width, const unsigned int screen_height):
window_(sf::VideoMode(screen_width, screen_height), "Centipede LM", sf::Style::Close),
background_(sf::Color::Black),
isLeftPressed_{false},
isRightPressed_{false},
isUpPressed_{false},
isDownPressed_{false},
isSpacePressed_{false},
game_level_colours_{sf::Color::White, sf::Color(125, 50, 80), sf::Color::White,
                    sf::Color(125, 50, 80), sf::Color::Magenta}
{

}

void Presentation::processLevelUpSound()
{
    auto iter_map = game_sounds_.find(GameSounds::LEVEL_UP);
    (iter_map->second)->stop();
    (iter_map->second)->play();
}

void Presentation::processPlayerShootSound()
{
    auto iter_map = game_sounds_.find(GameSounds::GUN_SHOT);
    (iter_map->second)->stop();
    (iter_map->second)->play();
}

void Presentation::processGameObjectSound(ObjectType object_type)
{
    auto temp_object_with_sound_start = static_cast<int>(ObjectType::MUSHROOM);
    auto temp_object = static_cast<int>(object_type);
    auto temp_mushroom_regen_sound =  static_cast<int>(GameSounds::MUSHROOM_REGEN);
    if(temp_object>=temp_object_with_sound_start)
    {
        temp_object-=temp_object_with_sound_start;
        auto temp_sound = static_cast<GameSounds>(temp_object+temp_mushroom_regen_sound);
        auto iter_map = game_sounds_.find(temp_sound);
        if((iter_map->second)->getStatus()!=sf::Music::Playing)
        {
            (iter_map->second)->setVolume(5);
            (iter_map->second)->stop();
            (iter_map->second)->play();
        }
    }
}

void Presentation::checkInput(const sf::Keyboard::Key key, const bool isPressed)
{
    if(key == sf::Keyboard::Left) isLeftPressed_ = isPressed;
    else if(key == sf::Keyboard::Right) isRightPressed_ = isPressed;
    else if(key == sf::Keyboard::Up) isUpPressed_ = isPressed;
    else if(key == sf::Keyboard::Down) isDownPressed_ = isPressed;
    else if(key == sf::Keyboard::Space)isSpacePressed_ = isPressed;
}

void Presentation::processInputEvents()
{
    sf::Event event;
    while(window_.pollEvent(event)){
        switch(event.type){

            case sf::Event::Closed:
                window_.close();
                break;
            case sf::Event::KeyPressed:
                checkInput(event.key.code, true);
                break;

            case sf::Event::KeyReleased:
                checkInput(event.key.code, false);
                break;
            default:
                break;
        }//switch

    }//while
}

void Presentation::generateSpriteSheet(ObjectType object_type, unsigned int row,
                                  sf::Vector2u imageCount, float switchTime,
                                  Direction direction)
{
    // Add to spritesheet for animations:
    auto iter_map = game_textures_.find(object_type);
    SpriteSheet sprite_image{object_type, &(iter_map->second),
                 imageCount, switchTime, row, direction};
    // Save it:
    sprite_sheets_.push_back(sprite_image);

}

void Presentation::populateSpriteSheets(const AssetManager& asset, const ObjectType& object_type)
{
    auto switch_time = 0.3f;
    auto [details, default_direction_in_image] = asset.getTextureDetails();
    if(details.empty()) return;

    auto rows_in_image    = details.at(0);
    auto columns_in_image = details.at(1);
    for(auto row = 0u; row<rows_in_image; row++)
        generateSpriteSheet(object_type, row, sf::Vector2u{columns_in_image,
                            rows_in_image}, switch_time, default_direction_in_image);
    return;
}

void Presentation::loadTextures(const vector<AssetManager>& game_assets)
{
    auto iter_last_sound = std::find_if(game_assets.begin(), game_assets.end(),
                        [](const AssetManager& asset)
                        {
                            return (asset.getAssetType() == AssetManager::AssetType::PLAYER);
                        });

    auto iter_asset = game_assets.begin();
    font_.loadFromFile(iter_asset->getAssetPath());

    // Get sounds:
    auto sound_id = 0;
    for(++iter_asset; iter_asset != iter_last_sound; ++iter_asset)
    {
        auto temp_sound = std::make_shared<sf::Music>();
        temp_sound->openFromFile(iter_asset->getAssetPath());
        temp_sound->setVolume(10);
        auto temp_pair = pair<GameSounds, shared_ptr<sf::Music>>(static_cast<GameSounds>(sound_id++),
                                                     temp_sound);
        game_sounds_.insert(temp_pair);
    }//for

    // Get object textures:
    for( ; iter_asset != game_assets.end(); ++iter_asset)
    {
        sf::Texture texture;
        texture.loadFromFile(iter_asset->getAssetPath());
        if(iter_asset->getAssetType() != AssetManager::AssetType::BULLET
        && iter_asset->getAssetType() != AssetManager::AssetType::SCORPION)
            texture.setSmooth(true);

        auto temp_object_id   = static_cast<int>(iter_asset->getAssetType());
        auto temp_player_id   = static_cast<int>(AssetManager::AssetType::PLAYER);
        auto temp_object_type = static_cast<ObjectType>(temp_object_id-temp_player_id);

        auto temp_pair = pair<ObjectType, sf::Texture>(temp_object_type, texture);
        game_textures_.insert(temp_pair);

        // If object with animated movement, generate spritesheet object.
        populateSpriteSheets(*iter_asset, temp_object_type);
    }//for
}

sf::Sprite Presentation::generateSpriteFromSpriteSheet(const shared_ptr<IEntity>& object){
     // Search for spritesheet:
     sf::Sprite gameObjectsSprite;
     auto entity_type = object->getObjectType();
     auto iter_map = game_textures_.find(entity_type);
     auto half = 2.0f;
     auto rect = sf::IntRect();

     auto iter_vec = find_if(sprite_sheets_.begin(), sprite_sheets_.end(),
                             [&, entity_type](const SpriteSheet& sheet){
                            return (sheet.getObjectType()==entity_type);
                            });

    if(entity_type == ObjectType::CENTIPEDE)
    {
        auto centipede_segment = std::dynamic_pointer_cast<CentipedeSegment>(object);
        if(centipede_segment->getBodyType() == CentipedeSegment::BodyType::BODY)
            ++iter_vec;
        rect = iter_vec->getTextureRect(centipede_segment->getDirection());
        gameObjectsSprite.setRotation(centipede_segment->getRotationAngle());

    }else if(entity_type == ObjectType::MUSHROOM)
    {
        if(object->isPoisoned())
            ++iter_vec;
        auto maxMushLives = 4;
        auto mushCol = maxMushLives - object->getRemainingLives();
        rect = iter_vec->getTextureRect(mushCol);

    }else if(entity_type == ObjectType::SCORPION)
    {
        auto scorpion = std::dynamic_pointer_cast<IMovingEntity>(object);
        rect = iter_vec->getTextureRect(scorpion->getDirection());

    }else
    {
        rect = iter_vec->getTextureRect(Direction::DOWN);
    }

    // Set Texture rect:
    gameObjectsSprite.setTextureRect(rect);
    // Set Origin:
    gameObjectsSprite.setOrigin(std::abs(rect.width/half),
                                std::abs(rect.height/half));
    return gameObjectsSprite;
}

sf::Sprite Presentation::generateSprite(const shared_ptr<IEntity>& object){
    sf::Sprite gameObjectsSprite;
    auto iter_map = game_textures_.find(object->getObjectType());
    auto half = 2.0f;

    if(object->getObjectType() == ObjectType::PLAYER ||
       object->getObjectType() == ObjectType::PLAYER_LASER_BULLET){

        // Set Origin:
        gameObjectsSprite.setOrigin((iter_map->second).getSize().x/half,
                                    (iter_map->second).getSize().y/half);
    }//if
    else{
        gameObjectsSprite = generateSpriteFromSpriteSheet(object);
    }//else

    // Set Texture:
    gameObjectsSprite.setTexture(iter_map->second);

    return gameObjectsSprite;
}

void Presentation::renderWindow(const vector<shared_ptr<IEntity>>& game_objects,
                                const int remaining_lives, const int player_score,
                                const int high_score, tuple<const int, const int> game_level)
{
    window_.clear();
    auto[current_level, max_level] = game_level;
    int number_of_colours = game_level_colours_.size();
    auto level = (current_level-1)%number_of_colours;
    auto level_colour = game_level_colours_.at(level);

    displayLives(remaining_lives, player_score, high_score, game_level, level_colour);

    for(const auto& object : game_objects)
    {
        sf::Sprite gameObjectsSprite = generateSprite(object);
        gameObjectsSprite.setColor(level_colour);
        // Set position:
        gameObjectsSprite.setPosition(object->getPosition().getX_pos(),
                                      object->getPosition().getY_pos());
        window_.draw(gameObjectsSprite);
    }//for

    window_.display();
    auto animation_speed = 0.060f;
    updateAnimations(animation_speed);
}

void Presentation::updateAnimations(float delta_time){

    for(auto& sprite_image : sprite_sheets_)
    {
        if(sprite_image.getObjectType()!=ObjectType::MUSHROOM)
        {
            auto temp = delta_time;
            if(sprite_image.getObjectType()==ObjectType::SCORPION)
                temp/=4.0f;
            sprite_image.update(temp);
        }//if
    }//for
}

void Presentation::drawSplashScreen()
{
    SplashScreen splash_screen{};
    splash_screen.show(window_);
}

void Presentation::drawGameOverScreen(const int player_score, const int high_score)
{
    GameOverScreen gameOverScreen;
    gameOverScreen.show(window_, player_score, high_score);
}

void Presentation::drawGameWonScreen(const int player_score, const int high_score)
{
    GameWonScreen gameWonScreen;
    gameWonScreen.show(window_, player_score, high_score);
}

void Presentation::displayLives(const int remaining_lives, const int player_score,
                                const int high_score, tuple<const int, const int> game_level,
                                const sf::Color level_colour)
{
    sf::Sprite lives_sprite;
    lives_sprite.setColor(level_colour);
    auto half = 2.0f;
    auto iter_map = game_textures_.find(ObjectType::PLAYER);
    lives_sprite.setTexture(iter_map->second);
    lives_sprite.setOrigin((iter_map->second).getSize().x/half,
                           (iter_map->second).getSize().y/half);

    // Draw lives using a sprite and player texture:
    auto xPos = (iter_map->second).getSize().x;
    for(auto i=0; i<(remaining_lives-1); i++)
    {
        lives_sprite.setPosition(xPos, (iter_map->second).getSize().y/half);
        window_.draw(lives_sprite);
        xPos+=(iter_map->second).getSize().x;
    }

    // Draw levels
    auto [current_level, max_level] = game_level;
    string level = "Level "+std::to_string(current_level)+" of "+std::to_string(max_level);
    sf::Text level_text(level, font_);
    level_text.setCharacterSize(18);
    sf::FloatRect titleRect = level_text.getLocalBounds();
    level_text.setOrigin(titleRect.left + titleRect.width/half,
    titleRect.top  + titleRect.height/half);
    level_text.setFillColor(sf::Color::Green);
    xPos+=100.0f;
    level_text.setPosition(xPos, level_text.getCharacterSize()/half);

    // Draw Score and high score:
    sf::Text score_text(std::to_string(player_score), font_);
    score_text.setCharacterSize(20);
    titleRect = score_text.getLocalBounds();
    score_text.setOrigin(titleRect.left + titleRect.width/half,
    titleRect.top  + titleRect.height/half);
    score_text.setFillColor(sf::Color::Magenta);

    score_text.setPosition(sf::Vector2f(window_.getSize().x/half,
                                        score_text.getCharacterSize()/half));

    sf::Text high_score_text(std::to_string(high_score), font_);
    high_score_text.setCharacterSize(20);
    titleRect = high_score_text.getLocalBounds();
    high_score_text.setOrigin(titleRect.left + titleRect.width/half,
    titleRect.top  + titleRect.height/half);
    high_score_text.setFillColor(sf::Color::Yellow);

    high_score_text.setPosition(sf::Vector2f(window_.getSize().x-titleRect.width/half,
                                        high_score_text.getCharacterSize()/half));

    window_.draw(score_text);
    window_.draw(level_text);
    window_.draw(high_score_text);
}

Presentation::~Presentation()
{
    //dtor
}
