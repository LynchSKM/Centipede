#include "GameEngine.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

TEST_CASE("Game initializes correctly.")
{
    Grid testGrid{592,640};
    GameEngine testGameEngine{testGrid};
    Player testPlayer{testGrid};
    HighScoreManager testHighScoreManager{};

    testGameEngine.generateMushrooms();
    auto[game_objects, player_lives, scores, game_level_info] = testGameEngine.getRenderingParameters();
    auto[current_score, high_score] = scores;
    auto[current_level, max_level]  = game_level_info;

    CHECK_FALSE(game_objects.empty());
    CHECK(current_level == 1);
    CHECK(high_score    == testHighScoreManager.getHighScore());
    CHECK(current_score == 0);
    CHECK(player_lives  == testPlayer.getRemainingLives());
}

TEST_CASE("Moving Entities besides the Player are successfully created in the game.")
{

    Grid testGrid{592,640};
    GameEngine testGameEngine{testGrid};

    testGameEngine.generateMushrooms();
    testGameEngine.runGameLogic();
    auto moving_game_objects = testGameEngine.getMovingEntities();
    auto moving_entities = count_if(moving_game_objects.begin(),
                                    moving_game_objects.end(),
                                    [](const shared_ptr<IMovingEntity>& object)
                                    {
                                        return(object->getObjectType()!=ObjectType::PLAYER);
                                    });
    CHECK(moving_entities>0);
}

TEST_CASE("Player can be moved successfully based on keyboard input.")
{
    Grid testGrid{592,640};
    GameEngine testGameEngine{testGrid};
    Player testPlayer{testGrid};

    testGameEngine.runGameLogic();
    auto moving_game_objects = testGameEngine.getMovingEntities();
    auto iter_player = find_if( moving_game_objects.begin(),
                                moving_game_objects.end(),
                                [](const shared_ptr<IMovingEntity>& object)
                                {
                                    return(object->getObjectType()==ObjectType::PLAYER);
                                });
    // Move left
    auto isLeftPressed  = true;
    auto isRightPressed = false;
    auto isUpPressed    = false;
    auto isDownPressed  = false;
    auto isSpacePressed = false;
    testGameEngine.getInputCommands({isLeftPressed, isRightPressed, isUpPressed,
                                    isDownPressed, isSpacePressed});
    testGameEngine.runGameLogic();

    testPlayer.setDirection(Direction::LEFT);
    testPlayer.move();

    CHECK(testPlayer.getPosition() == (*iter_player)->getPosition());
}

TEST_CASE("Moving entities besides the Player are successfully moved in the game.")
{
    Grid testGrid{592,640};
    GameEngine testGameEngine{testGrid};

    testGameEngine.generateMushrooms();
    testGameEngine.runGameLogic();
    auto moving_game_objects = testGameEngine.getMovingEntities();

    auto moving_game_enemies = vector<IMovingEntity_ptr>(moving_game_objects.size()-1);
    copy_if( moving_game_objects.begin(), moving_game_objects.end(), moving_game_enemies.begin(),
             [](const shared_ptr<IMovingEntity>& object)
             {
                return(object->getObjectType()!=ObjectType::PLAYER);
             });
    // Store current positions:
    vector<Position> previousPositions;
    for(const auto& object : moving_game_enemies)
        previousPositions.push_back(object->getPosition());

    // move:
    testGameEngine.runGameLogic();
    auto index = 0;
    for(const auto& object : moving_game_enemies)
    {
        CHECK_FALSE(previousPositions.at(index) == object->getPosition());
    }
}

TEST_CASE("Player Bullet is fired when space pressed is true.")
{
    Grid testGrid{592,640};
    GameEngine testGameEngine{testGrid};

    testGameEngine.levelUp(); // Adds a delay
    testGameEngine.runGameLogic();
    auto isLeftPressed  = false;
    auto isRightPressed = false;
    auto isUpPressed    = false;
    auto isDownPressed  = false;
    auto isSpacePressed = true; //Shoot

    testGameEngine.getInputCommands({isLeftPressed, isRightPressed, isUpPressed,
                                    isDownPressed, isSpacePressed});

    CHECK(testGameEngine.isPlayerBulletFired());
}
