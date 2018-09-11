#include "EnemyFactory.h"

EnemyFactory::EnemyFactory(Grid grid):grid_{grid},
isCentipedeGenerated_{false}
{
    //ctor
}

EnemyFactory::~EnemyFactory()
{
    //dtor
}

vector <shared_ptr<CentipedeSegment>> EnemyFactory::generateNormalCentipede()
{
    vector<shared_ptr<CentipedeSegment>> centipede;
    if(!isCentipedeGenerated_){

        auto numberOfSegments = 7;
        struct CentipedeSegmentDemensions dimension;
        auto half_screen_width = (grid_.getWidth()/2.0f)-dimension.speed;
        auto centipede_head_ptr = make_shared<CentipedeSegment>(grid_, CentipedeSegment::BodyType::HEAD,
                                                       Position{half_screen_width, -8.0f}, Direction::RIGHT);
        centipede.push_back(centipede_head_ptr);
        auto direction_of_head = centipede_head_ptr->getDirection();
        auto start_Xposition = centipede_head_ptr->getPosition().getX_pos();

        for(auto i=1;i<numberOfSegments;i++){
            start_Xposition-=dimension.width;
            auto centipedeSeg_ptr = make_shared<CentipedeSegment>(grid_, CentipedeSegment::BodyType::BODY,
                                                       Position{start_Xposition, -8.0f}, direction_of_head);
            centipede.push_back(centipedeSeg_ptr);
        }
        isCentipedeGenerated_=true;
    }
    return centipede;
}

vector <shared_ptr<CentipedeSegment>> EnemyFactory::generateCentipedeHeads()
{

}
