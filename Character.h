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

#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

#include "GameObject.h"
#include "Abilities.h"

class Character: public GameObject
{
public:
    int HP;
    int PlayerNumber;
    dVector Speed;
    AbilityList LearnedAbilities;
    AbilityList ReadyAbilities;
    bool Grounded, WallJumpRight, Dying, Dead, Shooting;
    int AnimationDelay;
    int Frame;
    bool Gravity;
    bool MovingRight;

    void MoveRight();
    void MoveLeft();
    void MoveDown();
    void Move();
    void Jump();
    void LearnNewAbility();
    virtual void UpdateFrame();

    Character(int _x, int _y, int _hp, int _playerNum, bool _gravity = true)
    :GameObject("character")
    {
        LearnedAbilities.DoubleJump = false;
        LearnedAbilities.WallJump = false;
        LearnedAbilities.Shoot = false;
        Gravity = _gravity;
        Dying = false;
        Dead = false;
        HP = _hp;
        Height = CHARSIZE;
        Width = CHARSIZE;
        Position.X = _x * TILESIZE;
        Position.Y = _y * TILESIZE;
        PlayerNumber = _playerNum;
        Speed.X = 0;
        Speed.Y = 0;
        Shooting = false;
        Frame = 0;
        AnimationDelay = 0;
        maxMoveSpeed = 3;
    }
protected:
    int maxMoveSpeed;
};

#endif // CHARACTER_H_INCLUDED
