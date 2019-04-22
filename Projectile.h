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
