//
// Created by roie on 26/05/2020.
//
#include "doctest.h"
#include <stdbool.h>
#include "Board.hpp"
#include "FootCommander.hpp"
#include "FootSoldier.hpp"
#include "Paramedic.hpp"
#include "ParamedicCommander.hpp"
#include "Sniper.hpp"
#include "SniperCommander.hpp"
#include "Soldier.hpp"
#include <cassert>

using namespace WarGame;
 setGame1()
{
    Board board1 (4,4);
    //Player 1
            board1[{0,0}] = new FootSoldier(1);// FootSoldier
            board1[{0,1}] = new Sniper(1);// Sniper
            board1[{0,2}] = new SniperCommander(1)// SniperCommander
            board1[{0,3}] = new FootCommander(1);// FootCommander
    //Player 2
            board1[{3,0}] = new FootSoldier(1);// FootSoldier
            board1[{3,1}] = new Sniper(1);// Sniper
            board1[{3,2}] = new SniperCommander(1)// SniperCommander
            board1[{3,3}] = new FootCommander(1);// FootCommander
}

TEST_CASE("Out of bounds moves")
{
    Board board1 (4,4);
    //Player 1
    board1[{0,0}] = new FootSoldier(1);// FootSoldier
    board1[{0,1}] = new Sniper(1);// Sniper
    board1[{0,2}] = new SniperCommander(1)// SniperCommander
    board1[{0,3}] = new FootCommander(1);// FootCommander
    //Player 2
    board1[{3,0}] = new FootSoldier(1);// FootSoldier
    board1[{3,1}] = new Sniper(1);// Sniper
    board1[{3,2}] = new SniperCommander(1)// SniperCommander
    board1[{3,3}] = new FootCommander(1);// FootCommander

    //Destroy it all!
    delete board1;
}
    CHECK_TROWS(board1[{,}]);
    CHECK_NOTHROW();
}
TEST_CASE("Testing find nearest enemy soldier")
{
    CHECK();
}
TEST_CASE("Finding soldiers to heal")
{
    CHECK();
}
TEST_CASE("Testing regular soldiers")
{
    CHECK();
}
TEST_CASE("Testing Commanders")
{
    CHECK();
}
