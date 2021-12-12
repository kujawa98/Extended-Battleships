#include "Battleship.h"

#include <iostream>
#include "Player.h"

Battleship::Battleship() {
    lenght = BATTLESHIP_LENGTH;
    availableShoots = BATTLESHIP_LENGTH;
    shootRange = BATTLESHIP_LENGTH;
}

void Battleship::setSegments() {
    segments = new Segment[lenght];
    segments[0] = Radar();
    segments[1] = Canon();
    segments[2] = Segment();
    segments[3] = Engine();
    resolveSegments();
}
