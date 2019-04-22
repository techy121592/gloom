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

#ifndef CONSTS_H_INCLUDED
#define CONSTS_H_INCLUDED

const int TILESIZE = 32;
const int ENEMYSIZE = 26;
const int CHARSIZE = 28;
const int PROJECTILESIZE = 8;
const int MAXLEVEL = 3;
const char T_EMPTY = '0';
const char I_ABILITY = '*';
const char T_FLOOR = '1';
const char T_WALL = '7';
const char T_PILLAR = 'p';
const char T_PLAYER = '2';
const char T_SPIKES = '3';
const char T_GOAL = '4';
const char E_WALKING = '5';
const char E_FLYING = 'z';
const char E_SHOOTING = 'x';
const char T_BRIDGE = '6';
const char T_ROUNDED_TR = 'q';
const char T_ROUNDED_BR = 'w';
const char T_ROUNDED_BL = 'e';
const char T_ROUNDED_TL = 'r';
const char T_ROUNDED_L = 't';
const char T_ROUNDED_R = 'y';
const char T_BLOCKER = 'a';
const char T_INVISIBLE = '8';
const char T_HIDDEN = '9';
const int S_TOP = 1;
const int S_LEFT = 2;
const int S_RIGHT = 3;
const int S_BOTTOM = 4;
const int CHAR_MAXMOVESPEED = 3;

#endif // CONSTS_H_INCLUDED
