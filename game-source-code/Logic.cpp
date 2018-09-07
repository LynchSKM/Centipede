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
    }
    if(!debounceSpaceKey_ && presentation_.isSpacePressed())debounceSpaceKey_ = false;
}
}

void Logic::run()
{
    if(screen_state_==ScreenState::SPLASHSCREEN) renderSplashScreen();
    //screen_state_=ScreenState::;
    while(screen_state_==ScreenState::GAME_ACTIVE){

    }
    //if(screen_state_==ScreenState::GAMEOVERSCREEN)renderGameOverScreen();

}
void Logic::loadAssets()
{

}

void Logic::renderSplashScreen()
{
    presentation_.drawSplashScreen();
    screen_state_ = ScreenState::GAME_ACTIVE;
}

void Logic::renderGameObjects()
{

}

void Logic::renderGameOverScreen()
{
    presentation_.drawGameOverScreen(player_->getScore(),highScoreManager_.getHighScore());
}

void Logic::renderGameWonScreen()
{
    presentation_.drawGameWonScreen(player_->getScore(),highScoreManager_.getHighScore());
}


Logic::~Logic()
{
    //dtor
}
