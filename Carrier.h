//
// Created by Kacper on 24.11.2021.
//

#ifndef BSHIPS_CARRIER_H
#define BSHIPS_CARRIER_H


#include "Ship.h"

class Carrier : public Ship {
public:
    Carrier();

    void setSegments() override;

};


#endif //BSHIPS_CARRIER_H
