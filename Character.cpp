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

#include "Character.h"

void Character::LearnNewAbility()
{
    if(!LearnedAbilities.WallJump)
    {
        LearnedAbilities.WallJump = true;
    }
    else if(!LearnedAbilities.Shoot)
    {
        LearnedAbilities.Shoot = true;
    }
    else if(!LearnedAbilities.DoubleJump)
    {
        LearnedAbilities.DoubleJump = true;
    }
}

void Character::MoveLeft()
{
    if(!Dying)
    {
        if(Speed.X > -maxMoveSpeed)
            --Speed.X;
        MovingRight = false;
    }
}

void Character::MoveRight()
{
    if(!Dying)
    {
        if(Speed.X < maxMoveSpeed)
            ++Speed.X;
        MovingRight = true;
    }
}

void Character::UpdateFrame()
{
    if((AnimationDelay >= 3 && !Dying && !Shooting) || (AnimationDelay >= 6 && Dying) || (AnimationDelay >= 6 && Shooting))
    {
        Frame++;
        AnimationDelay = 0;
    }
    else
        AnimationDelay++;

    if(Dying)
    {
        if(Frame < 21)
            Frame = 21;
        else if(Frame > 27)
            Dead = true;
    }
    else if(Shooting)
    {
        if((MovingRight && !ReadyAbilities.WallJump) || (!MovingRight && ReadyAbilities.WallJump))
        {
            if(Frame < 45 || Frame > 46)
            {
                AnimationDelay = 0;
                Frame = 45;
            }
            else if(Frame == 46 && AnimationDelay == 6)
            {
                Shooting = false;
                AnimationDelay = 0;
            }
        }
        else
        {
            if(Frame < 47 || Frame > 48)
            {
                Frame = 47;
                AnimationDelay = 0;
            }
            else if(Frame == 48 && AnimationDelay == 6)
            {
                AnimationDelay = 0;
                Shooting = false;
            }
        }
    }
    else if(ReadyAbilities.WallJump)
    {
        if(WallJumpRight)
        {
            Frame = 63;
        }
        else
            Frame = 66;
    }
    else if(Speed.Y > 0)
    {
        Frame = 20;
    }
    else if(Speed.Y < 0)
    {
        Frame = 18;
    }
    else if(Speed.X > 0)
    {
        if(Frame >= 8 || Frame < 1)
            Frame = 1;
    }
    else if(Speed.X < 0)
    {
        if(Frame < 9 || Frame >= 16)
            Frame = 9;
    }
    else if(Speed.X == 0 && Speed.Y == 0)
        Frame = 0;
}

void Character::Move()
{
    if(!Dying && (!Shooting || !Grounded))
        Position.X += Speed.X;
    Position.Y += Speed.Y;
}

void Character::MoveDown()
{
    if(Gravity && Speed.Y <= maxMoveSpeed * 1.5)
    {
        ++Speed.Y;
        Grounded = false;
    }
}

void Character::Jump()
{
    if(!Dying)
    {
        if(Speed.Y == 0 && Grounded)
        {
            Speed.Y = -13;
            Grounded = false;
        }
        else if(ReadyAbilities.WallJump)
        {
            Speed.Y = -13;
            ReadyAbilities.WallJump = false;
            if(WallJumpRight)
                Speed.X = 5;
            else
                Speed.X = -5;
        }
        else if(ReadyAbilities.DoubleJump)
        {
            Speed.Y = -13;
            Grounded = false;
            ReadyAbilities.DoubleJump = false;
        }
    }
}
