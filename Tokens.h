//
// Created by Kacper on 22.11.2021.
//

#ifndef BSHIPS_TOKENS_H
#define BSHIPS_TOKENS_H


class Tokens {
public:
    char **tokens;
    int lenght;

    Tokens();

    virtual ~Tokens();

    void createTokens(char *input);
};


#endif //BSHIPS_TOKENS_H
