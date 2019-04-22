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

#include "Enemy.h"

void Enemy::UpdateFrame()
{
    if(AnimationDelay > 3)
    {
        Frame++;
        AnimationDelay = 0;
    }
    else
        AnimationDelay++;
    if(!MovingRight)
    {
        if(Frame > 3 || Frame < 0)
            Frame = 0;
    }
    else
    {
        if(Frame > 7 || Frame < 4)
            Frame = 4;
    }
}
