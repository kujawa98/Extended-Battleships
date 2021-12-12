//
// Created by Kacper on 22.11.2021.
//

#ifndef BSHIPS_MAP_H
#define BSHIPS_MAP_H

class BattleshipGame;

#include "utils.h"

class Map {
public:
    char **map;
    FieldState **states;
    Visibility **aVisibilities;
    Visibility **bVisibilities;
    int height;
    int width;

    Map(int height, int width);

    Map();

    virtual ~Map();

    void allocateMap();

    void basicPrint(BattleshipGame *game) const;

    void extendedPrint(BattleshipGame *game) const;
};


#endif //BSHIPS_MAP_H
