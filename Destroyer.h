//
// Created by Kacper on 25.11.2021.
//

#ifndef BSHIPS_DESTROYER_H
#define BSHIPS_DESTROYER_H


#include "Ship.h"

class Destroyer : public Ship {
public:
    Destroyer();

    void setSegments() override;

};


#endif //BSHIPS_DESTROYER_H



