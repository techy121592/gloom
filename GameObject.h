#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include <stdlib.h>
#include <string>
#include "DVector.h"
#include "Consts.h"

class GameObject
{
public:
    dVector Position;
    long Width;
    long Height;
    std::string Name;
    bool Visible;

    GameObject(std::string _name)
    {
        Name = _name;
        Position.X = 0;
        Position.Y = 0;
        Width = TILESIZE;
        Height = TILESIZE;
        Visible = true;
    }
};

#endif // GAMEOBJECT_H_INCLUDED
