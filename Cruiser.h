//
// Created by Kacper on 25.11.2021.
//

#ifndef BSHIPS_CRUISER_H
#define BSHIPS_CRUISER_H


#include "Ship.h"

class Cruiser : public Ship{
public:
    Cruiser();

    void setSegments() override;

};


#endif //BSHIPS_CRUISER_H
