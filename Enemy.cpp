#include "Enemy.h"

void Enemy::UpdateFrame()
{
    if(AnimationDelay > 3)
    {
        Frame++;
        AnimationDelay = 0;
    }
    else
        AnimationDelay++;
    if(!MovingRight)
    {
        if(Frame > 3 || Frame < 0)
            Frame = 0;
    }
    else
    {
        if(Frame > 7 || Frame < 4)
            Frame = 4;
    }
}
