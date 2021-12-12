//
// Created by Kacper on 25.11.2021.
//

#include "Destroyer.h"
#include "Player.h"

Destroyer::Destroyer() {
    lenght = DESTROYER_LENGTH;
    availableShoots = DESTROYER_LENGTH;
    shootRange = DESTROYER_LENGTH;
}

void Destroyer::setSegments() {
    segments = new Segment[lenght];
    segments[0] = Radar();
    segments[1] = Engine();
    resolveSegments();
}
