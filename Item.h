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

#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED
#include "GameObject.h"

class Item: public GameObject
{
    public:
    int ItemType;
    bool Visible;

    Item(int _x, int _y, int _itemType)
    :GameObject("item")
    {
        Position.X = _x * TILESIZE;
        Position.Y = _y * TILESIZE;
        ItemType = _itemType;
        Visible = true;
    }

    Item(int _x, int _y, int _itemType, int _width, int _height)
    :GameObject("item")
    {
        Width = _width;
        Height = _height;
        Position.X = _x * TILESIZE;
        Position.Y = _y * TILESIZE;
        ItemType = _itemType;
        Position.Y += (TILESIZE - Height)/2;
        Position.X += (TILESIZE - Width)/2;
        Visible = true;
    }
};

#endif // ITEM_H_INCLUDED
