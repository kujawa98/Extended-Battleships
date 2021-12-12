//
// Created by Kacper on 22.11.2021.
//


#ifndef BSHIPS_PLAYER_H
#define BSHIPS_PLAYER_H

#include "utils.h"
#include "Ship.h"

class BattleshipGame;

class Map;

class Player {
public:
    Groups playerGroup;
    int remainParts;

    Ship *carriers;
    Ship *destroyers;
    Ship *cruisers;
    Ship *battleships;

    int setCarriers;
    int setDestroyers;
    int setCruisers;
    int setBattleships;

    int carriersCount;
    int destroyersCount;
    int cruisersCount;
    int battleshipsCount;

    int startY;
    int startX;
    int endY;
    int endX;

    explicit Player(Groups playerGroup);

    virtual ~Player();

    void setFleet(const int *ships);

    void shoot(BattleshipGame *game, char commandToPrint[50], int y, int x) const;

    void setBasicFleet();

    bool checkStartingPosition(int y, int x, char *commandToPrint) const;

    void deleteShips() const;

    Ship *
    placeShip(Map *map, char commandToPrint[50], int head_y, int head_x, int index, Direction dir, ShipClass shipClass);

    Ship *createShip(Map *map, int head_y, char *commandToPrint, int head_x, int index, Direction dir,
                     ShipClass shipClass);

    void initPosition(int yStart, int xStart, int yEnd, int xEnd);

    void move(Map *map, int index, ShipClass shipClass, MoveDirection moveDirection, char *commandToPrint) const;

    void
    extendedShoot(BattleshipGame *game, char *commandToPrint, int index, ShipClass shipClass, int head_y, int head_x) const;

    Ship *setShips(Map *map, Ship *ships, int shipCount, int *setShip, int index, int head_y, char *commandToPrint,
                   int head_x,
                   Direction dir,
                   ShipClass shipClass);

    void allocateShip(Map *map, int index, int head_y, char *commandToPrint, int head_x,
                      Direction dir,
                      ShipClass shipClass, int *segments);

    void print(Map *map) const;

    void spy(int index, int y, int x, Map *map, char* commandToPrint);

    void reset() const;

    void resetCarriers() const;

    void resetBattleships() const;

    void resetCruisers() const;

    void resetDestroyers() const;
};


#endif //BSHIPS_PLAYER_H
