/**
 * Copyright (C) 2018 David Welch
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; only version 2
 * of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

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
