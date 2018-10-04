#include "EnemyFactory.h"

EnemyFactory::EnemyFactory(const Grid& grid):
grid_{grid},
isCentipedeGenerated_{false},
isCentipedeHeadsGenerated_{false},
isScorpionGenerated_{false},
timeSinceLastSpider_{0},
spiderReleaseTime_{15.0},
centiHeadsReleaseTime_{7.5},
timeSinceLastcentiHeads_{0}
{
    //ctor
    srand(time(0));
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
        auto direction = static_cast<Direction>(rand()%2 + 2);
        auto centipede_head_ptr = make_shared<CentipedeSegment>(grid_, CentipedeSegment::BodyType::HEAD,
                                                       Position{half_screen_width, -8.0f}, direction);
        centipede.push_back(centipede_head_ptr);

        auto direction_of_head = centipede_head_ptr->getDirection();
        auto start_Xposition = centipede_head_ptr->getPosition().getX_pos();

        for(auto i=1;i<numberOfSegments;i++)
        {
            if(direction_of_head == Direction::RIGHT)
                start_Xposition-=(dimension.width+1);
            else if(direction_of_head == Direction::LEFT)
                start_Xposition+=(dimension.width+1);

            auto centipedeSeg_ptr = make_shared<CentipedeSegment>(grid_, CentipedeSegment::BodyType::BODY,
                                                       Position{start_Xposition, -8.0f}, direction_of_head);
            centipede.push_back(centipedeSeg_ptr);
        }
        isCentipedeGenerated_=true;
    }
    return centipede;
}

vector <shared_ptr<CentipedeSegment>> EnemyFactory::generateCentipedeHeads(const int number_of_heads)
{
    vector<shared_ptr<CentipedeSegment>> centipede_heads;
    struct CentipedeSegmentDemensions centiDimensions;
    auto direction_right = true;
    auto start_Y_pos = grid_.getHeight()-((centiDimensions.width+2.0f)*7.5f);
    if(!isCentipedeHeadsGenerated_)
    {
        CentiHeadsTimer_.pause();
        auto time_elapsed = CentiHeadsTimer_.getPauseTime();
        if((time_elapsed-timeSinceLastcentiHeads_)>centiHeadsReleaseTime_)
        {
            for(auto i=0;i<number_of_heads;i++)
            {
                auto direction = Direction::RIGHT;
                auto start_Xposition = centiDimensions.width/2.0f;
                if(!direction_right)
                {
                    direction = Direction::LEFT;
                    start_Xposition = grid_.getWidth()-centiDimensions.width/2.0f;
                }
                start_Y_pos+= (centiDimensions.height + 2.0f);
                auto centipedeSeg_ptr = make_shared<CentipedeSegment>(grid_, CentipedeSegment::BodyType::HEAD,
                                                           Position{start_Xposition, start_Y_pos}, direction);
                centipede_heads.push_back(centipedeSeg_ptr);
                direction_right = !direction_right;
            }
            timeSinceLastcentiHeads_ = time_elapsed;
            isCentipedeHeadsGenerated_ = true;
        }
        CentiHeadsTimer_.resume();
    }
    return centipede_heads;
}

vector <shared_ptr<Scorpion>> EnemyFactory::generateAScorpion()
{
    vector<shared_ptr<Scorpion>> scorpions;
    if(!isScorpionGenerated_)
    {
        scorpions.push_back(make_shared<Scorpion>(grid_));
        isScorpionGenerated_ = true;
    }
    return scorpions;
}

vector <shared_ptr<Spider>> EnemyFactory::generateASpider()
{
    vector<shared_ptr<Spider>> spider;
    SpiderTimer_.pause();
    auto time_elapsed = SpiderTimer_.getPauseTime();
    if((time_elapsed-timeSinceLastSpider_)>spiderReleaseTime_)
    {
        auto spider_ptr = make_shared<Spider>(grid_);
        spider.push_back(spider_ptr);

        timeSinceLastSpider_ = time_elapsed;
    }
    SpiderTimer_.resume();
    return spider;
}

void EnemyFactory::reset()
{
    isCentipedeGenerated_      = false;
    isCentipedeHeadsGenerated_ = false;
    isScorpionGenerated_       = false;

    timeSinceLastSpider_       = SpiderTimer_.getProcessTime();
    timeSinceLastcentiHeads_   = CentiHeadsTimer_.getProcessTime();

    SpiderTimer_.stop();
    CentiHeadsTimer_.stop();
    SpiderTimer_.start();
    CentiHeadsTimer_.start();
}

double EnemyFactory::getSpiderReleaseTime() const
{
    return spiderReleaseTime_;
}

void EnemyFactory::setSpiderReleaseTime(double new_delay)
{
    spiderReleaseTime_ = new_delay;
}
