#include "HighScoreManager.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>


// DATA LAYER
TEST_CASE("HighScoreManager can set and retrieve the High score successfully from a textfile")
{
    HighScoreManager high_score_manager{};
    auto high_score = 5000;
    high_score_manager.setHighScore(high_score);

    CHECK(high_score == high_score_manager.getHighScore());
}
