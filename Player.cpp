//
// Created by Kacper on 22.11.2021.
//

#include <iostream>
#include "Player.h"
#include "Carrier.h"
#include "Destroyer.h"
#include "Cruiser.h"
#include "Battleship.h"
#include "BattleshipGame.h"

Player::Player(Groups playerGroup) : playerGroup(playerGroup) {
    setBasicFleet();
    remainParts = 0;
}

void Player::setFleet(const int *ships) {
    for (int i = 0; i < SHIPS_NUMBER; i++) {
        if (ships[i] > MAX_SHIPS) {
            std::cout << "MAXIMUM AMOUNT OF SHIPS IS 10" << std::endl;
            exit(EXIT_CODE);
        }
    }
    deleteShips();
    this->carriers = new Carrier[ships[0]];
    this->battleships = new Battleship[ships[1]];
    this->cruisers = new Cruiser[ships[2]];
    this->destroyers = new Destroyer[ships[3]];
    setCarriers = ships[0];
    setBattleships = ships[1];
    setCruisers = ships[2];
    setDestroyers = ships[3];
    carriersCount = ships[0];
    battleshipsCount = ships[1];
    cruisersCount = ships[2];
    destroyersCount = ships[3];
}


Player::~Player() {
    deleteShips();
}


void Player::setBasicFleet() {
    this->carriers = new Carrier[DEFAULT_CARRIERS_NUMBER];
    this->battleships = new Battleship[DEFAULT_BATTLESHIPS_NUMBER];
    this->cruisers = new Cruiser[DEFAULT_CRUISERS_NUMBER];
    this->destroyers = new Destroyer[DEFAULT_DESTROYERS_NUMBER];
    setCarriers = DEFAULT_CARRIERS_NUMBER;
    setBattleships = DEFAULT_BATTLESHIPS_NUMBER;
    setCruisers = DEFAULT_CRUISERS_NUMBER;
    setDestroyers = DEFAULT_DESTROYERS_NUMBER;
    carriersCount = DEFAULT_CARRIERS_NUMBER;
    battleshipsCount = DEFAULT_BATTLESHIPS_NUMBER;
    cruisersCount = DEFAULT_CRUISERS_NUMBER;
    destroyersCount = DEFAULT_DESTROYERS_NUMBER;
}

void Player::deleteShips() const {
    delete[] carriers;
    delete[] battleships;
    delete[] destroyers;
    delete[] cruisers;
}

bool Player::checkStartingPosition(int y, int x, char *commandToPrint) const {
    if ((y > endY || y < startY) || (x > endX || x < startX)) {
        std::cout << "INVALID OPERATION \"" << commandToPrint
                  << "\": NOT IN STARTING POSITION"
                  << std::endl;
        exit(EXIT_CODE);
    }
    return true;
}


Ship *Player::placeShip(Map *map, char *commandToPrint, int head_y, int head_x, int index, Direction dir,
                        ShipClass shipClass) {
    if ((head_y > endY || head_y < startY) || (head_x > endX || head_x < startX)) {
        std::cout << "INVALID OPERATION \"" << commandToPrint
                  << "\": NOT IN STARTING POSITION"
                  << std::endl;
        exit(EXIT_CODE);
    }
    Ship *shp = createShip(map, head_y, commandToPrint, head_x, index, dir, shipClass);
    int ln = shp->lenght;
    if (ln == -1) {
        return nullptr;
    }

    if (playerGroup == PLAYER_A) {
        map->states[head_y][head_x] = FieldState::PLAYER_A_FIELD;
    } else {
        map->states[head_y][head_x] = FieldState::PLAYER_B_FIELD;
    }
    for (int i = 0; i < ln; i++) {
        if (dir == N) {
            checkStartingPosition(head_y + i, head_x, commandToPrint);
            map->states[head_y + i][head_x] = map->states[head_y][head_x];

        } else if (dir == S) {
            checkStartingPosition(head_y - i, head_x, commandToPrint);
            map->states[head_y - i][head_x] = map->states[head_y][head_x];


        } else if (dir == W) {
            checkStartingPosition(head_y, head_x + i, commandToPrint);
            map->states[head_y][head_x + i] = map->states[head_y][head_x];


        } else if (dir == E) {
            checkStartingPosition(head_y, head_x - i, commandToPrint);
            map->states[head_y][head_x - i] = map->states[head_y][head_x];

        }
    }
    remainParts += ln;
    return shp;
}

Ship *
Player::setShips(Map *map, Ship *ships, int shipCount, int *setShip, int index, int head_y, char *commandToPrint,
                 int head_x,
                 Direction dir,
                 ShipClass shipClass) {
    if (index < shipCount && ships[index].isSet) {
        std::cout << "INVALID OPERATION \"" << commandToPrint
                  << "\": SHIP ALREADY PRESENT"
                  << std::endl;

        std::exit(EXIT_CODE);
    } else if (*setShip == 0) {
        std::cout << "INVALID OPERATION \"" << commandToPrint
                  << "\": ALL SHIPS OF THE CLASS ALREADY SET"
                  << std::endl;
        exit(EXIT_CODE);
    }
    switch (shipClass) {
        case BAT:
            ships[index] = Battleship();
            break;
        case CRU:
            ships[index] = Cruiser();
            break;
        case CAR:
            ships[index] = Carrier();
            break;
        case DES:
            ships[index] = Destroyer();
            break;
    }
    ships[index].headY = head_y;
    ships[index].headX = head_x;
    ships[index].direction = dir;
    (*setShip)--;
    ships[index].isSet = true;
    ships[index].setSegments();
    ships[index].placeOnMap(map, commandToPrint);
    ships[index].setVisibility(map, this);
    return &ships[index];
}

Ship *Player::createShip(Map *map, int head_y, char *commandToPrint, int head_x, int index, Direction dir,
                         ShipClass shipClass) {
    switch (shipClass) {
        case CAR:
            return setShips(map, carriers, carriersCount, &setCarriers, index, head_y, commandToPrint, head_x, dir,
                            shipClass);
        case BAT:
            return setShips(map, battleships, battleshipsCount, &setBattleships, index, head_y, commandToPrint, head_x,
                            dir,
                            shipClass);
        case CRU:
            return setShips(map, cruisers, cruisersCount, &setCruisers, index, head_y, commandToPrint, head_x, dir,
                            shipClass);
        case DES:
            return setShips(map, destroyers, destroyersCount, &setDestroyers, index, head_y, commandToPrint, head_x,
                            dir,
                            shipClass);
        default:
            return nullptr;
    }
}


void Player::initPosition(int yStart, int xStart, int yEnd, int xEnd) {
    startY = yStart;
    startX = xStart;
    endY = yEnd;
    endX = xEnd;
}

void Player::shoot(BattleshipGame *game, char *commandToPrint, int y, int x) const {
    if ((y >= game->map->height || y < 0) || (x >= game->map->width || x < 0)) {
        std::cout << "INVALID OPERATION \"" << commandToPrint
                  << "\": FIELD DOES NOT EXIST"
                  << std::endl;
        exit(EXIT_CODE);
    }
    if (setCarriers != 0 || setCruisers != 0 || setDestroyers != 0 || setBattleships != 0) {
        std::cout << "INVALID OPERATION \"" << commandToPrint
                  << "\":  NOT ALL SHIPS PLACED"
                  << std::endl;
        exit(EXIT_CODE);
    }
    if (game->playerB->setCarriers != 0 || game->playerB->setCruisers != 0 || game->playerB->setDestroyers != 0 ||
        game->playerB->setBattleships != 0) {
        std::cout << "INVALID OPERATION \"" << commandToPrint
                  << "\":  NOT ALL SHIPS PLACED"
                  << std::endl;
        exit(EXIT_CODE);
    }
    if (game->map->map[y][x] != EMPTY_FIELD_SYMBOL && game->map->map[y][x] != REEF_FIELD_SYMBOL &&
        game->map->map[y][x] != HIT_FIELD_SYMBOL) {
        Ship::findShootShips(game->map, game->playerA, y, x);
        Ship::findShootShips(game->map, game->playerB, y, x);
    }
    game->checkVictory();
}

void Player::extendedShoot(BattleshipGame *game, char *commandToPrint, int index, ShipClass shipClass, int head_y,
                           int head_x) const {
    switch (shipClass) {
        case CAR:
            carriers[index].shoot(game, commandToPrint, head_y, head_x);
            break;
        case BAT:
            battleships[index].shoot(game, commandToPrint, head_y, head_x);
            break;
        case CRU:
            cruisers[index].shoot(game, commandToPrint, head_y, head_x);
            break;
        case DES:
            destroyers[index].shoot(game, commandToPrint, head_y, head_x);
            break;
        default:
            break;
    }
}

void Player::move(Map *map, int index, ShipClass shipClass, MoveDirection moveDirection, char *commandToPrint) const {
    switch (shipClass) {
        case CAR:
            carriers[index].move(map, moveDirection, commandToPrint);
            break;
        case BAT:
            battleships[index].move(map, moveDirection, commandToPrint);
            break;
        case CRU:
            cruisers[index].move(map, moveDirection, commandToPrint);
            break;
        case DES:
            destroyers[index].move(map, moveDirection, commandToPrint);
            break;
    }
}

void Player::print(Map *map) const {
    for (int i = 0; i < map->height; i++) {
        for (int j = 0; j < map->width; j++) {
            switch (playerGroup) {
                case PLAYER_A:
                    if (map->aVisibilities[i][j] == VISIBLE_BY_A) {
                        if (map->map[i][j] != EMPTY_FIELD_SYMBOL && map->map[i][j] != REEF_FIELD_SYMBOL &&
                            map->map[i][j] != HIT_FIELD_SYMBOL) {
                            std::cout << SEGMENT_SYMBOL;
                        } else {
                            std::cout << map->map[i][j];
                        }
                    } else {
                        std::cout << UNKNOWN_FIELD_SYMBOL;
                    }
                    break;
                case PLAYER_B:
                    if (map->bVisibilities[i][j] == VISIBLE_BY_B) {
                        if (map->map[i][j] != EMPTY_FIELD_SYMBOL && map->map[i][j] != REEF_FIELD_SYMBOL &&
                            map->map[i][j] != HIT_FIELD_SYMBOL) {
                            std::cout << SEGMENT_SYMBOL;
                        } else {
                            std::cout << map->map[i][j];
                        }
                    } else {
                        std::cout << UNKNOWN_FIELD_SYMBOL;
                    }
                    break;
                default:
                    break;
            }

        }
        std::cout << std::endl;
    }
}

void Player::allocateShip(Map *map, int index, int head_y, char *commandToPrint, int head_x, Direction dir,
                          ShipClass shipClass, int *segments) {
    Ship *shp = placeShip(map, commandToPrint, head_y, head_x, index, dir, shipClass);
    shp->setSegments(segments, map);
    for (int i = 0; i < shp->lenght; i++) {
        if (segments[i] == 0) {
            remainParts--;
        }
    }
}

void Player::reset() const {
    resetCarriers();
    resetBattleships();
    resetCruisers();
    resetDestroyers();
}

void Player::resetCarriers() const {
    for (int i = 0; i < carriersCount; i++) {
        carriers[i].reset();
    }
}

void Player::resetBattleships() const {
    for (int i = 0; i < battleshipsCount; i++) {
        battleships[i].reset();
    }
}

void Player::resetCruisers() const {
    for (int i = 0; i < cruisersCount; i++) {
        cruisers[i].reset();
    }
}

void Player::resetDestroyers() const {
    for (int i = 0; i < destroyersCount; i++) {
        destroyers[i].reset();
    }
}

void Player::spy(int index, int y, int x, Map *map, char* commandToPrint) {
    carriers[index].spy(y, x, map, this, commandToPrint);
}
