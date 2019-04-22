/**
 * Copyright (C) 2019 David Welch
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
