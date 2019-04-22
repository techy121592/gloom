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

#include "ImageHandler.h"

SDL_Surface* DLoadImage(std::string _filename)
{
    SDL_Surface* loadedImage = IMG_Load(_filename.c_str());
    SDL_Surface* optimizedImage = NULL;

    if (!loadedImage)
    {
        printf("Unable to load image: %s\n", SDL_GetError());
        return NULL;
    }
    else
    {
        optimizedImage = SDL_DisplayFormat(loadedImage);
        SDL_FreeSurface(loadedImage);
        loadedImage = NULL;
        Uint32 colorkey = SDL_MapRGB(optimizedImage->format, 0xFF, 0, 0xFF);
        SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorkey);
        return optimizedImage;
    }
}

void DrawCharacter(Character* _char, SDL_Surface* _image, SDL_Surface* _screen, dVector _offSet)
{
    int x = _char->Position.X - _offSet.X;
    if(_offSet.X > 0)
        x += _screen->w/2;
    int y = _char->Position.Y - _offSet.Y;
    if(_offSet.Y > 0)
        y += _screen->h/2;
    DrawImage(x, y, _char->Width, _char->Height, _image, _screen , _char->Frame);
}

void DrawProjectile(Projectile* _projectile, SDL_Surface* _sheet, SDL_Surface* _screen, dVector _offSet)
{
    if(_projectile->Moving)
    {
        int x = _projectile->Position.X - _offSet.X;
        if(_offSet.X > 0)
            x += _screen->w/2;
        int y = _projectile->Position.Y - _offSet.Y;
        if(_offSet.Y > 0)
            y += _screen->h/2;
        DrawImage(x, y, _projectile->Width, _projectile->Height, _sheet, _screen);
    }
}

void DrawImage(int _x, int _y, int _width, int _height, SDL_Surface* _image, SDL_Surface* _screen, int _frameX, int _yOffset)
{
    SDL_Rect sourceRect;
    sourceRect.h = _height;
    sourceRect.w = _width;
    sourceRect.y = _yOffset;
    sourceRect.x = _width * _frameX;
    SDL_Rect destRect;
    destRect.h = _height;
    destRect.w = _width;
    destRect.x = _x;
    destRect.y = _y;
    SDL_BlitSurface(_image, &sourceRect, _screen, &destRect);
}

void DrawItems(std::vector<Item*> _items, SDL_Surface* _itemSet, SDL_Surface* _screen, dVector _offSet)
{
    for(unsigned int i = 0; i < _items.size(); i++)
        DrawItem(_items[i], _itemSet, _screen, _offSet);
}

void DrawItem(Item* _item, SDL_Surface* _itemSet, SDL_Surface* _screen, dVector _offSet)
{
    if(_item->Visible)
    {
        int x = _item->Position.X - _offSet.X;
        if(_offSet.X > 0)
            x += _screen->w/2;
        int y = _item->Position.Y - _offSet.Y;
        if(_offSet.Y > 0)
            y += _screen->h/2;
        int height = _item->Height;
        int width = _item->Width;
        int frame = 0;
        int yOffset = 0;
        if(_item->ItemType == I_ABILITY)
        {
            frame = 0;
        }
        DrawImage(x, y, width, height, _itemSet, _screen, frame, yOffset);
    }
}

void DrawTile(Tile* _tile, SDL_Surface* _tileSet, SDL_Surface* _screen, dVector _offSet)
{
    int x = _tile->Position.X - _offSet.X;
    if(_offSet.X > 0)
        x += _screen->w/2;
    int y = _tile->Position.Y - _offSet.Y;
    if(_offSet.Y > 0)
        y += _screen->h/2;
    int height = _tile->Height;
    int width = _tile->Width;
    int frame = 0;
    int yOffset = 0;
    if(_tile->TileType == T_WALL || _tile->TileType == T_HIDDEN)
        frame = 10;
    else if(_tile->TileType == T_FLOOR || _tile->TileType == I_ABILITY)
    {
        frame = 0;
    }
    else if(_tile->TileType == T_PILLAR)
    {
        frame = 12;
    }
    else if(_tile->TileType == T_SPIKES)
    {
        frame = 1;
        yOffset = 8;
    }
    else if(_tile->TileType == T_GOAL)
        frame = 2;
    else if(_tile->TileType == T_BRIDGE)
    {
        frame = 3;
        yOffset = 22;
    }
    else if(_tile->TileType == T_ROUNDED_TR)
        frame = 4;
    else if(_tile->TileType == T_ROUNDED_BR)
        frame = 5;
    else if(_tile->TileType == T_ROUNDED_BL)
        frame = 6;
    else if(_tile->TileType == T_ROUNDED_TL)
        frame = 7;
    else if(_tile->TileType == T_ROUNDED_L)
        frame = 8;
    else if(_tile->TileType == T_ROUNDED_R)
        frame = 9;
    else if(_tile->TileType == T_INVISIBLE || _tile->TileType == T_BLOCKER)
        return;
    DrawImage(x, y, width, height, _tileSet, _screen, frame, yOffset);
}

void DrawEnemy(Enemy* _enemy, SDL_Surface* _enemySheet, SDL_Surface* _screen, dVector _offSet)
{
    if(!_enemy->Dead)
    {
        int yOffSet = ENEMYSIZE - _enemy->Height;
        if(_enemy->EnemyType == E_FLYING)
        {
            yOffSet += ENEMYSIZE;
        }
        int x = _enemy->Position.X - _offSet.X;
        if(_offSet.X > 0)
            x += _screen->w/2;
        int y = _enemy->Position.Y - _offSet.Y;
        if(_offSet.Y > 0)
            y += _screen->h/2;
        DrawImage(x, y, _enemy->Width, _enemy->Height, _enemySheet, _screen, _enemy->Frame, yOffSet);
    }
}

void DrawMap(std::vector<Tile*> _map, SDL_Surface* _tileSet, SDL_Surface* _screen, dVector _offSet)
{
    for(unsigned int i = 0; i < _map.size(); i++)
        DrawTile(_map[i], _tileSet, _screen, _offSet);
}

void DrawEnemies(std::vector<Enemy*> _enemies, SDL_Surface* _enemySheet, SDL_Surface* _screen, dVector _offSet)
{
    for(unsigned int i = 0; i < _enemies.size(); i++)
        DrawEnemy(_enemies[i], _enemySheet, _screen, _offSet);
}
