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

    if(!debounceSpaceKey_ && presentation_.isSpacePressed()) {
        debounceSpaceKey_ = true;
        auto bullet_Vector = player_->shoot();

        for(auto &bullets: bullet_Vector) {
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

    while(screen_state_ == ScreenState::GAME_ACTIVE) {
        game_timer.stop();
        timeSinceLastUpdate+=game_timer.getRunTime();
        game_timer.start();
        // Check if time that has passed is greater than the frame speed:
        while(timeSinceLastUpdate>game_speed && screen_state_ == ScreenState::GAME_ACTIVE) {
            timeSinceLastUpdate-=game_speed;
            getInputCommands();
            if(presentation_.isWindowOpen()==false) return;
            generateNormalCentipede();
            generateAScorpion();
            updateGameObjects();
            checkCollisions();
            generateMushroomAtCollision();
            updateScores();
            reincarnatePlayer();
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
    for(auto& object : moving_game_objects_) {
        if(object->isAlive())
            object->move();
    }
}

void Logic::removeDeadEntities()
{
    container_erase_if(game_objects_,
    [](shared_ptr<IEntity>& game_object) {
        return (!game_object->isAlive());
    });

    container_erase_if(moving_game_objects_,
    [](shared_ptr<IMovingEntity>& game_object) {
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

void Logic::generateCentipedeHeads()
{
    for(auto& segment: enemyFactory_.generateCentipedeHeads())
    {
        game_objects_.push_back(segment);
        moving_game_objects_.push_back(segment);
    }//for
}
void Logic::generateMushrooms() {
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

void Logic::generateMushroomAtCollision()
{
    for(auto& object: game_objects_)
    {
        if(object->getObjectType() == ObjectType::CENTIPEDE)
            if(!object->isAlive())
                game_objects_.push_back(enemyFactory_.generateAMushroom(object->getPosition()));
    }
}

void Logic::generateAScorpion()
{
    for(auto& scorpion: enemyFactory_.generateAScorpion())
    {
        game_objects_.push_back(scorpion);
        moving_game_objects_.push_back(scorpion);
    }//for
}

void Logic::reincarnatePlayer()
{
    if (player_->isHit() && player_->isAlive())
    {
        container_erase_if(game_objects_,
        [](shared_ptr<IEntity>& game_object)
        {
            return (game_object->getObjectType() == ObjectType::CENTIPEDE);
        });

        container_erase_if(moving_game_objects_,
        [](shared_ptr<IMovingEntity>& game_object)
        {
            return (game_object->getObjectType() == ObjectType::CENTIPEDE);
        });

        std::transform(game_objects_.begin(), game_objects_.end(),
                       game_objects_.begin(),
                       [](IEntity_ptr& object)
                       {
                            if(object->getObjectType() == ObjectType::MUSHROOM && object->isAlive())
                                object->reincarnate();

                            return object;
                       });

        enemyFactory_.reset();
        generateNormalCentipede();
        player_->reincarnate();

    } else return;

}

void Logic::updateScores()
{
    auto numberOfCentipedesSeg = count_if(moving_game_objects_.begin(),
                                          moving_game_objects_.end(),
                                          [](const IMovingEntity_ptr& object)
                                          {
                                            return(object->getObjectType()==ObjectType::CENTIPEDE);
                                          });

    // Check highscore:
    auto highScorePassed = player_->getScore()>highScoreManager_.getHighScore();
    auto CentipedeDead   = numberOfCentipedesSeg == 0;

    if(!player_->isAlive())
        screen_state_= ScreenState::GAMEOVERSCREEN;
    else if(CentipedeDead && player_->isAlive() || (!player_->isAlive() && highScorePassed))
        screen_state_= ScreenState::GAMEWONSCREEN;


    if(highScorePassed)
    {
        highScoreManager_.setHighScore(player_->getScore());
    }
}

Logic::~Logic()
{
    //dtor
}
