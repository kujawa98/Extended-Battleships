//
// Created by Kacper on 25.11.2021.
//

#include "Cruiser.h"
#include "Player.h"
#include <iostream>

Cruiser::Cruiser() {
    lenght = CRUISER_LENGTH;
    availableShoots = CRUISER_LENGTH;
    shootRange=CRUISER_LENGTH;
}

void Cruiser::setSegments() {
    segments = new Segment[lenght];
    segments[0] = Radar();
    segments[1] = Canon();
    segments[2] = Engine();
    resolveSegments();
}

