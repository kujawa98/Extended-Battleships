//
// Created by Kacper on 22.11.2021.
//
#include <string.h>
#include "Tokens.h"
#include "utils.h"

void Tokens::createTokens(char *input) {
    lenght = 0;
    char *token = strtok(input, " ");
    for (int i = 0; i < MAX_TOKEN_LENGTH; i++) {
        if (token != NULL) {
            tokens[i] = token;
            lenght++;
        }
        token = strtok(NULL, " ");
    }
}

Tokens::Tokens() {
    tokens = new char *[MAX_TOKEN_LENGTH];
    lenght = 0;
}

Tokens::~Tokens() {
    delete[]tokens;
}
