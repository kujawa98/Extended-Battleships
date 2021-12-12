#ifndef BSHIPS_BATTLESHIP_H
#define BSHIPS_BATTLESHIP_H


#include "Ship.h"

class Battleship : public Ship{
public:
    Battleship();

    void setSegments() override;

};


#endif //BSHIPS_BATTLESHIP_H