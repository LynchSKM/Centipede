#ifndef DIMENSIONS_H
#define DIMENSIONS_H

struct PlayerDimension{

    const float height = 16.0;
    const float width = 16.0;
    const float speed = 1.0;
};

struct CentipedeSegmentDemensions{

    const float height = 14.0;
    const float width = 14.0;
    const float speed = 1.0;
    const float speedY = 16.0;

};

struct PlayerBulletDimensions{

    const float height = 12.0;
    const float width = 2.0;
    const float speed = 2.0;

};

struct MushroomDimensions{

    const float height = 15.0;
    const float width = 16.0;

};

struct ScorpionDimensions{

    const float height = 16.0;
    const float width = 32.0;
    const float speed = 0.4;

};

struct SpiderDimensions{
    const float height = 16.0;
    const float width = 30.0;
    const float speed = 0.8;
};

#endif
