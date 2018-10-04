#include "GameEngine.h"

GameEngine::GameEngine(const Grid& grid):
grid_{grid},
mushroomfactory_{grid},
collisionHandler_{grid},
enemyFactory_{grid},
timeSinceLastMushroomRegen{0}
{
    //ctor
    srand(time(0));

    player_ = std::make_shared<Player>(grid_);
    game_objects_.push_back(player_);
    moving_game_objects_.push_back(player_);

    high_score_ = highScoreManager_.getHighScore();
}

GameEngine::~GameEngine()
{
    //dtor
}

void GameEngine::getInputCommands(tuple<bool, bool, bool, bool, bool> keyboard_inputs)
{
    bulletFired_ = false;
    auto [isLeftPressed,isRightPressed,isUpPressed,isDownPressed,isSpacePressed] = keyboard_inputs;
    if(isLeftPressed)       player_->setDirection(Direction::LEFT);
    else if(isRightPressed) player_->setDirection(Direction::RIGHT);
    else if(isUpPressed)    player_->setDirection(Direction::UP);
    else if(isDownPressed)  player_->setDirection(Direction::DOWN);
    else player_->setDirection(Direction::NONE);

    if(!debounceSpaceKey_ && isSpacePressed)
    {
        debounceSpaceKey_ = true;
        auto bullet_Vector = player_->shoot();

        for(auto &bullets: bullet_Vector)
        {
            game_objects_.push_back(bullets);
            moving_game_objects_.push_back(bullets);
        }//for
        if(!bullet_Vector.empty()) bulletFired_ = true;
    }//if

    debounceSpaceKey_ = isSpacePressed;
}

bool GameEngine::isPlayerBulletFired() const
{
    return bulletFired_;
}

void GameEngine::levelUp()
{
    if(playerHasLevelledUp())
    {
        StopWatch level_up_timer;
        level_up_timer.start();
        auto delay = 2.0;
        auto time_elapsed = level_up_timer.getProcessTime();
        delay += time_elapsed;

        while(true)
        {
            if(time_elapsed>delay) break;
            level_up_timer.pause();
            time_elapsed = level_up_timer.getPauseTime();
            level_up_timer.resume();
        }
        hasLevelledUp_ = false;
    }
}

void GameEngine::generateMushrooms()
{
    for(auto& mushroom: mushroomfactory_.generateMushrooms())
    {
        game_objects_.push_back(mushroom);
    }
}

void GameEngine::generateGameEnemies()
{
    auto numberOfCentipedesSeg = count_if(moving_game_objects_.begin(),
                                          moving_game_objects_.end(),
                                          [](const shared_ptr<IMovingEntity>& object)
                                          {
                                            return(object->getObjectType()==ObjectType::CENTIPEDE);
                                          });

    if(!resetLevel_  && numberOfCentipedesSeg == 0)
    {
        reset();
        auto decrease_delay_by = 4.0;
        enemyFactory_.setSpiderReleaseTime(enemyFactory_.getSpiderReleaseTime()-decrease_delay_by);
        ++gameLevel_;
        hasLevelledUp_ = true;
        removeMovingEntities();
    }

    if(gameLevel_>1) generateCentipedeHeads(gameLevel_);
    generateNormalCentipede();
    generateAScorpion();
    generateASpider();

    resetLevel_ = false;
    if(gameLevel_> maxLevel_)AllGameStageComplete_ = true;
}

void GameEngine::runGameLogic()
{
    generateGameEnemies();
    moveGameObjects();
    checkCollisions();
    generateAMushroom();
    updateScores();
    removeDeadEntities();
}

bool GameEngine::isMushroomReincarnationComplete()
{
    auto iter_mushroom = game_objects_.begin();
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

                mushroom_reincarnate_timer.resume();
                timeSinceLastMushroomRegen = mushroom_reincarnate_timer.getProcessTime();
                return true;
            }
        }
        else ++iter_mushroom;
    }
    return false;
}

bool GameEngine::allStagesComplete()
{
    return(gameLevel_ > maxLevel_);
}

bool GameEngine::playerHasLevelledUp()
{
    return hasLevelledUp_;
}

bool GameEngine::reincarnatePlayer()
{
    if (player_->isHit() && player_->isAlive())
    {
        removeMovingEntities();
        player_->reincarnate();
        return true;
    }
    return false;
}

void GameEngine::removeMovingEntities()
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
}

void GameEngine::reset()
{
    resetLevel_ = true;
    enemyFactory_.reset();
}

tuple<const vector<IEntity_ptr>&, int, tuple<int, int>, tuple<int,int>> GameEngine::getRenderingParameters()
{
    return {game_objects_, player_->getRemainingLives(), {getGameScores()}, {getGameLevel()}};
}

tuple<int, int> GameEngine::getGameScores()
{
    return {player_->getScore(), high_score_};
}

const vector<IMovingEntity_ptr>& GameEngine::getMovingEntities()
{
    return moving_game_objects_;
}

tuple<int,int> GameEngine::getGameLevel() const
{
    return {gameLevel_,maxLevel_};
}

tuple<bool, bool, bool> GameEngine::getGameStatus()
{
    return{player_->isAlive(), player_->getScore()>highScoreManager_.getHighScore(), allStagesComplete()};
}

void GameEngine::generateNormalCentipede()
{
    for(auto& segment : enemyFactory_.generateNormalCentipede())
    {
        game_objects_.push_back(segment);
        moving_game_objects_.push_back(segment);
    }
}

void GameEngine::generateCentipedeHeads(int numberOfHeads)
{
    for(auto& head_segment : enemyFactory_.generateCentipedeHeads(numberOfHeads))
    {
        game_objects_.push_back(head_segment);
        moving_game_objects_.push_back(head_segment);
    }
}

void GameEngine::generateAMushroom()
{
    for(auto& object: game_objects_)
    {
        if(object->getObjectType() == ObjectType::CENTIPEDE)
            if(!object->isAlive())
                game_objects_.push_back(mushroomfactory_.generateAMushroom(object->getPosition()));
    }
}

void GameEngine::generateAScorpion()
{
    for(auto& scorpion : enemyFactory_.generateAScorpion())
    {
        game_objects_.push_back(scorpion);
        moving_game_objects_.push_back(scorpion);
    }
}

void GameEngine::generateASpider()
{
    for(auto& spider : enemyFactory_.generateASpider())
    {
        game_objects_.push_back(spider);
        moving_game_objects_.push_back(spider);
    }
}

void GameEngine::moveGameObjects()
{
    for(auto& object : moving_game_objects_)
    {
        if(object->isAlive())
            object->move();
    }
}

void GameEngine::removeDeadEntities()
{
    container_erase_if(game_objects_,
    [](shared_ptr<IEntity>& game_object)
    {
        return (!game_object->isAlive());
    });

    container_erase_if(moving_game_objects_,
    [](shared_ptr<IMovingEntity>& game_object)
    {
        return (!game_object->isAlive());
    });
}

void GameEngine::checkCollisions()
{
    collisionHandler_.checkCollisions(game_objects_, moving_game_objects_);
    player_->addScore(collisionHandler_.getPointsObtained());
}

void GameEngine::updateScores()
{
    if(player_->getScore()>highScoreManager_.getHighScore())
        highScoreManager_.setHighScore(player_->getScore());
}
