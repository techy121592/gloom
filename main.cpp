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

#include "Game.h"

int main ( int _argc, char** _argv )
{
    bool done = false;
    int selection = 0;

    screen = Initialize();
    LoadImages();

    if(tileSet == NULL || characterImage == NULL || itemSet == NULL ||
       enemySheet == NULL || backgroundImage == NULL || projectileImage == NULL ||
       wallJumpMsgImage == NULL || doubleJumpMsgImage == NULL || gunMsgImage == NULL ||
       mainMenuBGImage == NULL || instructionsImage == NULL || endGameImage == NULL)
   {
       printf("Unable to load at least one image.");
       exit(1);
   }

    if(Mix_OpenAudio(22050, AUDIO_S16, 2, 4096))
    {
        printf("Unable to open audio\n");
        exit(1);
    }
    Mix_Music* backgroundMusic = Mix_LoadMUS("bg2.ogg"); // I have 3 different background songs. they are call bg1.ogg bg2.ogg bg3.ogg check these out. let me know which is the best for level background music
    if(backgroundMusic == NULL)
    {
        printf("Unable to load music file.");
        exit(1);
    }
    if(Mix_PlayMusic(backgroundMusic, -1))
    {
        printf("Unable to play music.");
        exit(1);
    }
    TimerStart();

    while (!done)
    {
        if(TimeElapsed() >= 17)
        {
            TimerStart();
            done = Events();
            if(gameState == Game)
            {
                if(keys.A)
                {
                    PlayerShoot();
                    keys.A = false;
                }
                MoveCharacter();
                player1->UpdateFrame();
                MoveEnemies();
                MoveProjectile(playerProjectile, map, enemies);
                if(player1->Dead)
                    LoadLevel();
                if(level > MAXLEVEL)
                    gameState = Message;
            }
            if(gameState != MainMenu)
            {
                DrawImage(0, 0, screen->w, screen->h, backgroundImage, screen);
                dVector offSet;
                offSet = ScrollScreen();
                DrawEnemies(enemies, enemySheet, screen, offSet);
                DrawCharacter(player1, characterImage, screen, offSet);
                DrawProjectile(playerProjectile, projectileImage, screen, offSet);
                DrawMap(map, tileSet, screen, offSet);
                DrawItems(items, itemSet, screen, offSet);
            }
            else
            {
                if(keys.Up || keys.Down)
                {
                    selection++;
                    if(selection > 1)
                        selection = 0;
                    keys.Up = false;
                    keys.Down = false;
                }
                if(keys.Enter)
                {
                    if(selection == 0)
                    {
                        ResetGame();
                        gameState = Message;
                    }
                    else
                        return 0;
                    keys.Enter = false;
                }
                DrawImage(0, 0, screen->w, screen->h, mainMenuBGImage, screen);
                DrawImage(121, 128 + 50 * selection, 47, 54, arrowImage, screen);
            }
            if(gameState == Message)
            {
                if(keys.A)
                {
                    if(level <= MAXLEVEL)
                        gameState = Game; // Return to game
                    else
                        gameState = MainMenu;
                    keys.A = false; // Prevents from instantly shooting
                }
                if(level > MAXLEVEL)
                    DrawImage(((screen->w - endGameImage->w)/2), ((screen->h - endGameImage->h)/2), 400, 200, endGameImage, screen);
                else if(player1->LearnedAbilities.DoubleJump)
                    DrawImage(((screen->w - doubleJumpMsgImage->w)/2), ((screen->h - doubleJumpMsgImage->h)/2), 400, 200, doubleJumpMsgImage, screen);
                else if(player1->LearnedAbilities.Shoot)
                    DrawImage(((screen->w - gunMsgImage->w)/2), ((screen->h - gunMsgImage->h)/2), 400, 200, gunMsgImage, screen);
                else if(player1->LearnedAbilities.WallJump)
                    DrawImage(((screen->w - wallJumpMsgImage->w)/2), ((screen->h - wallJumpMsgImage->h)/2), 400, 200, wallJumpMsgImage, screen);
                else
                    DrawImage(((screen->w - instructionsImage->w)/2), ((screen->h - instructionsImage->h)/2), 400, 200, instructionsImage, screen);
            }
            SDL_Flip(screen);
        }
        else
        {
            SDL_Delay(1);
        }
    }
    return 0;
}

void ResetGame()
{
    level = 1;
    keys.Left = false;
    keys.Right = false;
    playerProjectile = new Projectile(0, 0, true, false);
    savedAbilities.DoubleJump = false;
    savedAbilities.Shoot = false;
    savedAbilities.WallJump = false;
    LoadLevel();
}

char** CurrentLevel()
{
    switch(level)
    {
        case 1: return level1; break;
        case 2: return level2; break;
        case 3: return level3; break;
        default: return level1; break;
    }
}

int CurrentLevelHeight()
{
    switch(level)
    {
        case 1: return ((sizeof(level1)/sizeof(level1)[0])-1); break;
        case 2: return ((sizeof(level2)/sizeof(level2)[0])-1); break;
        case 3: return ((sizeof(level3)/sizeof(level3)[0])-1); break;
        default: return ((sizeof(level1)/sizeof(level1)[0])-1); break;
    }
}

void MoveProjectile(Projectile* _projectile, std::vector<Tile*> _map, std::vector<Enemy*> _enemies)
{
    //Checks for collision between projectile and the map
    for(unsigned int x = 0; x < _map.size(); x++)
    {
        Tile* tempTile = _map[x];
        if(tempTile->TileType != T_BLOCKER)
        {
            if(tempTile->Position.X <= _projectile->Position.X + _projectile->Width)
            {
                if(tempTile->Position.X + tempTile->Width >= _projectile->Position.X)
                {
                    if(tempTile->Position.Y <= _projectile->Position.Y + _projectile->Height)
                    {
                        if(tempTile->Position.Y + tempTile->Height >= _projectile->Position.Y)
                        {
                            _projectile->Moving = false;
                            return;
                        }
                    }
                }
            }
        }
    }

    //Checks for collision between enemies
    for(unsigned int y = 0; y < _enemies.size(); y++)
    {
        Enemy* tempEnemy = _enemies[y];
        if(!tempEnemy->Dead)
        {
            if(tempEnemy->Position.X <= _projectile->Position.X + _projectile->Width)
            {
                if(tempEnemy->Position.X + tempEnemy->Width >= _projectile->Position.X)
                {
                    if(tempEnemy->Position.Y <= _projectile->Position.Y + _projectile->Height)
                    {
                        if(tempEnemy->Position.Y + tempEnemy->Height >= _projectile->Position.Y)
                        {
                            _projectile->Moving = false;
                            tempEnemy->Dead = true;
                            return;
                        }
                    }
                }
            }
        }
    }
    _projectile->Move();
}

dVector ScrollScreen()
{
    dVector offSet;
    int maxSize = strlen(CurrentLevel()[0])*32;
    if(player1->Position.X > screen->w/2 && maxSize > screen->w)
    {
        offSet.X = player1->Position.X;
        if(offSet.X + screen->w/2 > maxSize)
           offSet.X = maxSize-screen->w/2;
    }
    else
        offSet.X = 0;
    maxSize = CurrentLevelHeight()*32;
    if(player1->Position.Y > screen->h/2 && maxSize > screen->h)
    {
        offSet.Y = player1->Position.Y;
        if(offSet.Y + screen->h/2 > maxSize)
           offSet.Y = maxSize-screen->h/2;
    }
    else
        offSet.Y = 0;
    return offSet;
}

void MoveEnemies()
{
    for(unsigned int i = 0; i < enemies.size(); i++)
    {
        Enemy* tempEnemy = enemies[i];
        if(tempEnemy->MovingRight)
        {
            tempEnemy->MoveRight();
        }
        else
        {
            tempEnemy->MoveLeft();
        }
        if(Collision(tempEnemy, tempEnemy->Speed, true))
        {
            tempEnemy->MovingRight = !tempEnemy->MovingRight;
            tempEnemy->Speed.X = 0;
        }
        tempEnemy->MoveDown();
        if(Collision(tempEnemy, tempEnemy->Speed, true))
        {
            tempEnemy->Speed.Y = 0;
        }
        tempEnemy->Move();
        tempEnemy->UpdateFrame();
    }
}

void LoadLevel()
{
    map.empty();
    map = LoadMap(CurrentLevel());
    enemies.empty();
    enemies = LoadEnemies(CurrentLevel());
    items.empty();
    items = LoadItems(CurrentLevel());
    dVector tempPos = PositionOfCharacter(CurrentLevel());
    player1 = new Character(tempPos.X, tempPos.Y, 10, 1);
    playerProjectile->Moving = false;
    playerProjectile->Position.X = -500;
    player1->LearnedAbilities.Shoot = savedAbilities.Shoot;
    player1->LearnedAbilities.DoubleJump = savedAbilities.DoubleJump;
    player1->LearnedAbilities.WallJump = savedAbilities.WallJump;
}

void PlayerShoot()
{
    if(!playerProjectile->Moving && !player1->Dying)
    {
        if(player1->LearnedAbilities.Shoot)
        {
            int x = player1->Position.X;
            int y = player1->Position.Y;
            bool movingRight = (player1->MovingRight);
            if(player1->ReadyAbilities.WallJump)
                movingRight = !movingRight;
            if(movingRight)
                x += CHARSIZE;
            else
                x -= PROJECTILESIZE;
            playerProjectile = new Projectile(x, y+4, movingRight);
            player1->Shooting = true;
        }
    }
}

void NewPlayer()
{
    dVector tempPos = PositionOfCharacter(CurrentLevel());
    player1 = new Character(tempPos.X, tempPos.Y, 10, 1);
    playerProjectile->Moving = false;
}

bool CollisionWithTile(Character* _player, dVector _direction, Tile* _tile, bool _enemy)
{
    if(_player->Position.X + _direction.X < _tile->Position.X + _tile->Width && _player->Position.X + _direction.X + _player->Width > _tile->Position.X)
    {
        if(_player->Position.Y + _direction.Y < _tile->Position.Y + _tile->Height && _player->Position.Y + _direction.Y + _player->Height > _tile->Position.Y)
        {
            if(_enemy && _tile->TileType == T_BLOCKER)
            {
                return true;
            }
            else if(_tile->TileType == T_GOAL && !_enemy)
            {
                ++level;
                savedAbilities.DoubleJump = player1->LearnedAbilities.DoubleJump;
                savedAbilities.WallJump = player1->LearnedAbilities.WallJump;
                savedAbilities.Shoot = player1->LearnedAbilities.Shoot;
                LoadLevel();
            }
            else if(_tile->TileType == T_SPIKES && _direction.Y > 0 && !_enemy)
            {
                _player->Dying = true;
                if(_player->Position.Y + _direction.Y + _player->Height > _tile->Position.Y + _tile->Height)
                    return true;
                else
                    return false;
            }
            else if((_tile->TileType == T_BRIDGE && _direction.Y < 0 && !_enemy) || (_player->Position.Y > _tile->Position.Y - _player->Height && _tile->TileType == T_BRIDGE && !_enemy))
            {
                return false;
            }
            else if((_tile->TileType == T_HIDDEN || _tile->TileType == T_BLOCKER) && !_enemy)
                return false;
            return true;
        }
    }
    return false;
}

bool CollisionWithEnemy(Character* _player, dVector _direction, Enemy* _tile)
{
    if(_player->Position.X + _direction.X < _tile->Position.X + _tile->Width && _player->Position.X + _direction.X + _player->Width > _tile->Position.X)
    {
        if(_player->Position.Y + _direction.Y < _tile->Position.Y + _tile->Height && _player->Position.Y + _direction.Y + _player->Height > _tile->Position.Y)
        {
            _player->Dying = true;
            return true;
        }
    }
    return false;
}

bool CollisionWithItem(Character* _player, dVector _direction, Item* _item)
{
    if(_item->Visible)
    {
        if(_player->Position.X + _direction.X < _item->Position.X + _item->Width && _player->Position.X + _direction.X + _player->Width > _item->Position.X)
        {
            if(_player->Position.Y + _direction.Y < _item->Position.Y + _item->Height && _player->Position.Y + _direction.Y + _player->Height > _item->Position.Y)
            {
                return true;
            }
        }
    }
    return false;
}

bool Collision(Character* _player, dVector _direction, bool _enemy)
{
    for(unsigned int i = 0; i < map.size(); i++)
    {
        if(CollisionWithTile(_player, _direction, map[i], _enemy))
        {
            return true;
        }
    }
    if(!_enemy)
    {
        for(unsigned int i = 0; i < enemies.size(); i++)
        {
            if(!enemies[i]->Dead)
            {
                if(CollisionWithEnemy(_player, _direction, enemies[i]))
                {
                    return true;
                }
            }
        }
        for(unsigned int i = 0; i < items.size(); i++)
        {
            if(CollisionWithItem(_player, _direction, items[i]))
            {
                _player->LearnNewAbility();
                items[i]->Visible = false;
                gameState = Message;
                return true;
            }
        }
    }
    return false;
}

void MoveCharacter()
{
    dVector moveDir;
    if(keys.Right)
    {
        player1->MoveRight();
    }
    else if(keys.Left)
    {
        player1->MoveLeft();
    }
    else
        player1->Speed.X = 0;
    if(keys.A)
        PlayerShoot();
    moveDir.X = player1->Speed.X;
    moveDir.Y = 0;
    if(Collision(player1, moveDir))
    {
            if(player1->Speed.Y > CHAR_MAXMOVESPEED)
            {
                player1->Speed.Y = player1->Speed.Y / 2;
                if(player1->Speed.Y < CHAR_MAXMOVESPEED)
                    player1->Speed.Y = CHAR_MAXMOVESPEED;
            }
        player1->Speed.X = 0;
        player1->ReadyAbilities.WallJump = player1->LearnedAbilities.WallJump;
        player1->WallJumpRight = (moveDir.X < 0);
    }
    else
        player1->ReadyAbilities.WallJump = false;
    if(keys.Up)
    {
        keys.Up = false;
        player1->Jump();
    }
    player1->MoveDown();
    moveDir.X = player1->Speed.X;
    moveDir.Y = player1->Speed.Y;
    if(Collision(player1, moveDir))
    {
        if(player1->Speed.Y > 0)
        {
            player1->Grounded = true;
            player1->ReadyAbilities.DoubleJump = player1->LearnedAbilities.DoubleJump;
            player1->ReadyAbilities.WallJump = false;
            player1->Speed.Y = 0;
        }
        else if(player1->Speed.Y < 0)
        {
            moveDir.Y = player1->Speed.Y/2;
            if(Collision(player1, moveDir))
            {
                player1->Speed.Y = 0;
            }
            else
                player1->Speed.Y = moveDir.Y;
        }
        if(Collision(player1, player1->Speed))
            player1->Speed.X = 0;
    }
    player1->Move();
}

SDL_Surface* Initialize()
{
    if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return NULL;
    }
    atexit(SDL_Quit);
    IMG_Init(IMG_INIT_PNG);
    SDL_Surface* screen = SDL_SetVideoMode(800, 600, 24, SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 800x600 video: %s\n", SDL_GetError());
        return NULL;
    }
    gameState = MainMenu;
    return screen;
}

void LoadImages()
{
    tileSet = DLoadImage("TileSet.png");
    characterImage = DLoadImage("Depp.png");
    itemSet = DLoadImage("misc.png");
    enemySheet = DLoadImage("enemies.png");
    backgroundImage = DLoadImage("background.png");
    projectileImage = DLoadImage("Projectile.png");
    wallJumpMsgImage = DLoadImage("WallJumpMsg.bmp");
    doubleJumpMsgImage = DLoadImage("DoubleJumpMsg.bmp");
    gunMsgImage = DLoadImage("GunMsg.bmp");
    mainMenuBGImage = DLoadImage("MainMenuBG.bmp");
    arrowImage = DLoadImage("Arrow.bmp");
    instructionsImage = DLoadImage("Instructions.bmp");
    endGameImage = DLoadImage("EndGame.bmp");
}

bool Events()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            return true;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
                return true;
            else if(event.key.keysym.sym == SDLK_RIGHT)
                keys.Right = true;
            else if(event.key.keysym.sym == SDLK_LEFT)
                keys.Left = true;
            else if(event.key.keysym.sym == SDLK_UP)
                keys.Up = true;
            else if(event.key.keysym.sym == SDLK_DOWN)
                keys.Down = true;
            else if(event.key.keysym.sym == SDLK_a)
                keys.A = true;
            else if(event.key.keysym.sym == SDLK_RETURN)
                keys.Enter = true;
            break;
        case SDL_KEYUP:
            if(event.key.keysym.sym == SDLK_RIGHT)
                keys.Right = false;
            else if(event.key.keysym.sym == SDLK_LEFT)
                keys.Left = false;
            else if(event.key.keysym.sym == SDLK_UP)
                keys.Up = false;
            else if(event.key.keysym.sym == SDLK_DOWN)
                keys.Down = false;
            else if(event.key.keysym.sym == SDLK_a)
                keys.A = false;
            else if(event.key.keysym.sym == SDLK_RETURN)
                keys.Enter = false;
        break;
        }
    }
    return false;
}
