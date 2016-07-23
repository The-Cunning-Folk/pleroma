#ifndef TILE_H
#define TILE_H

#include<string>
#include<rapidjson/document.h>

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

    bool parse(const rapidjson::Value &);
};
}

#endif // TILE_H
