#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED
#include "GameObject.h"

class Item: public GameObject
{
    public:
    int ItemType;
    bool Visible;

    Item(int _x, int _y, int _itemType)
    :GameObject("item")
    {
        Position.X = _x * TILESIZE;
        Position.Y = _y * TILESIZE;
        ItemType = _itemType;
        Visible = true;
    }

    Item(int _x, int _y, int _itemType, int _width, int _height)
    :GameObject("item")
    {
        Width = _width;
        Height = _height;
        Position.X = _x * TILESIZE;
        Position.Y = _y * TILESIZE;
        ItemType = _itemType;
        Position.Y += (TILESIZE - Height)/2;
        Position.X += (TILESIZE - Width)/2;
        Visible = true;
    }
};

#endif // ITEM_H_INCLUDED
