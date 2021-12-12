//
// Created by Kacper on 24.11.2021.
//

#ifndef BSHIPS_SHIP_H
#define BSHIPS_SHIP_H

#include "Map.h"
#include "Segment.h"
#include "Canon.h"
#include "Engine.h"
#include "Radar.h"
#include "utils.h"

class Player;

class Ship {
public:
    int headX;
    int headY;
    int lenght;
    Direction direction;
    int shootRange;

    bool isSet = false;
    int availableMoves;
    int availableShoots;

    Segment *segments;
    Segment *canon;
    Segment *engine;
    Segment *radar;

    Ship();

    virtual ~Ship();

    void reset();

    void shoot(BattleshipGame *game, char *commandToPrint, int y, int x);

    void spy(int y, int x, Map *map, Player *player, char *commandToPrint);

    static void findShootShips(Map *map, Player *player, int y, int x);

    static void findShootShip(Map *map, Ship *ships, int *remainParts, int len, int shipsCount, int y, int x);

    void checkShootPossibility(int y, int x, char *commandToPrint, Map*map);

    static void checkGameSet(Player *player, char *commandToPrint);

    //functions responsible for moving ship
    //for example nl() means, that ship pointed north turns left

    void move(Map *map, MoveDirection moveDirection, char *commandToPrint);

    void forward(Map *map, char *commandToPrint) const;

    void moveStraight(int ver, int hor, Map *map, char *commandToPrint) const;

    void moveWithDirChange(int yOffset, int xOffset, int index, Map *map, char *commandToPrint) const;

    void nr(Map *map, char *commandToPrint) const;

    void nl(Map *map, char *commandToPrint) const;

    void sr(Map *map, char *commandToPrint) const;

    void sl(Map *map, char *commandToPrint) const;

    void er(Map *map, char *commandToPrint) const;

    void el(Map *map, char *commandToPrint) const;

    void wr(Map *map, char *commandToPrint) const;

    void wl(Map *map, char *commandToPrint) const;

    void checkMovePossibility(char *commandToPrint);

    //functions responsible for creating segments, either default or from SHIP command

    virtual void setSegments() = 0;

    void setSegments(const int *outerSegments, Map *map) const;

    void resolveSegments();

    void setVisibility(Map *map, Player *player) const;

    void placeOnMap(Map *map, char *commandToPrint) const;

    void checkSurrounding(Map *map, char *commandToPrint) const;

    void checkFieldsNS(Map *map, char *commandToPrint) const;

    void checkFieldsWE(Map *map, char *commandToPrint) const;

    static void checkPlacingPossibility(Map *map, int y, int x, char *commandToPrint) ;

    static bool checkIfPointIsInRange(int y, int x, int yp, int xp, int radius, Map*map) ;

};


#endif //BSHIPS_SHIP_H