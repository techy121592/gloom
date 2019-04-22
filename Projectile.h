#ifndef PROJECTILE_H_INCLUDED
#define PROJECTILE_H_INCLUDED

#include "GameObject.h"

class Projectile: public GameObject
{
public:
    void Move();
    bool Moving;
    Projectile(int _x, int _y, bool _movingRight, bool _moving = true)
    :GameObject("projectile")
    {
        Height = PROJECTILESIZE;
        Width = PROJECTILESIZE;
        Position.X = _x;
        Position.Y = _y;
        MovingRight = _movingRight;
        Moving = _moving;
    }
private:
    bool MovingRight;
};

#endif // PROJECTILE_H_INCLUDED
