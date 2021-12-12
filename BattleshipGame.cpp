//
// Created by Kacper on 22.11.2021.
//
#include <iostream>
#include "utils.h"
#include "BattleshipGame.h"

BattleshipGame::BattleshipGame() {
    playerA = new Player(PLAYER_A);
    playerB = new Player(PLAYER_B);
    nextPlayer = playerA;
    playerA->initPosition(A_START_Y, A_START_X, A_END_Y, A_END_X);
    playerB->initPosition(B_START_Y, B_START_X, B_END_Y, B_END_X);
    map = new Map();
}

BattleshipGame::~BattleshipGame() {
    delete playerA;
    delete playerB;
    delete map;
}

Groups BattleshipGame::checkVictory() const {
    if (playerA->remainParts == 0) {
        std::cout << "B won";
        exit(EXIT_CODE);
    } else if (playerB->remainParts == 0) {
        std::cout << "A won";
        exit(EXIT_CODE);
    } else {
        return EMPTY;
    }
}
