//
// Created by Kacper on 22.11.2021.
//


#ifndef BSHIPS_BATTLESHIPGAME_H
#define BSHIPS_BATTLESHIPGAME_H

#include "Player.h"

class BattleshipGame {
public:
    Player *playerA;
    Player *playerB;
    Player *nextPlayer;
    Map *map;

    BattleshipGame();

    Groups checkVictory() const;

    virtual ~BattleshipGame();
};


#endif //BSHIPS_BATTLESHIPGAME_H
