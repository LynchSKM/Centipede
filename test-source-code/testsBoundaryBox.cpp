#include "BoundaryBox.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

TEST_CASE("A Boundary box can be constructed correctly"){

    //BoundaryBox(Position centre, float width, float height, float rotationAngle);
    Position Origin{325.0f,580.0f};
    auto width  = 30.0f;
    auto height = 40.0f;

    vector<Position> rectA{Position{310,560}, Position{340,560}, Position{310,600}, Position{340,600}};

    BoundaryBox testBox{Origin, width, height, 0.0f};
    auto testRect = testBox.getVertices();

    CHECK(rectA.at(0) == testRect.at(0));
    CHECK(rectA.at(1) == testRect.at(1));
    CHECK(rectA.at(2) == testRect.at(2));
    CHECK(rectA.at(3) == testRect.at(3));

}

TEST_CASE("A Boundary box rotated clockwise can be constructed correctly"){

    Position Origin{325.0f,580.0f};
    auto width  = 30.0f;
    auto height = 40.0f;

    vector<Position> rectA{Position{300.25,576.460}, Position{321.464,555.251}, Position{328.535,604.748}, Position{349.748,583.535}};

    BoundaryBox testBox{Origin, width, height, 45.0f};
    auto testRect = testBox.getVertices();

    CHECK(rectA.at(0).getX_pos() == doctest::Approx(testRect.at(0).getX_pos()));
    CHECK(rectA.at(0).getY_pos() == doctest::Approx(testRect.at(0).getY_pos()));

    CHECK(rectA.at(1).getX_pos() == doctest::Approx(testRect.at(1).getX_pos()));
    CHECK(rectA.at(1).getY_pos() == doctest::Approx(testRect.at(1).getY_pos()));

    CHECK(rectA.at(2).getX_pos() == doctest::Approx(testRect.at(2).getX_pos()));
    CHECK(rectA.at(2).getY_pos() == doctest::Approx(testRect.at(2).getY_pos()));

    CHECK(rectA.at(3).getX_pos() == doctest::Approx(testRect.at(3).getX_pos()));
    CHECK(rectA.at(3).getY_pos() == doctest::Approx(testRect.at(3).getY_pos()));

}

TEST_CASE("A Boundary box rotated anti-clockwise can be constructed correctly"){

    Position Origin{325.0f,580.0f};
    auto width  = 30.0f;
    auto height = 40.0f;

    vector<Position> rectA{Position{300.25,583.53}, Position{328.535,555.251}, Position{321.464,604.748}, Position{349.748,576.464}};

    BoundaryBox testBox{Origin, width, height, -45.0f};
    auto testRect = testBox.getVertices();

    CHECK(rectA.at(0).getX_pos() == doctest::Approx(testRect.at(0).getX_pos()));
    CHECK(rectA.at(0).getY_pos() == doctest::Approx(testRect.at(0).getY_pos()));

    CHECK(rectA.at(1).getX_pos() == doctest::Approx(testRect.at(1).getX_pos()));
    CHECK(rectA.at(1).getY_pos() == doctest::Approx(testRect.at(1).getY_pos()));

    CHECK(rectA.at(2).getX_pos() == doctest::Approx(testRect.at(2).getX_pos()));
    CHECK(rectA.at(2).getY_pos() == doctest::Approx(testRect.at(2).getY_pos()));

    CHECK(rectA.at(3).getX_pos() == doctest::Approx(testRect.at(3).getX_pos()));
    CHECK(rectA.at(3).getY_pos() == doctest::Approx(testRect.at(3).getY_pos()));

}

TEST_CASE("A Boundary box rotated 90 degrees anti-clockwise can be constructed correctly"){

    Position Origin{325.0f,580.0f};
    auto width  = 30.0f;
    auto height = 40.0f;

    vector<Position> rectA{Position{305,565}, Position{345,565}, Position{305,595}, Position{345,595}};

    BoundaryBox testBox{Origin, width, height, 90.0f};
    auto testRect = testBox.getVertices();

    CHECK(rectA.at(0) == testRect.at(0));
    CHECK(rectA.at(1) == testRect.at(1));
    CHECK(rectA.at(2) == testRect.at(2));
    CHECK(rectA.at(3) == testRect.at(3));


}

