//
// Created by Kacper on 24.11.2021.
//

#include "Ship.h"

#include "BattleshipGame.h"

#include <iostream>

Ship::Ship() {
    isSet = false;
    availableMoves = DEFAULT_MOVES_NUMBER;
    segments = nullptr;
    canon = nullptr;
    radar = nullptr;
    engine = nullptr;
}

void Ship::findShootShip(Map *map, Ship *ships, int *remainParts, int len, int shipsCount, int y, int x) {
    for (int i = 0; i < shipsCount; i++) {
        for (int j = 0; j < len; j++) {
            if (ships[i].segments[j].y == y &&
                ships[i].segments[j].x == x) {
                ships[i].segments[j].symbol = HIT_FIELD_SYMBOL;
                ships[i].segments[j].isDestroyed = true;
                map->map[y][x] = HIT_FIELD_SYMBOL;
                (*remainParts)--;
            }
        }
    }
}

void Ship::shoot(BattleshipGame *game, char *commandToPrint, int y, int x) {
    checkShootPossibility(y, x, commandToPrint, game->map);
    checkGameSet(game->playerA, commandToPrint);
    checkGameSet(game->playerB, commandToPrint);
    if (game->map->states[y][x] == PLAYER_A_FIELD) {
        findShootShips(game->map, game->playerA, y, x);
    } else if (game->map->states[y][x] == PLAYER_B_FIELD) {
        findShootShips(game->map, game->playerB, y, x);
    }
    game->checkVictory();
}


void Ship::move(Map *map, MoveDirection moveDirection, char *commandToPrint) {
    checkMovePossibility(commandToPrint);
    switch (moveDirection) {
        case FORWARD:
            forward(map, commandToPrint);
            break;
        case LEFT:
            switch (direction) {
                case N:
                    nl(map, commandToPrint);
                    direction = W;
                    break;
                case S:
                    sl(map, commandToPrint);
                    direction = E;
                    break;
                case E:
                    el(map, commandToPrint);
                    direction = N;
                    break;
                case W:
                    wl(map, commandToPrint);
                    direction = S;
                    break;
            }
            break;
        case RIGHT:
            switch (direction) {
                case N:
                    nr(map, commandToPrint);
                    direction = E;
                    break;
                case S:
                    sr(map, commandToPrint);
                    direction = W;
                    break;
                case E:
                    er(map, commandToPrint);
                    direction = S;
                    break;
                case W:
                    wr(map, commandToPrint);
                    direction = N;
                    break;
            }
            break;
    }
    checkSurrounding(map, commandToPrint);
}


void Ship::nr(Map *map, char *commandToPrint) const {
    for (int i = 0; i < lenght; i++) {
        moveWithDirChange(-(i + 1), (lenght - 1 - i), i, map, commandToPrint);
    }
}

void Ship::nl(Map *map, char *commandToPrint) const {
    for (int i = 0; i < lenght; i++) {
        moveWithDirChange(-(i + 1), -(lenght - 1 - i), i, map, commandToPrint);
    }
}

void Ship::sr(Map *map, char *commandToPrint) const {
    for (int i = 0; i < lenght; i++) {
        moveWithDirChange((i + 1), -(lenght - 1 - i), i, map, commandToPrint);
    }
}

void Ship::sl(Map *map, char *commandToPrint) const {
    for (int i = 0; i < lenght; i++) {
        moveWithDirChange((i + 1), (lenght - 1 - i), i, map, commandToPrint);
    }
}

void Ship::er(Map *map, char *commandToPrint) const {
    for (int i = 0; i < lenght; i++) {
        moveWithDirChange((lenght - 1 - i), (i + 1), i, map, commandToPrint);
    }
}

void Ship::el(Map *map, char *commandToPrint) const {
    for (int i = 0; i < lenght; i++) {
        moveWithDirChange(-(lenght - 1 - i), (i + 1), i, map, commandToPrint);
    }
}

void Ship::wl(Map *map, char *commandToPrint) const {
    for (int i = 0; i < lenght; i++) {
        moveWithDirChange((lenght - 1 - i), -(i + 1), i, map, commandToPrint);
    }
}

void Ship::wr(Map *map, char *commandToPrint) const {
    for (int i = 0; i < lenght; i++) {
        moveWithDirChange(-(lenght - 1 - i), -(i + 1), i, map, commandToPrint);
    }
}

void Ship::moveStraight(int ver, int hor, Map *map, char *commandToPrint) const {
    for (int i = 0; i < lenght; i++) {
        moveWithDirChange(ver, hor, i, map, commandToPrint);
    }
}

void Ship::moveWithDirChange(int yOffset, int xOffset, int index, Map *map, char *commandToPrint) const {
    int y = segments[index].y;
    int x = segments[index].x;
    int newX = x + xOffset;
    int newY = y + yOffset;
    if (newY < 0 || newY >= map->height || newX < 0 || newX >= map->width) {
        std::cout << "INVALID OPERATION \"" << commandToPrint
                  << "\": SHIP WENT FROM BOARD"
                  << std::endl;
        exit(EXIT_CODE);
    }
    map->states[newY][newX] = map->states[y][x];
    map->states[y][x] = EMPTY_FIELD;
    map->map[y][x] = ' ';
    map->map[newY][newX] = segments[index].symbol;
    segments[index].y = newY;
    segments[index].x = newX;
}

void Ship::forward(Map *map, char *commandToPrint) const {
    switch (direction) {
        case N:
            moveStraight(-1, 0, map, commandToPrint);
            break;
        case S:
            moveStraight(1, 0, map, commandToPrint);
            break;
        case E:
            moveStraight(0, 1, map, commandToPrint);
            break;
        case W:
            moveStraight(0, -1, map, commandToPrint);
            break;
    }
}

void Ship::placeOnMap(Map *map, char *commandToPrint) const {
    for (int i = 0; i < lenght; i++) {
        int y = segments[i].y;
        int x = segments[i].x;
        checkPlacingPossibility(map, y, x, commandToPrint);
        map->map[y][x] = segments[i].symbol;
    }
    checkSurrounding(map, commandToPrint);
}

void Ship::reset() {
    availableMoves = 3;
    availableShoots = lenght;
}

void Ship::setVisibility(Map *map, Player *player) const {
    int y = radar->y;
    int x = radar->x;
    for (int i = y - lenght; i <= y + lenght; i++) {
        for (int j = x - lenght; j <= x + lenght; j++) {
            if (i >= 0 && i < map->height && j >= 0 && j < map->width) {
                if (checkIfPointIsInRange(y, x, i, j, lenght, map)) {
                    switch (player->playerGroup) {
                        case PLAYER_A:
                            map->aVisibilities[i][j] = VISIBLE_BY_A;
                            break;
                        case PLAYER_B:
                            map->bVisibilities[i][j] = VISIBLE_BY_B;
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }
}

bool Ship::checkIfPointIsInRange(int y, int x, int yp, int xp, int radius, Map *map) {
    if (yp >= 0 && yp < map->height && xp >= 0 && xp < map->width) {
        int y_sub = abs(y - yp);
        int x_sub = abs(x - xp);
        double underSquare = pow(y_sub, 2) + pow(x_sub, 2);
        if (underSquare <= pow(radius, 2)) {
            return true;
        }
        return false;
    }
    return false;
}

void Ship::setSegments(const int *outerSegments, Map *map) const {
    for (int i = 0; i < lenght; i++) {
        if (outerSegments[i] == 1) {
            this->segments[i].isDestroyed = false;
        } else {
            this->segments[i].isDestroyed = true;
            this->segments[i].symbol = 'x';
            map->map[segments[i].y][segments[i].x] = segments[i].symbol;
        }
    }
}

void Ship::resolveSegments() {
    int i, j;
    switch (direction) {
        case N:
            i = 1;
            j = 0;
            break;
        case S:
            i = -1;
            j = 0;
            break;
        case W:
            i = 0;
            j = 1;
            break;
        case E:
            i = 0;
            j = -1;
            break;
        default:
            break;
    }
    for (int k = 0; k < lenght; k++) {
        segments[k].y = headY + k * i;
        segments[k].x = headX + k * j;
    }
    radar = &segments[0];
    canon = &segments[1];
    engine = &segments[lenght - 1];
}

void Ship::checkFieldsNS(Map *map, char *commandToPrint) const {
    for (int k = 1; k < lenght - 1; k++) {
        if (segments[k].x - 1 >= 0) {
            if (map->map[segments[k].y][segments[k].x - 1] != '#' &&
                map->map[segments[k].y][segments[k].x - 1] != ' ') {
                std::cout << "INVALID OPERATION \"" << commandToPrint
                          << "\": PLACING SHIP TOO CLOSE TO OTHER SHIP"
                          << std::endl;
                exit(EXIT_CODE);
            }
        }
        if (segments[k].x + 1 < map->width) {
            if (map->map[segments[k].y][segments[k].x + 1] != '#' &&
                map->map[segments[k].y][segments[k].x + 1] != ' ') {
                std::cout << "INVALID OPERATION \"" << commandToPrint
                          << "\": PLACING SHIP TOO CLOSE TO OTHER SHIP"
                          << std::endl;
                exit(EXIT_CODE);
            }
        }
    }
}

void Ship::checkSurrounding(Map *map, char *commandToPrint) const {
    switch (direction) {
        case N:
            if (radar->y - 1 >= 0) {
                if (map->map[radar->y - 1][radar->x] != '#' && map->map[radar->y - 1][radar->x] != ' ') {
                    std::cout << "INVALID OPERATION \"" << commandToPrint
                              << "\": PLACING SHIP TOO CLOSE TO OTHER SHIP"
                              << std::endl;
                    exit(EXIT_CODE);
                }
            }
            checkFieldsNS(map, commandToPrint);
            if (engine->y + 1 < map->height) {
                if (map->map[engine->y + 1][engine->x] != '#' && map->map[engine->y + 1][engine->x] != ' ') {
                    std::cout << "INVALID OPERATION \"" << commandToPrint
                              << "\": PLACING SHIP TOO CLOSE TO OTHER SHIP"
                              << std::endl;
                    exit(EXIT_CODE);
                }
            }
            break;
        case S:
            if (radar->y + 1 < map->height) {
                if (map->map[radar->y + 1][radar->x] != '#' && map->map[radar->y + 1][radar->x] != ' ') {
                    std::cout << "INVALID OPERATION \"" << commandToPrint
                              << "\": PLACING SHIP TOO CLOSE TO OTHER SHIP"
                              << std::endl;
                    exit(EXIT_CODE);
                }
            }
            checkFieldsNS(map, commandToPrint);
            if (engine->y - 1 >= 0) {
                if (map->map[engine->y - 1][engine->x] != '#' && map->map[engine->y - 1][engine->x] != ' ') {
                    std::cout << "INVALID OPERATION \"" << commandToPrint
                              << "\": PLACING SHIP TOO CLOSE TO OTHER SHIP"
                              << std::endl;
                    exit(EXIT_CODE);
                }
            }
            break;
        case W:
            if (radar->x - 1 >= 0) {
                if (map->map[radar->y][radar->x - 1] != '#' && map->map[radar->y][radar->x - 1] != ' ') {
                    std::cout << "INVALID OPERATION \"" << commandToPrint
                              << "\": PLACING SHIP TOO CLOSE TO OTHER SHIP"
                              << std::endl;
                    exit(EXIT_CODE);
                }
            }
            checkFieldsWE(map, commandToPrint);
            if (engine->x + 1 < map->width) {
                if (map->map[engine->y][engine->x + 1] != '#' && map->map[engine->y][engine->x + 1] != ' ') {
                    std::cout << "INVALID OPERATION \"" << commandToPrint
                              << "\": PLACING SHIP TOO CLOSE TO OTHER SHIP"
                              << std::endl;
                    exit(EXIT_CODE);
                }
            }
            break;
        case E:
            if (radar->x + 1 < map->width) {
                if (map->map[radar->y][radar->x + 1] != '#' && map->map[radar->y][radar->x + 1] != ' ') {
                    std::cout << "INVALID OPERATION \"" << commandToPrint
                              << "\": PLACING SHIP TOO CLOSE TO OTHER SHIP"
                              << std::endl;
                    exit(EXIT_CODE);
                }
            }
            checkFieldsWE(map, commandToPrint);
            if (engine->x - 1 >= 0) {
                if (map->map[engine->y][engine->x - 1] != '#' && map->map[engine->y][engine->x - 1] != ' ') {
                    std::cout << "INVALID OPERATION \"" << commandToPrint
                              << "\": PLACING SHIP TOO CLOSE TO OTHER SHIP"
                              << std::endl;
                    exit(EXIT_CODE);
                }
            }
            break;
    }

}

void Ship::checkFieldsWE(Map *map, char *commandToPrint) const {
    for (int k = 1; k < lenght - 1; k++) {
        if (segments[k].y - 1 >= 0) {
            if (map->map[segments[k].y - 1][segments[k].x] != '#' &&
                map->map[segments[k].y - 1][segments[k].x] != ' ') {
                std::cout << "INVALID OPERATION \"" << commandToPrint
                          << "\": PLACING SHIP TOO CLOSE TO OTHER SHIP"
                          << std::endl;
                exit(EXIT_CODE);
            }
        }
        if (segments[k].y + 1 < map->height) {
            if (map->map[segments[k].y + 1][segments[k].x] != '#' &&
                map->map[segments[k].y + 1][segments[k].x] != ' ') {
                std::cout << "INVALID OPERATION \"" << commandToPrint
                          << "\": PLACING SHIP TOO CLOSE TO OTHER SHIP"
                          << std::endl;
                exit(EXIT_CODE);
            }
        }
    }
}

void Ship::findShootShips(Map *map, Player *player, int y, int x) {
    findShootShip(map, player->carriers, &(player->remainParts), CARRIER_LENGTH,
                  player->carriersCount,
                  y, x);
    findShootShip(map, player->battleships, &(player->remainParts), BATTLESHIP_LENGTH,
                  player->battleshipsCount, y, x);
    findShootShip(map, player->cruisers, &(player->remainParts), CRUISER_LENGTH,
                  player->cruisersCount,
                  y, x);
    findShootShip(map, player->destroyers, &(player->remainParts), DESTROYER_LENGTH,
                  player->destroyersCount, y, x);
}

void Ship::checkShootPossibility(int y, int x, char *commandToPrint, Map *map) {
    if (canon->isDestroyed) {
        std::cout << "INVALID OPERATION \"" << commandToPrint
                  << "\": SHIP CANNOT SHOOT"
                  << std::endl;
        exit(EXIT_CODE);
    }
    if (!checkIfPointIsInRange(canon->y, canon->x, y, x, shootRange, map)) {
        std::cout << "INVALID OPERATION \"" << commandToPrint
                  << "\": SHOOTING TOO FAR"
                  << std::endl;
        exit(EXIT_CODE);
    }
    if (--availableShoots < 0) {
        std::cout << "INVALID OPERATION \"" << commandToPrint
                  << "\": TOO MANY SHOOTS"
                  << std::endl;
        exit(EXIT_CODE);
    }
}

void Ship::checkGameSet(Player *player, char *commandToPrint) {
    if (player->setCarriers != 0 || player->setCruisers != 0 || player->setDestroyers != 0 ||
        player->setBattleships != 0) {
        std::cout << "INVALID OPERATION \"" << commandToPrint
                  << "\": ALL SHIPS NOT PLACED"
                  << std::endl;
        exit(EXIT_CODE);
    }
}

void Ship::checkMovePossibility(char *commandToPrint) {
    if (engine->isDestroyed) {
        std::cout << "INVALID OPERATION \"" << commandToPrint
                  << "\": SHIP CANNOT MOVE"
                  << std::endl;
        exit(EXIT_CODE);
    }
    if (--availableMoves < 0) {
        std::cout << "INVALID OPERATION \"" << commandToPrint
                  << "\": SHIP MOVED ALREADY"
                  << std::endl;
        exit(EXIT_CODE);
    }
}

void Ship::checkPlacingPossibility(Map *map, int y, int x, char *commandToPrint) {
    if (map->map[y][x] == REEF_FIELD_SYMBOL) {
        std::cout << "INVALID OPERATION \"" << commandToPrint
                  << "\": PLACING SHIP ON REEF"
                  << std::endl;
        exit(EXIT_CODE);
    } else if (map->map[y][x] != EMPTY_FIELD_SYMBOL) {
        std::cout << "INVALID OPERATION \"" << commandToPrint
                  << "\": PLACING SHIP TOO CLOSE TO OTHER SHIP"
                  << std::endl;
        exit(EXIT_CODE);
    }
}

Ship::~Ship() {
    delete[] segments;
}

void Ship::spy(int y, int x, Map *map, Player *player, char *commandToPrint) {
    if (--availableShoots < 0) {
        std::cout << "INVALID OPERATION \"" << commandToPrint
                  << "\": TOO MANY SHOOTS"
                  << std::endl;
        exit(EXIT_CODE);
    }
    for (int i = y - 3; i <= y + 3; i++) {
        for (int j = x - 3; j <= x + 3; j++) {
            if (i >= 0 && i < map->height && j >= 0 && j < map->width) {
                if (checkIfPointIsInRange(y, x, i, j, lenght, map)) {
                    switch (player->playerGroup) {
                        case PLAYER_A:
                            map->aVisibilities[i][j] = VISIBLE_BY_A;
                            break;
                        case PLAYER_B:
                            map->bVisibilities[i][j] = VISIBLE_BY_B;
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }
}


