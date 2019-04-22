#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED

#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "GameObject.h"

class Tile: public GameObject
{
    public:
    int TileType;

    Tile(int _x, int _y, int _tileType)
    :GameObject("tile")
    {
        Position.X = _x * TILESIZE;
        Position.Y = _y * TILESIZE;
        TileType = _tileType;
    }

    Tile(int _x, int _y, int _tileType, int _width, int _height)
    :GameObject("tile")
    {
        Width = _width;
        Height = _height;
        Position.X = _x * TILESIZE;
        Position.Y = _y * TILESIZE;
        TileType = _tileType;
        if(TileType == T_SPIKES)
            Position.Y += TILESIZE - Height;
    }
};

#endif // TILE_H_INCLUDED
