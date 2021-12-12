cmake_minimum_required(VERSION 3.20)
project(BShips)

set(CMAKE_CXX_STANDARD 11)

add_executable(BShips main.cpp Player.cpp Player.h BattleshipGame.cpp BattleshipGame.h CommandsHandler.cpp CommandsHandler.h Tokens.cpp Tokens.h Map.cpp Map.h Ship.cpp Ship.h Carrier.cpp Carrier.h Destroyer.cpp Destroyer.h Cruiser.cpp Cruiser.h Battleship.cpp Segment.h utils.h Segment.cpp Battleship.h Canon.cpp Canon.h Radar.cpp Radar.h Engine.cpp Engine.h)
