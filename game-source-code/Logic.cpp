#include "Logic.h"

Logic::Logic():screen_state_{ScreenState::SPLASHSCREEN}
{
    player_ = std::make_shared<Player>(grid_);
    game_objects_.push_back(player_);
    moving_game_objects.push_back(player_);
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
            moving_game_objects.push_back(bullets);
        }//for
        if(!debounceSpaceKey_ && presentation_.isSpacePressed())
            debounceSpaceKey_ = false;

    }//if

}

void Logic::run()
{
    if(screen_state_==ScreenState::SPLASHSCREEN) renderSplashScreen();

    loadAssets();
    high_score_ = highScoreManager_.getHighScore();

    StopWatch game_timer;
    auto game_speed = 1.0f/5.0f;
    auto deltaTime  = 0.0f;
    game_timer.start();

    while(screen_state_==ScreenState::GAME_ACTIVE){
        game_timer.stop();
        deltaTime+=game_timer.getRunTime();

        game_timer.start();

        // Check if time that has passed is greater than the frame speed:
        while(deltaTime>game_speed && screen_state_ == ScreenState::GAME_ACTIVE){
            getInputCommands();
            updateGameObjects();
            renderGameObjects();
        }
    }
    //if(screen_state_==ScreenState::GAMEOVERSCREEN)renderGameOverScreen();

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
    for(auto& object : moving_game_objects){
        if(object->isAlive()) object->move();
    }
}

void Logic::removeDeadEntities()
{

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


Logic::~Logic()
{
    //dtor
}
