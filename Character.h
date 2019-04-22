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
