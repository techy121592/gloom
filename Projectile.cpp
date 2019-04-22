#include "Projectile.h"
#include "Consts.h"

void Projectile::Move()
{
    if(Moving)
    {
        if(MovingRight)
            Position.X += CHAR_MAXMOVESPEED*2;
        else
            Position.X -= CHAR_MAXMOVESPEED*2;
    }
}
