#ifndef IMAGEHANDLER_H_INCLUDED
#define IMAGEHANDLER_H_INCLUDED

#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include "GameObject.h"
#include "Consts.h"
#include "Tile.h"
#include "Character.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Item.h"

SDL_Surface* DLoadImage(std::string _filename);
void DrawTile(Tile* _tile, SDL_Surface* _tileSet, SDL_Surface* _screen, dVector _offSet);
void DrawCharacter(Character* _char, SDL_Surface* _image, SDL_Surface* _screen, dVector _offSet);
void DrawEnemy(Enemy* _enemy, SDL_Surface* _enemySheet, SDL_Surface* _screen, dVector _offSet);
void DrawMap(std::vector<Tile*> _map, SDL_Surface* _tileSet, SDL_Surface* _screen, dVector _offSet);
void DrawItems(std::vector<Item*> _items, SDL_Surface* _itemSet, SDL_Surface* _screen, dVector _offSet);
void DrawItem(Item* _item, SDL_Surface* _itemSet, SDL_Surface* _screen, dVector _offSet);
void DrawEnemies(std::vector<Enemy*> _map, SDL_Surface* _enemySheet, SDL_Surface* _screen, dVector _offSet);
void DrawImage(int _x, int _y, int _width, int _height, SDL_Surface* _image, SDL_Surface* _screen, int _frameX = 0, int _frameY = 0);
void DrawProjectile(Projectile* _projectile, SDL_Surface* _sheet, SDL_Surface* _screen, dVector _offSet);

#endif // IMAGEHANDLER_H_INCLUDED
