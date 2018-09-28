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
    auto game_speed = 1.0f/4000.0f;
    auto timeSinceLastUpdate = 0.0;

    while(screen_state_ == ScreenState::GAME_ACTIVE)
    {
        timeSinceLastUpdate+=game_timer.getStopTime();
        game_timer.start();
        // Check if time that has passed is greater than the frame speed:
        while(timeSinceLastUpdate>game_speed && screen_state_ == ScreenState::GAME_ACTIVE)
        {
            timeSinceLastUpdate-=game_speed;
            getInputCommands();
            if(presentation_.isWindowOpen()==false) return;
            generateGameEnemies();
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
    for(auto& object : moving_game_objects_)
    {
        if(object->isAlive())
        {
            object->move();
            presentation_.processGameObjectSound(object->getObjectType());
        }
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

void Logic::generateGameEnemies()
{
    generateNormalCentipede();
    generateAScorpion();
    //generateASpider();
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

void Logic::generateASpider()
{
    for(auto& spider: enemyFactory_.generateASpider())
    {
        game_objects_.push_back(spider);
        moving_game_objects_.push_back(spider);
    }//for
}

void Logic::reincarnateMushroom()
{
    StopWatch mushroom_reincarnate_timer;
    mushroom_reincarnate_timer.start();
    auto iter_mushroom = game_objects_.begin();
    auto timeSinceLastMushroomRegen = 0.0;
    auto delay = 0.30;
    while(iter_mushroom!=game_objects_.end())
    {
        if((*iter_mushroom)->getObjectType() == ObjectType::MUSHROOM
           && (*iter_mushroom)->getRemainingLives()<4 || (*iter_mushroom)->isPoisoned())
        {
            mushroom_reincarnate_timer.pause();
            auto time_elapsed = mushroom_reincarnate_timer.getPauseTime();
            if((time_elapsed-timeSinceLastMushroomRegen)>delay)
            {
                timeSinceLastMushroomRegen = time_elapsed;
                (*iter_mushroom)->reincarnate();
                renderGameObjects();
                presentation_.processGameObjectSound(ObjectType::MUSHROOM);
                mushroom_reincarnate_timer.resume();
                ++iter_mushroom;
            }
        }
        else ++iter_mushroom;
    }
}

void Logic::reincarnatePlayer()
{
    if (player_->isHit() && player_->isAlive())
    {
        container_erase_if(game_objects_,
        [](shared_ptr<IEntity>& game_object)
        {
            return (game_object->getObjectType() != ObjectType::PLAYER &&
                    game_object->getObjectType() != ObjectType::MUSHROOM);
        });

        container_erase_if(moving_game_objects_,
        [](shared_ptr<IMovingEntity>& game_object)
        {
            return (game_object->getObjectType() != ObjectType::PLAYER);
        });

        reincarnateMushroom();
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
