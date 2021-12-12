//
// Created by Kacper on 24.11.2021.
//

#include "Carrier.h"
#include <limits.h>

Carrier::Carrier() {
    lenght = CARRIER_LENGTH;
    availableShoots = CARRIER_LENGTH;
    availableMoves = CARRIER_MOVES_NUMBER;
    shootRange = CARRIER_SHOOT_RANGE;
}

void Carrier::setSegments() {
    segments = new Segment[lenght];
    segments[0] = Radar();
    segments[1] = Canon();
    segments[2] = Segment();
    segments[3] = Segment();
    segments[4] = Engine();
    resolveSegments();
}

