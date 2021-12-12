//
// Created by Kacper on 22.11.2021.
//


#ifndef BSHIPS_COMMANDSHANDLER_H
#define BSHIPS_COMMANDSHANDLER_H


#include "BattleshipGame.h"
#include "Tokens.h"
#include "utils.h"


class CommandsHandler {
public:
    Groups currentGroup;
    char currentCommand[MAX_COMMAND_LENGTH];
    char commandToPrint[MAX_COMMAND_LENGTH];
    BattleshipGame game;
    Tokens tokens;
    bool initState;
    bool extendedBehavior;

    CommandsHandler();

    void handleCommand();

    void handleNonEntryCommand();

    void handleStateEntry();

    void handlePlayerEntry(Groups playerGroup);

    void handleStateCommands();

    void handlePlayerCommand(Player *player);

    void handlePrint();

    void handleSetFleet();

    void handleNextPlayer();

    void handleBoardSize();

    void handleReef();

    void handleInitPosition();

    void handleShip();

    void handleSave() const;

    void saveShip(char **saveStatement, int *statementCounter, Ship *ships, int length, int shipsCount,
                  ShipClass shipClass) const;


    void handleShoot(Player *player);

    void handlePlaceShip(Player *player);

    void handleMove(Player *player);

    void handleSpy(Player *player);

    void checkInitState();

    static int *getShipsCount(char **tokens);

    ShipClass getShipClass(char *toks) const;

    Direction getDirection(char token);

    MoveDirection getMoveDirection(char token);

    static int *getSegments(char *toks);
};


#endif //BSHIPS_COMMANDSHANDLER_H
