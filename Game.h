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

/*-------------------------------------------------------------+
 |                     Naming convention                       |
 | local variable       =   first letter lower case            |
 | parameter variable   =   underscore variable followed by    |
 |                              lower case letter              |
 | global variable      =   first letter capital               |
 | public variable      =   first letter capital               |
 | function             =   first letter capital               |
 |                                                             |
 | Note - All naming schemes are in camelback format           |
 +-------------------------------------------------------------*/
/*-------------------------------------------------------------+
 |                        Game Ideas                           |
 | Music starts of sounding like a creepy, slow, and sounds    |
 |      like a broken music box sounding and ends with a fixed |
 |      happy sounding music box.                              |
 | The whole atmosphere is a gloomy strange feeling(empty      |
 |      ferris wheel turning in background etc.)               |
 +-------------------------------------------------------------*/
#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "ImageHandler.h"
#include "LoadLevel.h"
#include "Key.h"
#include "Character.h"
#include "Timer.h"
#include <SDL_Mixer.h>
#include "Enemy.h"
#include "Projectile.h"
#include "Item.h"

enum GameStateEnum
{
    MainMenu,
    Game,
    Pause,
    Message
};

char* level2[] = {
"7777777777777777777777777",
"7000000000700000000000007",
"7000000000700000000000007",
"7200000000700000006100047",
"7100500a0*700000000711117",
"771111y0t1700000006700007",
"7000000000700000500700007",
"7000000000766666666700007",
"7000000000705000000700007",
"7000000000766666666700007",
"7000000000700050000700007",
"7000000000766666666700007",
"7000000000750000000700007",
"7000a50000766666666700007",
"70t3311111700005000700007",
"7000000000766666666700007",
"7000000000700000005700007",
"7000000000766666666700007",
"7z00000000750000000700007",
"7000000000e66666600700007",
"7000000000000000000700007",
"7111111111111111111711117",
NULL};

char* level1[] = {
"7777777777777777777777777777",
"7000000000000000000000000007",
"700ry00000000000000000000007",
"766700000000000000000ry00007",
"7207000000000000000007000007",
"71176611111111111y0007000007",
"7007000000000000000007000007",
"7007y00000000000000007000007",
"7007*00000000000000r1w000007",
"7007111133133133133700004007",
"700e777777777777777w000t1y07",
"7000000000000000000000000007",
"7111111111111111111111111117",
NULL};

char* level3[] = {
"77777777777777777777777777777777777777777777777777777777777777",
"70000000000000000000000000000000000000000000000000000000000007",
"70000000000000000000000000000000000000000000000000000000000047",
"70000000000000000000000000000000000000000000000000000000007777",
"70000000000000000000000000000000000000000000000000000000007007",
"70000000000000000000000000000000000000000000000000000007777007",
"70000000000000000000000000000000000000000000a000z0000a00000007",
"70000000000000000000000000000000000000000000000000000000000007",
"70000000000000000000000000000000000000000000a050aa050a00000007",
"70000000000000000000000000000000000000000000077777777000000007",
"70000000000000000000000000000000000000000000070000000000000007",
"70000000000000000000000000000000000000000000070000000000000007",
"70000000000000000000000000000000000000000000070000000000000007",
"70000000000000000000000000000000000000000000070000000000000007",
"70000000000000000000000000000000000000000000070000000000000007",
"70000000000000000000000000000000000000000000070000000000000007",
"70000000000000000000000000000000000000000000070000000000000007",
"70000000000000000000000000000000000000000007770000000000000007",
"70000000000000000000000000000000000000000000070000000000000007",
"70000000000000000000000000000000000000000000070000000000000007",
"70000000000000000000000000000000000000000000070000000000000007",
"700000000000000000000000000000000000a5000000070000000000000007",
"70000000000000000000000000000000000007777777770000000000000007",
"70000000000000000000000000000000000000000000000000000000000007",
"7000000500000a000000000000000az00a7700000000000000000000000007",
"77667777777770000000000000000000000000000000000000000000000007",
"77000000000070000000000000a00za7700000000000000000000000000000",
"77000000000070000000000000000000000000000000000000000000000007",
"77000000000070000000000a0z0a7700000000000000000000000000000007",
"77000000000070000000000000000000000000000000000000000000000007",
"77200000000070000000000007700000000000000000000000000000000007",
"77110000000070000000000000000000000000000000000000000000000007",
"7000000000007000a000005a00000000000000000000000000000000000007",
"70000000000070007777777700000000000000000000000000000000000007",
"70000000000070000000000000000000000000000000000000000000000007",
"70000000000070000000000000000000000000000000000000000000000007",
"7000000000007000*000000000000000000000000000000000000000000007",
"73333333333373337333333333333333333333333333333333333333333333",
NULL};

Character* player1;
Keys keys;
AbilityList savedAbilities;
std::vector<Tile*> map;
std::vector<Item*> items;
std::vector<Enemy*> enemies;
SDL_Surface* screen;
Projectile* playerProjectile;
int level = 1;
GameStateEnum gameState;

SDL_Surface* tileSet;
SDL_Surface* characterImage;
SDL_Surface* itemSet;
SDL_Surface* enemySheet;
SDL_Surface* backgroundImage;
SDL_Surface* projectileImage;
SDL_Surface* wallJumpMsgImage;
SDL_Surface* doubleJumpMsgImage;
SDL_Surface* gunMsgImage;
SDL_Surface* mainMenuBGImage;
SDL_Surface* arrowImage;
SDL_Surface* instructionsImage;
SDL_Surface* endGameImage;

SDL_Surface* Initialize();
bool Events();
void ResetGame();
void MoveCharacter();
bool Collision(Character* _player, dVector _direction, bool _enemy = false);
bool CollisionWithTile(Character* _player, dVector _direction, Tile* _tile, bool _enemy = false);
bool CollisionWithEnemy(Character* _player, dVector _direction, Enemy* _tile);
bool CollisionWithItem(Character* _player, dVector _direction, Item* _item);
void NewPlayer();
void LoadLevel();
void MoveEnemies();
dVector ScrollScreen();
void PlayerShoot();
void MoveProjectile(Projectile* _projectile, std::vector<Tile*> _map, std::vector<Enemy*> _enemies);
void LoadImages();

char** CurrentLevel();
int CurrentLevelHeight();

#endif // GAME_H_INCLUDED
