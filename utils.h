//
// Created by Kacper on 06.12.2021.
//

#ifndef BSHIPS_UTILS_H
#define BSHIPS_UTILS_H

#define EXIT_CODE 1

#define CANON_SYMBOL '!'
#define ENGINE_SYMBOL '%'
#define RADAR_SYMBOL '@'
#define SEGMENT_SYMBOL '+'

#define EMPTY_FIELD_SYMBOL ' '
#define REEF_FIELD_SYMBOL '#'
#define HIT_FIELD_SYMBOL 'x'
#define UNKNOWN_FIELD_SYMBOL '?'

#define A_START_Y 0
#define A_START_X 0
#define A_END_Y 9
#define A_END_X 9

#define B_START_Y 11
#define B_START_X 0
#define B_END_Y 20
#define B_END_X 9

#define CARRIER_LENGTH 5
#define BATTLESHIP_LENGTH 4
#define CRUISER_LENGTH 3
#define DESTROYER_LENGTH 2

#define CARRIER_SHOOT_RANGE INT_MAX

#define DEFAULT_MOVES_NUMBER 3
#define CARRIER_MOVES_NUMBER 2

#define DEFAULT_CARRIERS_NUMBER 1
#define DEFAULT_BATTLESHIPS_NUMBER 2
#define DEFAULT_CRUISERS_NUMBER 3
#define DEFAULT_DESTROYERS_NUMBER 4

#define SHIPS_NUMBER 4

#define MIN_MAP_HEIGHT 11
#define MIN_MAP_WIDTH 10

#define DEFAULT_HEIGHT 21
#define DEFAULT_WIDTH 10

#define MAX_TOKEN_LENGTH 10
#define MAX_COMMAND_LENGTH 40

#define MAX_SAVE_STATEMENTS 20

#define MAX_SHIPS 10

enum Direction {
    N, S, W, E
};

enum MoveDirection {
    FORWARD, LEFT, RIGHT
};

enum ShipClass {
    CAR, BAT, CRU, DES
};

enum Groups {
    EMPTY, STATE, PLAYER_A, PLAYER_B
};

enum FieldState {
    EMPTY_FIELD, PLAYER_A_FIELD, PLAYER_B_FIELD
};

enum Visibility {
    UNKNOWN, VISIBLE_BY_A, VISIBLE_BY_B
};

#endif //BSHIPS_UTILS_H
