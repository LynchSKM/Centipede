#include "EnemyFactory.h"

EnemyFactory::EnemyFactory(const Grid& grid):
grid_{grid},
isCentipedeGenerated_{false},
mushroomfactory_{grid},
isCentipedeHeadsGenerated_{false}
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
    if(!isCentipedeGenerated_)
    {

        auto numberOfSegments = 10;
        struct CentipedeSegmentDemensions dimension;
        auto half_screen_width = (grid_.getWidth()/2.0f)-dimension.speed;
        auto centipede_head_ptr = make_shared<CentipedeSegment>(grid_, CentipedeSegment::BodyType::HEAD,
                                                       Position{half_screen_width, -8.0f}, Direction::RIGHT);
        centipede.push_back(centipede_head_ptr);
        auto direction_of_head = centipede_head_ptr->getDirection();
        auto start_Xposition = centipede_head_ptr->getPosition().getX_pos();

        for(auto i=1;i<numberOfSegments;i++)
        {
            start_Xposition-=(dimension.width+1);
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
    vector<shared_ptr<CentipedeSegment>> centipede_heads;
    auto direction_right = true;
    if(!isCentipedeHeadsGenerated_)
    {
        auto numberOfSegments = 2;
        auto start_Y_pos = grid_.getHeight()-56.0f;
        for(auto i=0;i<numberOfSegments;i++)
        {
            auto direction = Direction::RIGHT;
            auto start_Xposition = 8.0f;
            if(!direction_right)
            {
                direction = Direction::LEFT;
                start_Xposition = grid_.getWidth()-8.0f;
                //
            }

            auto centipedeSeg_ptr = make_shared<CentipedeSegment>(grid_, CentipedeSegment::BodyType::HEAD,
                                                       Position{start_Xposition, start_Y_pos}, direction);
            centipede_heads.push_back(centipedeSeg_ptr);
            direction_right = !direction_right;
        }

        isCentipedeHeadsGenerated_ = true;
    }//if
    return centipede_heads;
}
vector <shared_ptr<Mushroom>> EnemyFactory::generateMushrooms()
{
    vector<shared_ptr<Mushroom>> mushrooms;
    for(auto& mushroom: mushroomfactory_.generateMushrooms()){
        mushrooms.push_back(mushroom);
    }
    return mushrooms;
}

void EnemyFactory::reset()
{
    isCentipedeGenerated_ = false;
    isCentipedeHeadsGenerated_ = false;
}
