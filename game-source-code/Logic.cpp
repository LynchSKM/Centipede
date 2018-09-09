#include "Logic.h"
#include "CentipedeSegment.h"
Logic::Logic():screen_state_{ScreenState::SPLASHSCREEN}
{
    player_ = std::make_shared<Player>(grid_);
    game_objects_.push_back(player_);
    moving_game_objects.push_back(player_);
    auto centi_pede = std::make_shared<CentipedeSegment>(grid_, CentipedeSegment::BodyType::HEAD,
                                                   Position{0, 200}, Direction::RIGHT);
    game_objects_.push_back(centi_pede);
    moving_game_objects.push_back(centi_pede);

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
    }//if

    debounceSpaceKey_ = presentation_.isSpacePressed();

}

void Logic::run()
{
    if(screen_state_==ScreenState::SPLASHSCREEN) renderSplashScreen();

    //screen_state_ = ScreenState::GAME_ACTIVE;
    loadAssets();
    high_score_ = highScoreManager_.getHighScore();

    StopWatch game_timer;
    auto game_speed = 1.0f/6000.0f;
    auto time_elapsed = 0.0f;
    game_timer.start();

    while(screen_state_ == ScreenState::GAME_ACTIVE){
        game_timer.stop();
        time_elapsed=game_timer.getRunTime();

        game_timer.start();
        // Check if time that has passed is greater than the frame speed:
        while(time_elapsed>game_speed && screen_state_ == ScreenState::GAME_ACTIVE){
            getInputCommands();
            if(presentation_.isWindowOpen()==false) return;
            updateGameObjects();

            removeDeadEntities();
            renderGameObjects(time_elapsed);
            //time_elapsed-=game_speed;
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
    container_erase_if(game_objects_,
                       [](shared_ptr<IEntity>& game_object){
                       return (!game_object->isAlive());
                       });
    container_erase_if(moving_game_objects,
                   [](shared_ptr<IMovingEntity>& game_object){
                   return (!game_object->isAlive());
                   });
}

void Logic::renderGameObjects(float delta_time)
{
    presentation_.renderWindow(game_objects_,
                          player_->getRemainingLives(), player_->getScore(),
                          high_score_, delta_time);
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
