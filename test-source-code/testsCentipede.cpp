#include "CentipedeSegment.h"
#include "Dimensions.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>


TEST_CASE("Centipede Segment is placed at the right position.")
{

    Grid testGrid{650,600};
    CentipedeSegment centipede_seg(testGrid, CentipedeSegment::BodyType::HEAD,
                               Position{325.0f,580.0f}, Direction::DOWN);

    CHECK(centipede_seg.getPosition() == Position{325.0f,580.0f});
}

TEST_CASE("Centipede Segment can be moved up, down, left and right.")
{

    Grid testGrid{650,600};
    CentipedeSegment centipede_seg(testGrid, CentipedeSegment::BodyType::HEAD,
                               Position{325.0f,300.0f}, Direction::DOWN);

    struct CentipedeSegmentDemensions temp;
    auto x = centipede_seg.getPosition().getX_pos();
    auto y = centipede_seg.getPosition().getY_pos();

    centipede_seg.move();
    y+=temp.speedY;
    x-=temp.speed;
    CHECK(centipede_seg.getPosition() == Position{x, y});

    centipede_seg.move();
    x-=temp.speed;
    CHECK(x == doctest::Approx(centipede_seg.getPosition().getX_pos()));
    CHECK(y == doctest::Approx(centipede_seg.getPosition().getY_pos()));

    centipede_seg.changeDirection();
    centipede_seg.move();
    y+=temp.speedY;
    x+=temp.speed;
    CHECK(centipede_seg.getPosition() == Position{x, y});

    centipede_seg.move();
    x+=temp.speed;
    CHECK(centipede_seg.getPosition() == Position{x, y});
}

TEST_CASE("Centipede Segment move down when poisoned.")
{

    Grid testGrid{650,600};
    CentipedeSegment centipede_seg(testGrid, CentipedeSegment::BodyType::HEAD,
                               Position{325.0f,300.0f}, Direction::LEFT);

    struct CentipedeSegmentDemensions temp;
    auto x = centipede_seg.getPosition().getX_pos();
    auto y = centipede_seg.getPosition().getY_pos()+2.0f*temp.speedY;
    centipede_seg.poison();
    centipede_seg.move();
    centipede_seg.move();
    CHECK(x == doctest::Approx(centipede_seg.getPosition().getX_pos()));
    CHECK(y == doctest::Approx(centipede_seg.getPosition().getY_pos()));
}


TEST_CASE("Centipede Segment turns when it hits the screen boundary on the right.")
{

    Grid testGrid{592,640};
    struct CentipedeSegmentDemensions dimesions;
    CentipedeSegment centipede_seg(testGrid, CentipedeSegment::BodyType::HEAD,
                               Position{592-(dimesions.width/2.0f),300},Direction::RIGHT);


    auto x = centipede_seg.getPosition().getX_pos()-(2.0f*dimesions.speed);
    auto y = centipede_seg.getPosition().getY_pos()+dimesions.speedY;

    centipede_seg.move();
    centipede_seg.move();
    CHECK(x == doctest::Approx(centipede_seg.getPosition().getX_pos()));
    CHECK(y == doctest::Approx(centipede_seg.getPosition().getY_pos()));
    CHECK(centipede_seg.getDirection()== Direction::LEFT);
}

TEST_CASE("Centipede Segment turns when it hits the screen boundary on the left.")
{

    Grid testGrid{600,648};
    struct CentipedeSegmentDemensions dimesions;
    CentipedeSegment centipede_seg(testGrid, CentipedeSegment::BodyType::HEAD,
                               Position{(dimesions.width/2.0f),300.0f},Direction::LEFT);

    auto x = centipede_seg.getPosition().getX_pos()+(2.0f*dimesions.speed);
    auto y = centipede_seg.getPosition().getY_pos()+dimesions.speedY;

    centipede_seg.move();
    centipede_seg.move();
    CHECK(centipede_seg.getPosition() == Position{x, y});
    CHECK(centipede_seg.getDirection()== Direction::RIGHT);
}

TEST_CASE("Centipede Segment turns up when it hits the bottom boundary.")
{

    Grid testGrid{592,640};
    struct CentipedeSegmentDemensions dimesions;
    CentipedeSegment centipede_seg(testGrid, CentipedeSegment::BodyType::HEAD,
                               Position{592-(dimesions.width/2.0f),632},Direction::RIGHT);

    auto x = centipede_seg.getPosition().getX_pos();
    auto y = centipede_seg.getPosition().getY_pos()-dimesions.speedY;

    centipede_seg.move();
    CHECK(centipede_seg.getPosition() == Position{x, y});
    CHECK(centipede_seg.getDirection()== Direction::LEFT);
}
