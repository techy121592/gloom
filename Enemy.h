#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED
#include "Character.h"

class Enemy: public Character
{
public:
    int EnemyType;
    bool MovingRight;

    void UpdateFrame();

    Enemy(int _x, int _y, int _hp, int _enemyType, bool _gravity = true)
    :Character(_x, _y, _hp, 0)
    {
        AnimationDelay = 0;
        Frame = 0;
        Gravity = _gravity;
        MovingRight = true;
        EnemyType = _enemyType;
        Width = ENEMYSIZE;
        Height = ENEMYSIZE;
        maxMoveSpeed = 2;
    }
};

#endif // ENEMY_H_INCLUDED
