//
// Created by Kacper on 22.11.2021.
//

#include "CommandsHandler.h"
#include <iostream>

void CommandsHandler::handleCommand() {
    strncpy(commandToPrint, currentCommand, MAX_COMMAND_LENGTH);
    if (strcmp(currentCommand, "[state]") == 0) {
        handleStateEntry();
    } else if (strcmp(currentCommand, "[playerA]") == 0) {
        handlePlayerEntry(PLAYER_A);
    } else if (strcmp(currentCommand, "[playerB]") == 0) {
        handlePlayerEntry(PLAYER_B);
    } else if (strcmp(currentCommand, "") == 0) {
    } else {
        handleNonEntryCommand();
    }
}

void CommandsHandler::handleStateEntry() {
    if (currentGroup == EMPTY) {
        currentGroup = STATE;
    } else if (currentGroup == STATE) {
        currentGroup = EMPTY;
        initState = false;
    } else {
        std::cout << "INVALID OPERATION " << commandToPrint << " SPECIFIED: WRONG COMMAND GROUP"
                  << std::endl;
    }
}

void CommandsHandler::handlePlayerEntry(Groups playerGroup) {
    if (currentGroup == EMPTY) {
        if (playerGroup != game.nextPlayer->playerGroup) {
            std::cout << "INVALID OPERATION \"" << commandToPrint
                      << " \": THE OTHER PLAYER EXPECTED"
                      << std::endl;
            exit(EXIT_CODE);
        } else {
            currentGroup = playerGroup;
            initState = false;
        }
    } else if (currentGroup == playerGroup) {
        currentGroup = EMPTY;
        switch (playerGroup) {
            case PLAYER_A:
                game.nextPlayer = game.playerB;
                game.playerA->reset();
                break;
            case PLAYER_B:
                game.nextPlayer = game.playerA;
                game.playerB->reset();
                break;
            default:
                break;
        }
    } else {
        std::cout << "INVALID OPERATION " << commandToPrint
                  << " : WRONG COMMAND GROUP"
                  << std::endl;
    }
}

void CommandsHandler::handleNonEntryCommand() {
    tokens.createTokens(currentCommand);
    if (currentGroup == STATE) {
        handleStateCommands();
    } else if (currentGroup == PLAYER_A) {
        handlePlayerCommand(game.playerA);
    } else if (currentGroup == PLAYER_B) {
        handlePlayerCommand(game.playerB);
    } else {
        std::cout << "INVALID OPERATION " << commandToPrint << " SPECIFIED: NOT IN COMMAND GROUP"
                  << std::endl;
    }
}

void CommandsHandler::handleStateCommands() {
    if (strcmp(tokens.tokens[0], "PRINT") == 0) {
        handlePrint();
    } else if (strcmp(tokens.tokens[0], "NEXT_PLAYER") == 0) {
        handleNextPlayer();
    } else if (strcmp(tokens.tokens[0], "SET_FLEET") == 0) {
        handleSetFleet();
    } else if (strcmp(tokens.tokens[0], "BOARD_SIZE") == 0) {
        handleBoardSize();
    } else if (strcmp(tokens.tokens[0], "REEF") == 0) {
        handleReef();
    } else if (strcmp(tokens.tokens[0], "INIT_POSITION") == 0) {
        handleInitPosition();
    } else if (strcmp(tokens.tokens[0], "SHIP") == 0) {
        handleShip();
    } else if (strcmp(tokens.tokens[0], "SAVE") == 0) {
        handleSave();
    } else if (strcmp(tokens.tokens[0], "EXTENDED_SHIPS") == 0) {
        extendedBehavior = true;
    } else {
        std::cout << "INVALID OPERATION " << commandToPrint
                  << " SPECIFIED: UNKNOWN [state] COMMAND"
                  << std::endl;
    }
}

void CommandsHandler::handlePlayerCommand(Player *player) {
    if (strcmp(tokens.tokens[0], "SHOOT") == 0) {
        handleShoot(player);
    } else if (strcmp(tokens.tokens[0], "PLACE_SHIP") == 0) {
        handlePlaceShip(player);
    } else if (strcmp(tokens.tokens[0], "MOVE") == 0) {
        handleMove(player);
    } else if (strcmp(tokens.tokens[0], "PRINT") == 0) {
        player->print(game.map);
    } else if (strcmp(tokens.tokens[0], "SPY") == 0) {
        handleSpy(player);
    } else {
        std::cout << "INVALID OPERATION " << commandToPrint
                  << " SPECIFIED: UNKNOWN [playerA/B] COMMAND"
                  << std::endl;
    }
}

void CommandsHandler::handleShoot(Player *player) {
    if (!extendedBehavior) {
        int head_y = atoi(tokens.tokens[1]);
        int head_x = atoi(tokens.tokens[2]);
        player->shoot(&game, commandToPrint, head_y, head_x);
    } else {
        int index = atoi(tokens.tokens[1]);
        ShipClass shipClass = getShipClass(tokens.tokens[2]);
        int head_y = atoi(tokens.tokens[3]);
        int head_x = atoi(tokens.tokens[4]);
        player->extendedShoot(&game, commandToPrint, index, shipClass, head_y, head_x);
    }
}

void CommandsHandler::handlePlaceShip(Player *player) {
    int head_y = atoi(tokens.tokens[1]);
    int head_x = atoi(tokens.tokens[2]);
    Direction dir = getDirection(tokens.tokens[3][0]);
    int index = atoi(tokens.tokens[4]);
    ShipClass shipClass = getShipClass(tokens.tokens[5]);
    player->placeShip((game.map), commandToPrint, head_y, head_x, index, dir, shipClass);
}

void CommandsHandler::handleMove(Player *player) {
    if (!extendedBehavior) {
        int index = atoi(tokens.tokens[1]);
        ShipClass shipClass = getShipClass(tokens.tokens[2]);
        MoveDirection moveDirection = getMoveDirection(tokens.tokens[3][0]);
        player->move(game.map, index, shipClass, moveDirection, commandToPrint);
    } else {
        return;
    }
}

void CommandsHandler::handlePrint() {
    if (strcmp(tokens.tokens[1], "0") == 0) {
        game.map->basicPrint(&game);
    } else if (strcmp(tokens.tokens[1], "1") == 0) {
        game.map->extendedPrint(&game);
    } else {
        std::cout << "INVALID OPERATION " << commandToPrint
                  << " SPECIFIED: FORBIDDEN ARGUMENT VALUE"
                  << std::endl;
    }
}

void CommandsHandler::handleSetFleet() {
    checkInitState();
    int *ships = getShipsCount(tokens.tokens);
    if (strcmp(tokens.tokens[1], "A") == 0) {
        game.playerA->setFleet(ships);
    } else if (strcmp(tokens.tokens[1], "B") == 0) {
        game.playerB->setFleet(ships);
    } else {
        std::cout << "INVALID OPERATION " << commandToPrint
                  << " SPECIFIED: THERE'S NO SUCH PLAYER"
                  << std::endl;
        delete[] ships;
        exit(EXIT_CODE);
    }
    delete[] ships;
}


void CommandsHandler::handleNextPlayer() {
    checkInitState();
    if (strcmp(tokens.tokens[1], "A") == 0) {
        game.nextPlayer = game.playerA;
    } else if (strcmp(tokens.tokens[1], "B") == 0) {
        game.nextPlayer = game.playerB;
    } else {
        std::cout << "INVALID OPERATION \"" << commandToPrint
                  << "\": THERE'S NO SUCH PLAYER"
                  << std::endl;
        exit(EXIT_CODE);
    }
}

void CommandsHandler::handleBoardSize() {
    checkInitState();
    int y = atoi(tokens.tokens[1]);
    int x = atoi(tokens.tokens[2]);
    delete game.map;
    game.map = new Map(y, x);
}

void CommandsHandler::handleReef() {
    checkInitState();
    int y = atoi(tokens.tokens[1]);
    int x = atoi(tokens.tokens[2]);
    if ((y >= game.map->height || y < 0) || (x >= game.map->width || x < 0)) {
        std::cout << "INVALID OPERATION \"" << commandToPrint << "\": " << "REEF IS NOT PLACED ON BOARD";
        exit(EXIT_CODE);
    } else {
        game.map->map[y][x] = '#';
    }
}

void CommandsHandler::handleInitPosition() {
    checkInitState();
    int startY = atoi(tokens.tokens[2]);
    int startX = atoi(tokens.tokens[3]);
    int endY = atoi(tokens.tokens[4]);
    int endX = atoi(tokens.tokens[5]);
    if (strcmp(tokens.tokens[1], "A") == 0) {
        game.playerA->initPosition(startY, startX, endY, endX);
    } else if (strcmp(tokens.tokens[1], "B") == 0) {
        game.playerB->initPosition(startY, startX, endY, endX);
    } else {
        std::cout << "INVALID OPERATION " << commandToPrint
                  << " SPECIFIED: THERE'S NO SUCH PLAYER"
                  << std::endl;
        exit(EXIT_CODE);
    }
}


void CommandsHandler::handleShip() {
    checkInitState();
    int y = atoi(tokens.tokens[2]);
    int x = atoi(tokens.tokens[3]);
    Direction dir = getDirection(tokens.tokens[4][0]);
    int index = atoi(tokens.tokens[5]);
    ShipClass shipClass = getShipClass(tokens.tokens[6]);
    int *segments = getSegments(tokens.tokens[7]);
    if (strcmp(tokens.tokens[1], "A") == 0) {
        game.playerA->allocateShip(game.map, index, y, commandToPrint, x, dir, shipClass, segments);
    } else if (strcmp(tokens.tokens[1], "B") == 0) {
        game.playerB->allocateShip(game.map, index, y, commandToPrint, x, dir, shipClass, segments);
    } else {
        std::cout << "INVALID OPERATION " << commandToPrint
                  << " SPECIFIED: THERE'S NO SUCH PLAYER"
                  << std::endl;
    }
}


void CommandsHandler::handleSave() const {
    char **saveStatements = new char *[MAX_SAVE_STATEMENTS];
    for (int i = 0; i < MAX_SAVE_STATEMENTS; i++) {
        saveStatements[i] = new char[MAX_COMMAND_LENGTH];
    }
    sprintf(saveStatements[0], "[state]\n");
    sprintf(saveStatements[1], "BOARD_SIZE %d %d\n", game.map->height, game.map->width);
    int statementCounter = 2;
    for (int i = 0; i < game.map->height; i++) {
        for (int j = 0; j < game.map->width; j++) {
            if (game.map->map[i][j] == REEF_FIELD_SYMBOL) {
                sprintf(saveStatements[statementCounter++], "REEF %d %d\n", i, j);
            }
        }
    }
    switch (game.nextPlayer->playerGroup) {
        case PLAYER_A:
            sprintf(saveStatements[statementCounter++], "NEXT_PLAYER A\n");
            break;
        case PLAYER_B:
            sprintf(saveStatements[statementCounter++], "NEXT_PLAYER B\n");
            break;
        default:
            break;
    }
    sprintf(saveStatements[statementCounter++], "INIT_POSITION A %d %d %d %d\n", game.playerA->startY,
            game.playerA->startX, game.playerA->endY, game.playerA->endX);
    sprintf(saveStatements[statementCounter++], "SET_FLEET A %d %d %d %d\n", game.playerA->carriersCount,
            game.playerA->battleshipsCount,
            game.playerA->cruisersCount, game.playerA->destroyersCount);

    saveShip(saveStatements, &statementCounter, game.playerA->carriers, CARRIER_LENGTH, game.playerA->carriersCount,
             CAR);

    saveShip(saveStatements, &statementCounter, game.playerA->battleships, BATTLESHIP_LENGTH,
             game.playerA->battleshipsCount, BAT);
    saveShip(saveStatements, &statementCounter, game.playerA->cruisers, CRUISER_LENGTH, game.playerA->cruisersCount,
             CRU);
    saveShip(saveStatements, &statementCounter, game.playerA->destroyers, DESTROYER_LENGTH,
             game.playerA->destroyersCount, DES);


    sprintf(saveStatements[statementCounter++], "INIT_POSITION B %d %d %d %d\n", game.playerB->startY,
            game.playerB->startX, game.playerB->endY, game.playerB->endX);
    sprintf(saveStatements[statementCounter++], "SET_FLEET B %d %d %d %d\n", game.playerB->carriersCount,
            game.playerB->battleshipsCount,
            game.playerB->cruisersCount, game.playerB->destroyersCount);
    saveShip(saveStatements, &statementCounter, game.playerB->carriers, CARRIER_LENGTH, game.playerB->carriersCount,
             CAR);
    saveShip(saveStatements, &statementCounter, game.playerB->battleships, BATTLESHIP_LENGTH,
             game.playerB->battleshipsCount, BAT);
    saveShip(saveStatements, &statementCounter, game.playerB->cruisers, CRUISER_LENGTH, game.playerB->cruisersCount,
             CRU);
    saveShip(saveStatements, &statementCounter, game.playerB->destroyers, DESTROYER_LENGTH,
             game.playerB->destroyersCount, DES);
    sprintf(saveStatements[statementCounter++], "[state]\n");

    for (int i = 0; i < statementCounter; i++) {
        std::cout << saveStatements[i];
    }


}

int *CommandsHandler::getShipsCount(char **tokens) {
    int *ships = new int[4];
    for (int i = 0; i < 4; i++) {
        ships[i] = atoi(tokens[i + 2]);
    }
    return ships;
}

Direction CommandsHandler::getDirection(char token) {
    switch (token) {
        case 'N':
            return N;
        case 'S':
            return S;
        case 'W':
            return W;
        case 'E':
            return E;
        default:
            std::cout << "INVALID OPERATION " << commandToPrint
                      << " SPECIFIED: UNKNOWN DIRECTION"
                      << std::endl;
            return N;
    }
}

ShipClass CommandsHandler::getShipClass(char *toks) const {
    if (strcmp(toks, "CAR") == 0) {
        return CAR;
    } else if (strcmp(toks, "CRU") == 0) {
        return CRU;
    } else if (strcmp(toks, "BAT") == 0) {
        return BAT;
    } else if (strcmp(toks, "DES") == 0) {
        return DES;
    } else {
        std::cout << "INVALID OPERATION " << commandToPrint
                  << " SPECIFIED: THERE'S NO SUCH SHIP CLASS"
                  << std::endl;
        exit(EXIT_CODE);
    }
}

int *CommandsHandler::getSegments(char *toks) {
    int *seg = new int[strlen(toks)];
    for (int i = 0; i < strlen(toks); i++) {
        seg[i] = toks[i] - '0';
    }
    return seg;
}

MoveDirection CommandsHandler::getMoveDirection(char token) {
    switch (token) {
        case 'F':
            return FORWARD;
        case 'L':
            return LEFT;
        case 'R':
            return RIGHT;
        default:
            std::cout << "INVALID OPERATION " << commandToPrint
                      << " SPECIFIED: UNKNOWN DIRECTION"
                      << std::endl;
            exit(EXIT_CODE);
    }
}

void CommandsHandler::checkInitState() {
    if (!initState) {
        std::cout << "INVALID OPERATION " << commandToPrint
                  << " SPECIFIED: GAME ALREADY SET"
                  << std::endl;
        exit(EXIT_CODE);
    }
}

CommandsHandler::CommandsHandler() {
    initState = true;
    extendedBehavior = false;
    currentGroup = EMPTY;
}

void
CommandsHandler::saveShip(char **saveStatement, int *statementCounter, Ship *ships, int length, int shipsCount,
                          ShipClass shipClass) const {
    int *seg = new int[length];
    for (int i = 0; i < shipsCount; i++) {
        for (int j = 0; j < length; j++) {
            if (ships[i].segments[j].isDestroyed) {
                seg[j] = 0;
            } else {
                seg[j] = 1;
            }
        }
        char dir;
        switch (ships[i].direction) {
            case N:
                dir = 'N';
                break;
            case S:
                dir = 'S';
                break;
            case W:
                dir = 'W';
                break;
            case E:
                dir = 'E';
                break;
        }
        switch (shipClass) {
            case CAR:
                sprintf(saveStatement[(*statementCounter)++], "SHIP A %d %d %c %d CAR %d%d%d%d%d \n", ships[i].headY,
                        ships[i].headX, dir, i, seg[0], seg[1], seg[2],
                        seg[3], seg[4]);
                break;
            case BAT:
                sprintf(saveStatement[(*statementCounter)++], "SHIP A %d %d %c %d BAT %d%d%d%d \n", ships[i].headY,
                        ships[i].headX, dir, i, seg[0], seg[1], seg[2],
                        seg[3]);
                break;
            case CRU:
                sprintf(saveStatement[(*statementCounter)++], "SHIP A %d %d %c %d CRU %d%d%d \n", ships[i].headY,
                        ships[i].headX, dir, i, seg[0], seg[1], seg[2]);
                break;
            case DES:
                sprintf(saveStatement[(*statementCounter)++], "SHIP A %d %d %c %d DES %d%d \n", ships[i].headY,
                        ships[i].headX, dir, i, seg[0], seg[1]);
                break;
        }
    }
    delete[] seg;
}

void CommandsHandler::handleSpy(Player *player) {
    int index = atoi(tokens.tokens[1]);
    int y = atoi(tokens.tokens[2]);
    int x = atoi(tokens.tokens[3]);

    player->spy(index, y, x, game.map, commandToPrint);
}
