#include "Logic.h"

Logic::Logic():screen_state_{ScreenState::SPLASHSCREEN}
{
    player_ = std::make_shared<Player>(grid_);
    game_objects_.push_back(player_);
    moving_game_objects_.push_back(player_);
    srand(time(0));
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
            moving_game_objects_.push_back(bullets);
        }//for
        if(!bullet_Vector.empty()) presentation_.processPlayerShootSound();
    }//if

    debounceSpaceKey_ = presentation_.isSpacePressed();
}

void Logic::run()
{
    if(screen_state_==ScreenState::SPLASHSCREEN) renderSplashScreen();
    loadAssets();
    high_score_ = highScoreManager_.getHighScore();
    generateMushrooms();

    StopWatch game_timer;
    game_timer.start();
    auto game_speed = 1.0f/6000.0f;
    //auto time_elapsed = 0.0;
    auto timeSinceLastUpdate = 0.0;

    while(screen_state_ == ScreenState::GAME_ACTIVE)
    {
        game_timer.stop();
        timeSinceLastUpdate+=game_timer.getRunTime();
        game_timer.start();
        // Check if time that has passed is greater than the frame speed:
        while(timeSinceLastUpdate>game_speed && screen_state_ == ScreenState::GAME_ACTIVE)
        {
            timeSinceLastUpdate-=game_speed;
            getInputCommands();
            if(presentation_.isWindowOpen()==false) return;
            generateNormalCentipede();
            updateGameObjects();
            checkCollisions();
            updateScores();
            removeDeadEntities();
            renderGameObjects();
        }//while
    }//while

    if(screen_state_ == ScreenState::GAMEOVERSCREEN) renderGameOverScreen();
    if(screen_state_ == ScreenState::GAMEWONSCREEN)  renderGameWonScreen();

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
    for(auto& object : moving_game_objects_)
    {
        //if(object->isAlive()&& object->getObjectType()!=ObjectType::MUSHROOM){
           // auto moving_object_ptr = std::dynamic_pointer_cast<IMovingEntity>(object);
        if(object->isAlive())
            object->move();
    }
}

void Logic::removeDeadEntities()
{
    container_erase_if(game_objects_,
                       [](shared_ptr<IEntity>& game_object){
                       return (!game_object->isAlive());
                       });

    container_erase_if(moving_game_objects_,
                       [](shared_ptr<IMovingEntity>& game_object){
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
void Logic::generateNormalCentipede()
{

    for(auto& segment: enemyFactory_.generateNormalCentipede())
    {
        game_objects_.push_back(segment);
        moving_game_objects_.push_back(segment);
    }
}

void Logic::generateCentipedeHeads(){

}
void Logic::generateMushrooms()
{
    for(auto& mushroom: enemyFactory_.generateMushrooms())
    {
        game_objects_.push_back(mushroom);
    }
}

void Logic::checkCollisions()
{
    collisionHandler_.checkCollisions(game_objects_, moving_game_objects_);
    player_->addScore(collisionHandler_.getPointsObtained());
}

void Logic::updateScores()
{
    // Check highscore:
    if(player_->getScore()>highScoreManager_.getHighScore())
        highScoreManager_.setHighScore(player_->getScore());

    if(!player_->isAlive())
        screen_state_= ScreenState::GAMEOVERSCREEN;
}

Logic::~Logic()
{
    //dtor
}
