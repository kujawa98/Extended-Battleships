//
// Created by Kacper on 02.12.2021.
//

#ifndef BSHIPS_SEGMENT_H
#define BSHIPS_SEGMENT_H

#include "utils.h"
class Segment {
public:
    bool isDestroyed;
    int y;
    int x;
    char symbol;

    Segment();
};


#endif //BSHIPS_SEGMENT_H