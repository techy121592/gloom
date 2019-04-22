#ifndef LOADLEVEL_H_INCLUDED
#define LOADLEVEL_H_INCLUDED

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "Tile.h"
#include "DVector.h"
#include <string>
#include "Enemy.h"
#include "Item.h"

std::vector<Tile*> LoadMap(char** level);
std::vector<Enemy*> LoadEnemies(char** level);
std::vector<Item*> LoadItems(char** level);
dVector PositionOfCharacter(char** level);

#endif // LOADLEVEL_H_INCLUDED
