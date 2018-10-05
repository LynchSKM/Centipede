#include "Logic.h"

Logic::Logic():screen_state_{ScreenState::SPLASHSCREEN}
{
    srand(time(0));
    //ctor
}

void Logic::getInputCommands()
{
    presentation_.processInputEvents();
    auto isLeftPressed  = presentation_.isLeftPressed();
    auto isRightPressed = presentation_.isRightPressed();
    auto isUpPressed    = presentation_.isUpPressed();
    auto isDownPressed  = presentation_.isDownPressed();
    auto isSpacePressed = presentation_.isSpacePressed();

    gameEngine_.processInputCommands({isLeftPressed, isRightPressed, isUpPressed,
                                   isDownPressed, isSpacePressed});

    if(gameEngine_.isPlayerBulletFired()) presentation_.processPlayerShootSound();
}

void Logic::run()
{
    if(screen_state_==ScreenState::SPLASHSCREEN) renderSplashScreen();
    loadAssets();
    startUp();
    game_timer_.start();
    auto game_speed = 1.0f/600.0f;
    auto timeSinceLastUpdate = 0.0;

    while(screen_state_ == ScreenState::GAME_ACTIVE)
    {
        game_timer_.stop();
        timeSinceLastUpdate+=game_timer_.getRunTime();
        game_timer_.start();
        // Check if time that has passed is greater than the frame speed:
        while(timeSinceLastUpdate>game_speed && screen_state_ == ScreenState::GAME_ACTIVE)
        {
            if(presentation_.isWindowOpen()==false) return;
            timeSinceLastUpdate-=game_speed;
            updateGame();
        }//while
    }//while

    if(screen_state_ == ScreenState::GAMEOVERSCREEN) renderGameOverScreen();
    if(screen_state_ == ScreenState::GAMEWONSCREEN)  renderGameWonScreen();
}

void Logic::updateGame()
{
    getInputCommands();
    levelUp();
    gameEngine_.runGameLogic();
    updateScores();
    reincarnatePlayer();
    renderGameObjects();
    updateMovingObjectsSound();
}

void Logic::startUp()
{
    gameEngine_.generateMushrooms();
    renderGameObjects();
}

void Logic::loadAssets()
{
    AssetManager::loadTextureDetails();
    presentation_.loadTextures(assetManager_.getAssetInfo());
}

void Logic::renderSplashScreen()
{
    presentation_.drawSplashScreen();
    screen_state_ = ScreenState::GAME_ACTIVE;
}

void Logic::updateMovingObjectsSound()
{
    for(const auto& object : gameEngine_.getMovingEntities())
        presentation_.processGameObjectSound(object->getObjectType());
}

void Logic::levelUp()
{
    game_timer_.pause();
    if(gameEngine_.playerHasLevelledUp())
    {
        presentation_.processLevelUpSound();
        gameEngine_.levelUp();
    }
    game_timer_.resume();
}

void Logic::renderGameObjects()
{
    auto[game_objects, player_lives, scores, game_level_info] = gameEngine_.getRenderingParameters();
    auto[score, high_score] = scores;
    presentation_.renderWindow(game_objects, player_lives, score, high_score, game_level_info);
}

void Logic::renderGameOverScreen()
{
    auto[score, high_score] = gameEngine_.getGameScores();
    presentation_.drawGameOverScreen(score, high_score);
}

void Logic::renderGameWonScreen()
{
    auto[score, high_score] = gameEngine_.getGameScores();
    presentation_.drawGameWonScreen(score, high_score);
}

void Logic::reincarnateMushrooms()
{
    game_timer_.pause();
    while(true)
    {
        if(gameEngine_.isMushroomReincarnationComplete())
        {
            presentation_.processGameObjectSound(ObjectType::MUSHROOM);
            renderGameObjects();
        }
        else break;
    }
    game_timer_.resume();
}

void Logic::reincarnatePlayer()
{
    if(gameEngine_.reincarnatePlayer())
    {
        reincarnateMushrooms();
        gameEngine_.reset();
        gameEngine_.generateGameEnemies();
    } else return;
}

void Logic::updateScores()
{
    // Check highscore:
    auto[isPlayerAlive, highScorePassed, stagesComplete] = gameEngine_.getGameStatus();

    if(!isPlayerAlive)
        screen_state_= ScreenState::GAMEOVERSCREEN;
    else if(stagesComplete && isPlayerAlive || (!isPlayerAlive && highScorePassed))
        screen_state_= ScreenState::GAMEWONSCREEN;
}

Logic::~Logic()
{
    //dtor
}
