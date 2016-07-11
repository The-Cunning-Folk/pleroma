#ifndef TILE_H
#define TILE_H

#include<string>

namespace BQ{
class Tile
{
public:
    Tile();
    int index;
    int x;
    int y;
    int rot;
    bool flipX;
};
}

#endif // TILE_H
