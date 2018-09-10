#include "Logic.h"

Logic::Logic():screen_state_{ScreenState::SPLASHSCREEN}
{
    player_ = std::make_shared<Player>(grid_);
    game_objects_.push_back(player_);

    debounceSpaceKey_ = false;
    //ctor
}

void Logic::getInputCommands()
{
    presentation_.processInputEvents();

    if(presentation_.isLeftPressed()) player_->setDirection(Direction::LEFT);
    else if(presentation_.isRightPressed()) player_->setDirection(Direction::RIGHT);
    else if(presentation_.isUpPressed()) player_->setDirection(Direction::UP);
    else if(presentation_.isDownPressed()) player_->setDirection(Direction::DOWN);
    else player_->setDirection(Direction::NONE);

    if(!debounceSpaceKey_ && presentation_.isSpacePressed()){
        debounceSpaceKey_ = true;
        auto bullet_Vector = player_->shoot();

        for(auto &bullets: bullet_Vector){
            game_objects_.push_back(bullets);
        }//for
    }//if

    debounceSpaceKey_ = presentation_.isSpacePressed();
}

void Logic::run()
{
    if(screen_state_==ScreenState::SPLASHSCREEN) renderSplashScreen();
    loadAssets();
    high_score_ = highScoreManager_.getHighScore();

    StopWatch game_timer;
    auto game_speed = 1.0f/6000.0f;
    auto time_elapsed = 0.0f;
    auto timeSinceLastUpdate = 0.0f;
    game_timer.start();

    while(screen_state_ == ScreenState::GAME_ACTIVE){
        game_timer.stop();
        time_elapsed=game_timer.getRunTime();
        timeSinceLastUpdate+=time_elapsed;
        game_timer.start();
        // Check if time that has passed is greater than the frame speed:
        while(timeSinceLastUpdate>game_speed && screen_state_ == ScreenState::GAME_ACTIVE){
            timeSinceLastUpdate-=game_speed;
            getInputCommands();
            if(presentation_.isWindowOpen()==false) return;
            generateNormalCentipede();
            updateGameObjects();

            removeDeadEntities();
            renderGameObjects();
        }//while
    }//while

    if(screen_state_==ScreenState::GAMEOVERSCREEN) renderGameOverScreen();
    if(screen_state_==ScreenState::GAMEWONSCREEN)  renderGameWonScreen();

}
void Logic::loadAssets()
{
    presentation_.loadTextures(assetManager_.getAssetInfo());
}

void Logic::renderSplashScreen()
{
    presentation_.drawSplashScreen();
    screen_state_ = ScreenState::GAME_ACTIVE;
}
void Logic::updateGameObjects()
{
    for(auto& object : game_objects_){
        if(object->isAlive()&& object->getObjectType()!=ObjectType::MUSHROOM){
            auto moving_object_ptr = std::dynamic_pointer_cast<IMovingEntity>(object);
                moving_object_ptr->move();
        }
    }
}

void Logic::removeDeadEntities()
{
    container_erase_if(game_objects_,
                       [](shared_ptr<IEntity>& game_object){
                       return (!game_object->isAlive());
                       });
}

void Logic::renderGameObjects()
{
    presentation_.renderWindow(game_objects_,
                          player_->getRemainingLives(), player_->getScore(),
                          high_score_);
}

void Logic::renderGameOverScreen()
{
    presentation_.drawGameOverScreen(player_->getScore(), high_score_);
}

void Logic::renderGameWonScreen()
{
    presentation_.drawGameWonScreen(player_->getScore(), high_score_);
}
void Logic::generateNormalCentipede(){

    for(auto& segment: enemyFactory_.generateNormalCentipede()){
        game_objects_.push_back(segment);
    }
}

void Logic::generateCentipedeHeads(){

}

Logic::~Logic()
{
    //dtor
}
