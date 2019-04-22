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

#include "LoadLevel.h"
#include "Character.h"
#include "Enemy.h"
#include <iostream>
#include <fstream>

using namespace std;

/*char** LoadFromFile(char* _fileName)
{
    ifstream tempFile;
    tempFile.open(_fileName);
    int width = 0;
    int height = 0;
    char* input;
    tempFile.getline(input, 20);
    char* tempInput;
    tempInput = strtok(input, ",");
    width = atoi(tempInput);
    tempInput = strtok(NULL, ",");
    height = atoi(tempInput);

    char* tempLevel[] = new char*[height];
    for(int y = 0; y < height; y++)
    {
        tempLevel[y] = new char[width+1];
        tempFile.getline(tempLevel[y], width);
    }
    return tempLevel;
}*/

std::vector<Tile*> LoadMap(char** _level)
{
    std::vector<Tile*> map;
    for (int y = 0; _level[y]; y++)
    {
        for(int x = 0; _level[y][x]; x++)
        {
            if(_level[y][x] == T_SPIKES)
            {
                Tile* tempTile = new Tile(x, y, _level[y][x], TILESIZE, TILESIZE - 8);
                map.push_back(tempTile);
            }
            else if(_level[y][x] == T_BRIDGE)
            {
                Tile* tempTile = new Tile(x, y, _level[y][x], TILESIZE, TILESIZE - 22);
                map.push_back(tempTile);
            }
            else if(_level[y][x] != T_EMPTY && _level[y][x] != T_PLAYER && _level[y][x] != E_WALKING && _level[y][x] != E_FLYING && _level[y][x] != I_ABILITY)
            {
                Tile* tempTile = new Tile(x, y, _level[y][x]);
                map.push_back(tempTile);
            }

        }
    }
    return map;
}

std::vector<Enemy*> LoadEnemies(char** _level)
{
    std::vector<Enemy*> enemies;
    for (int y = 0; _level[y]; y++)
    {
        for(int x = 0; _level[y][x]; x++)
        {
            if(_level[y][x] == E_WALKING)
            {
                Enemy* tempEnemy = new Enemy(x, y, 10, E_WALKING);
                enemies.push_back(tempEnemy);
            }
            else if(_level[y][x] == E_FLYING)
            {
                Enemy* tempEnemy = new Enemy(x, y, 10, E_FLYING, false);
                enemies.push_back(tempEnemy);
            }
        }
    }
    return enemies;
}

std::vector<Item*> LoadItems(char** _level)
{
    std::vector<Item*> items;
    for (int y = 0; _level[y]; y++)
    {
        for(int x = 0; _level[y][x]; x++)
        {
            if(_level[y][x] == I_ABILITY)
            {
                Item* tempItem = new Item(x, y, I_ABILITY, 16, 16);
                items.push_back(tempItem);
            }
        }
    }
    return items;
}

dVector PositionOfCharacter(char** _level)
{
    dVector pos;
    for (int y = 0; _level[y]; y++)
    {
        for(int x = 0; _level[y][x]; x++)
        {
            if(_level[y][x] == T_PLAYER)
            {
                pos.Y = y;
                pos.X = x;
            }
        }
    }
    return pos;
}
