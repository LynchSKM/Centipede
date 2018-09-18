#ifndef DIMENSIONS_H
#define DIMENSIONS_H

struct PlayerDimension{

    const float height = 16.0;
    const float width = 16.0;
    const float speed = 0.001;
};

struct CentipedeSegmentDemensions{

    const float height = 14.0;
    const float width = 14.0;
    const float speed = 0.1;
    const float speedY = 16.0;

};

struct PlayerBulletDimentions{

    const float height = 16.0;
    const float width = 16.0;
    const float speed = 0.2;

};

struct MushroomDimensions{

    const float height = 16.0;
    const float width = 16.0;

};

#endif
