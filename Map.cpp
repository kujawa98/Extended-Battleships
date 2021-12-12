//
// Created by Kacper on 22.11.2021.
//
#include <iostream>
#include "Map.h"
#include "BattleshipGame.h"

Map::Map(int height, int width) {
    if (height < MIN_MAP_HEIGHT && width < MIN_MAP_WIDTH) {
        std::cout << "AT LEAST 11 ON 10" << std::endl;
        height = DEFAULT_HEIGHT;
        width = DEFAULT_WIDTH;
    }
    this->height = height;
    this->width = width;
    allocateMap();
}

void Map::basicPrint(BattleshipGame *game) const {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (map[i][j] != EMPTY_FIELD_SYMBOL && map[i][j] != REEF_FIELD_SYMBOL && map[i][j] != HIT_FIELD_SYMBOL) {
                std::cout << SEGMENT_SYMBOL;
            } else {
                std::cout << map[i][j];
            }
        }
        std::cout << std::endl;
    }
    std::cout << "PARTS REMAINING:: A : " << game->playerA->remainParts << " B : " << game->playerB->remainParts
              << std::endl;
}

Map::Map() {
    this->height = DEFAULT_HEIGHT;
    this->width = DEFAULT_WIDTH;
    map = nullptr;
    states = nullptr;
    aVisibilities = nullptr;
    bVisibilities = nullptr;
    allocateMap();
}

void Map::allocateMap() {
    map = new char *[height];
    states = new FieldState *[height];
    aVisibilities = new Visibility *[height];
    bVisibilities = new Visibility *[height];
    for (int i = 0; i < height; i++) {
        map[i] = new char[width];
        states[i] = new FieldState[width];
        aVisibilities[i] = new Visibility[width];
        bVisibilities[i] = new Visibility[width];
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            map[i][j] = ' ';
            states[i][j] = EMPTY_FIELD;
            aVisibilities[i][j] = UNKNOWN;
            bVisibilities[i][j] = UNKNOWN;
        }
    }
}

void Map::extendedPrint(BattleshipGame *game) const {
    std::cout << "  ";
    int hw = 0;
    int tmpW = width;
    int tmpH = height;
    int vw = 0;
    while (tmpW / 10 > 0) {
        hw++;
        tmpW /= 10;
    }
    while (tmpH / 10 > 0) {
        vw++;
        tmpH /= 10;
    }
    int mns;
    int pbs;
    for (int i = hw; i >= 1; i--) {
        int currentPower = (int) pow(10, i);
        mns = width / currentPower;
        pbs = (width % currentPower);
        if (width > currentPower) {
            for (int k = 0; k < mns; k++) {
                for (int j = 0; j < currentPower; j++) {
                    std::cout << k % currentPower;
                }
            }
        }
        for (int k = 1; k <= pbs; k++) {
            std::cout << mns % currentPower;
        }
        std::cout << std::endl;
        std::cout << "  ";
    }
    for (int i = 0; i < width / 10; i++) {
        for (int j = 0; j < 10; j++) {
            std::cout << j;
        }
    }
    for (int i = 0; i < pbs; i++) {
        std::cout << i;
    }
    std::cout << std::endl;
    for (int i = 0; i < height; i++) {
        if (i < 10) {
            std::cout << "0" << i;
        } else {
            std::cout << i;
        }
        for (int j = 0; j < width; j++) {
            std::cout << map[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << "PARTS REMAINING:: A : " << game->playerA->remainParts << " B : " << game->playerB->remainParts
              << std::endl;
}

Map::~Map() {
    for (int i = 0; i < height; i++) {
        delete[] map[i];
        delete[] states[i];
        delete[] aVisibilities[i];
        delete[] bVisibilities[i];
    }
    delete[] map;
    delete[] states;
    delete[] aVisibilities;
    delete[] bVisibilities;
}

