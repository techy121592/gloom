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
