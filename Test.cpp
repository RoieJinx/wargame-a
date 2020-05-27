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
 /*setGame1()
{
    Board board1 (4,4);
    //Player 1
            board1[{0,0}] = new FootSoldier(1);// FootSoldier
            board1[{0,1}] = new Sniper(1);// Sniper
            board1[{0,2}] = new SniperCommander(1);// SniperCommander
            board1[{0,3}] = new FootCommander(1);// FootCommander
    //Player 2
            board1[{3,0}] = new FootSoldier(2);// FootSoldier
            board1[{3,1}] = new Sniper(2);// Sniper
            board1[{3,2}] = new SniperCommander(2);// SniperCommander
            board1[{3,3}] = new FootCommander(2);// FootCommander
}*/

TEST_CASE("Out of bounds moves")
{
    Board board1(4, 4);
    //Player 1
    board1[{0, 0}] = new FootSoldier(1);// FootSoldier
    board1[{0, 1}] = new Sniper(1);// Sniper
    board1[{0, 2}] = new SniperCommander(1);// SniperCommander
    board1[{0, 3}] = new FootCommander(1);// FootCommander
    //Player 2
    board1[{3, 0}] = new FootSoldier(2);// FootSoldier
    board1[{3, 1}] = new Sniper(2);// Sniper
    board1[{3, 2}] = new SniperCommander(2);// SniperCommander
    board1[{3, 3}] = new FootCommander(2);// FootCommander



    //Out of bounds different soldiers

    CHECK_THROWS(board1.move(1, {0, 0}, Board::MoveDIR::Left));// Should Throw
    CHECK_THROWS(board1.move(1, {0, 1}, Board::MoveDIR::Down));// Should Throw
    CHECK_THROWS(board1.move(1, {0, 2}, Board::MoveDIR::Down));// Should Throw
    CHECK_THROWS(board1.move(1, {0, 3}, Board::MoveDIR::Right));// Should Throw
    //Walking Sniper legale moves up untill meet an enemy, then go left out of bound
    CHECK_NOTHROW(board1.move(1, {0, 1}, Board::MoveDIR::Up)); // Should not Throw 1,1 is free
    CHECK_NOTHROW(board1.move(1, {1, 1}, Board::MoveDIR::Up)); // Should not Throw 2,1 is free
    CHECK_THROWS(board1.move(1, {2, 1}, Board::MoveDIR::Up)); // Should Throw 1,3 is not free , and he supposed to stay here
    CHECK_NOTHROW(board1.move(1, {2, 1}, Board::MoveDIR::Left)); // Should not Throw 2,0 is free
    CHECK_THROWS(board1.move(1, {2, 0}, Board::MoveDIR::Left)); // Should Throw  going out of bound to 2,-1
    // Walking footCommander ligale moves up untill meet an enemy, then go right out of bound
    CHECK_NOTHROW(board1.move(1, {0, 3}, Board::MoveDIR::Up)); // Should not Throw 1,3 is free
    CHECK_NOTHROW(board1.move(1, {1, 3}, Board::MoveDIR::Up)); // Should not Throw 2,3 is free
    CHECK_THROWS(board1.move(1, {2, 3}, Board::MoveDIR::Up)); // Should Throw 3,3 is not free , and he supposed to stay here
    CHECK_THROWS(board1.move(1, {2, 3}, Board::MoveDIR::Right)); // Should Throw  going out of bound to 2,4
    // Walking with  foot soildier to until he cannot move any more
    CHECK_NOTHROW(board1.move(1, {0, 0}, Board::MoveDIR::Up)); // Should not Throw 1,0 is free
    CHECK_THROWS(board1.move(1, {1, 0},Board::MoveDIR::Up)); // Should Throw 2,0 is not free, ocupied by sniper, we should stay on 1,1
    CHECK_NOTHROW(board1.move(1, {1, 0}, Board::MoveDIR::Right)); // Should not Throw 1,1 is free
    CHECK_NOTHROW(board1.move(1, {1, 1}, Board::MoveDIR::Up)); // Should not Throw 2,1 is free
    CHECK_THROWS(board1.move(1, {2, 1}, Board::MoveDIR::Left)); // Should Throw 1,1 is  occupied by freindly soldier
    CHECK_THROWS(board1.move(1, {2, 1}, Board::MoveDIR::Up)); // Should  Throw 3,1 is occupied by enemy soldier
    CHECK_NOTHROW(board1.move(1, {2, 1}, Board::MoveDIR::Right)); // Should not Throw 2,2 is free
    CHECK_THROWS(board1.move(1, {2, 2}, Board::MoveDIR::Right)); // Should Throw 2,1 is occupied by freindly soldier
    CHECK_THROWS(board1.move(1, {2, 2}, Board::MoveDIR::Up)); // Should Throw 232 is occupied by enemy soldier
    //Destroy it all!

}
TEST_CASE("Testing find nearest enemy soldier on even board")
{
    Board board2 (4,4);// even n*n board
    // Player 1
    board2[{0,1}] = new FootSoldier(1);// FootSoldier
    // Player 2
    board2[{3,0}] = new FootSoldier(2);// FootSoldier
    board2[{3,3}] = new FootSoldier(2);// FootCommander
    // InitialHp check
    CHECK(board2[{3,0}]->HP == 100 );
    CHECK(board2[{3,3}]->HP == 100); // check enemy soldier initial health

    //first move up
    board2.move(1, {0,1}, Board::MoveDIR::Up);// Going to 1,1
            CHECK(board2[{3,0}]->HP == 90);// Should hit  3,0 with 10 dmg leaving it with 90
            CHECK(board2[{3,3}]->HP == 100);// Should not hit  3,3 with 10 dmg leaving it with 100
    // Second Move right
    board2.move(1, {1,1}, Board::MoveDIR::Right);// Going to 1,2
            CHECK(board2[{3,0}]->HP == 80);// Should hit  3,0 with 10 dmg leaving it with 80
            CHECK(board2[{3,3}]->HP == 100);// Should not hit  3,3 with 10 dmg leaving it with 100
    // THird Move right
    board2.move(1, {1,2}, Board::MoveDIR::Right);// Going to 1,3
            CHECK(board2[{3,0}]->HP == 80);// Should  not hit  3,0 with 10 dmg leaving it with 80
            CHECK(board2[{3,3}]->HP == 90);// Should  hit  3,3 with 10 dmg leaving it with 90

    CHECK_THROWS(board2.move(1, {1,3}, Board::MoveDIR::Right));// out of bounds right, should throw

            CHECK(board2[{3,0}]->HP == 80);// HP should not be effected cause an illigal move was made
            CHECK(board2[{3,3}]->HP == 90);// Should  hit  3,3 with 10 dmg leaving it with 90

    //Destroy it all
    /////////////////////////////////////////////////////////////////
    //delete board1;



    //Destroy it all


};

TEST_CASE("Testing find nearest enemy soldier on odd board")
{
    Board boardOdd (5,5);// Odd n*n board
    // Player 1
    boardOdd[{0,1}] = new FootSoldier(1);// FootSoldier
    // Player 2
    boardOdd[{4,0}] = new FootSoldier(2);// FootSoldier
    boardOdd[{4,4}] = new FootSoldier(2);// FootCommander
    // InitialHp check
            CHECK(boardOdd[{4,0}]->HP == 100 );
            CHECK(boardOdd[{4,4}]->HP == 100); // check enemy soldier initial health
    //first move up
    boardOdd.move(1, {0,1}, Board::MoveDIR::Up);// Going to 1,1
            CHECK(boardOdd[{4,0}]->HP == 90);// Should hit  3,0 with 10 dmg leaving it with 90
            CHECK(boardOdd[{4,4}]->HP == 100);// Should not hit  3,3 with 10 dmg leaving it with 100
    // Second Move right
    boardOdd.move(1, {1,1}, Board::MoveDIR::Right);// Going to 1,2 , this is middle ground , which one it should strike?

                  CHECK(boardOdd[{4,0}]->HP == 80);// Should hit  3,0 with 10 dmg leaving it with 80
                  CHECK(boardOdd[{4,4}]->HP == 100);// Should not hit  3,3 with 10 dmg leaving it with 100
// Or will it be
                CHECK(boardOdd[{4,0}]->HP == 90);// Should hit  3,0 with 10 dmg leaving it with 890
                CHECK(boardOdd[{4,4}]->HP == 90);// Should not hit  3,3 with 10 dmg leaving it with 100)


    // THird Move right
    boardOdd.move(1, {1,2}, Board::MoveDIR::Up);// Going to 1,3
            CHECK(boardOdd[{4,0}]->HP == 70);// Should  not hit  3,0 with 10 dmg leaving it with 80
            CHECK(boardOdd[{4,4}]->HP == 90);// Should  hit  3,3 with 10 dmg leaving it with 90

            CHECK(boardOdd[{4,0}]->HP == 90);// Should  not hit  3,0 with 10 dmg leaving it with 80
            CHECK(boardOdd[{4,4}]->HP == 80);// Should  hit  3,3 with 10 dmg leaving it with 90

};

/*
TEST_CASE("Finding soldiers to heal dammged by foorSoldier") {
    Board boardOfMedic1(5, 5);// Odd n*n board
    boardOfMedic1[{0, 2}] = new Paramedic(1);
    boardOfMedic1[{1, 2}] = new FootSoldier(1);
    boardOfMedic1[{4, 2}] = new FootSoldier(2);
    boardOfMedic1.move(2, {4, 2}, Board::MoveDIR::Down); // enemy soldier end up on 3,2
            CHECK(boardOfMedic1[{1, 2}]->HP == 90);
    cout<<"Error here1"<<endl;

    boardOfMedic1.move(1, {1, 2}, Board::MoveDIR::Up);// freindly soldier end up on 2,2
    cout<<"Error here2"<<endl;

    CHECK(boardOfMedic1[{3, 2}]->HP == 90);
    cout<<"Error here22"<<endl;

    boardOfMedic1.move(1, {0, 2}, Board::MoveDIR::Up); // end 1,2
    cout<<"Error here33"<<endl;

    CHECK(boardOfMedic1[{2, 2}]->HP == 100);
    //Now Medic moves to try and heal the enemy
    boardOfMedic1.move(1, {1, 2}, Board::MoveDIR::Left);
    cout<<"Error here3"<<endl;

    CHECK(boardOfMedic1[{3, 2}]->HP != 100);
    boardOfMedic1.move(1, {1, 1}, Board::MoveDIR::Up);
            CHECK(boardOfMedic1[{3, 2}]->HP != 100);
    boardOfMedic1.move(1, {2, 1}, Board::MoveDIR::Up);
            CHECK(boardOfMedic1[{3, 2}]->HP != 100);
    cout<<"Error here!"<<endl;

}

TEST_CASE("Finding soldiers to heal dammged by Sniper")
{
    Board boardOfMedic2 (5,5);// Odd n*n board
    boardOfMedic2[{0,2}] = new Paramedic(1);
    boardOfMedic2[{1,2}] = new Sniper(1);
    boardOfMedic2[{4,2}] = new Sniper(2);
    boardOfMedic2.move(2, {4,2}, Board::MoveDIR::Down);
            CHECK(boardOfMedic2[{1,2}]->HP != 90);
    boardOfMedic2.move(1, {1,2}, Board::MoveDIR::Up);
            CHECK(boardOfMedic2[{3,2}]->HP != 90);
    boardOfMedic2.move(1, {0,2}, Board::MoveDIR::Up);
            CHECK(boardOfMedic2[{2,2}]->HP == 100);
    //Now Medic moves to try and heal the enemy
    boardOfMedic2.move(1, {1,2}, Board::MoveDIR::Left);
            CHECK(boardOfMedic2[{3,2}]->HP != 100);
    boardOfMedic2.move(1, {1,1}, Board::MoveDIR::Up);
            CHECK(boardOfMedic2[{3,2}]->HP != 100);
    boardOfMedic2.move(1, {2,1}, Board::MoveDIR::Up);
            CHECK(boardOfMedic2[{3,2}]->HP != 100);


    //


    //CHECK();
}*/
TEST_CASE("Walking on the plane")
{

    Board boardWalk(10, 10);
    //Player 1
    boardWalk[{0, 0}] = new FootSoldier(1);// FootSoldier
    boardWalk[{0, 1}] = new Sniper(1);// Sniper
    boardWalk[{0, 2}] = new SniperCommander(1);// SniperCommander
    boardWalk[{0, 4}] = new Paramedic(1);// FootCommander
    boardWalk[{0, 5}] = new ParamedicCommander(1);// FootCommander
    boardWalk[{0, 6}] = new FootCommander(1);// FootCommander
    boardWalk[{0, 7}] = new FootCommander(1);// FootCommander
    boardWalk[{0, 8}] = new FootCommander(1);// FootCommander
    boardWalk[{0, 9}] = new FootCommander(1);// FootCommander
    // Every body step forward
    CHECK_NOTHROW(boardWalk.move(1, {0, 0}, Board::MoveDIR::Up)); // Should not Throw 1,0 is free
    CHECK_NOTHROW(boardWalk.move(1, {0, 1}, Board::MoveDIR::Up)); // Should not Throw 1,1 is free
    CHECK_NOTHROW(boardWalk.move(1, {0, 2}, Board::MoveDIR::Up)); // Should not Throw 1,2 is free
    CHECK_NOTHROW(boardWalk.move(1, {0, 3}, Board::MoveDIR::Up)); // Should not Throw 1,3 is free
    CHECK_NOTHROW(boardWalk.move(1, {0, 4}, Board::MoveDIR::Up)); // Should not Throw 1,4 is free
    CHECK_NOTHROW(boardWalk.move(1, {0, 5}, Board::MoveDIR::Up)); // Should not Throw 1,5 is free
    CHECK_NOTHROW(boardWalk.move(1, {0, 6}, Board::MoveDIR::Up)); // Should not Throw 1,6 is free
    CHECK_NOTHROW(boardWalk.move(1, {0, 7}, Board::MoveDIR::Up)); // Should not Throw 1,7 is free
    CHECK_NOTHROW(boardWalk.move(1, {0, 8}, Board::MoveDIR::Up)); // Should not Throw 1,8 is free
    CHECK_NOTHROW(boardWalk.move(1, {0, 9}, Board::MoveDIR::Up)); // Should not Throw 1,9 is free
    // Another step forward
    CHECK_NOTHROW(boardWalk.move(1, {1, 0}, Board::MoveDIR::Up)); // Should not Throw 2,0 is free
    CHECK_NOTHROW(boardWalk.move(1, {1, 1}, Board::MoveDIR::Up)); // Should not Throw 2,1 is free
    CHECK_NOTHROW(boardWalk.move(1, {1, 2}, Board::MoveDIR::Up)); // Should not Throw 2,2 is free
    CHECK_NOTHROW(boardWalk.move(1, {1, 3}, Board::MoveDIR::Up)); // Should not Throw 2,3 is free
    CHECK_NOTHROW(boardWalk.move(1, {1, 4}, Board::MoveDIR::Up)); // Should not Throw 2,4 is free
    CHECK_NOTHROW(boardWalk.move(1, {1, 5}, Board::MoveDIR::Up)); // Should not Throw 2,5 is free
    CHECK_NOTHROW(boardWalk.move(1, {1, 6}, Board::MoveDIR::Up)); // Should not Throw 2,6 is free
    CHECK_NOTHROW(boardWalk.move(1, {1, 7}, Board::MoveDIR::Up)); // Should not Throw 2,7 is free
    CHECK_NOTHROW(boardWalk.move(1, {1, 8}, Board::MoveDIR::Up)); // Should not Throw 2,8 is free
    CHECK_NOTHROW(boardWalk.move(1, {1, 9}, Board::MoveDIR::Up)); // Should not Throw 2,9 is free
    // Another step forward
    CHECK_NOTHROW(boardWalk.move(1, {2, 0}, Board::MoveDIR::Up)); // Should not Throw 3,0 is free
    CHECK_NOTHROW(boardWalk.move(1, {2, 1}, Board::MoveDIR::Up)); // Should not Throw 3,1 is free
    CHECK_NOTHROW(boardWalk.move(1, {2, 2}, Board::MoveDIR::Up)); // Should not Throw 3,2 is free
    CHECK_NOTHROW(boardWalk.move(1, {2, 3}, Board::MoveDIR::Up)); // Should not Throw 3,3 is free
    CHECK_NOTHROW(boardWalk.move(1, {2, 4}, Board::MoveDIR::Up)); // Should not Throw 3,4 is free
    CHECK_NOTHROW(boardWalk.move(1, {2, 5}, Board::MoveDIR::Up)); // Should not Throw 3,5 is free
    CHECK_NOTHROW(boardWalk.move(1, {2, 6}, Board::MoveDIR::Up)); // Should not Throw 3,6 is free
    CHECK_NOTHROW(boardWalk.move(1, {2, 7}, Board::MoveDIR::Up)); // Should not Throw 3,7 is free
    CHECK_NOTHROW(boardWalk.move(1, {2, 8}, Board::MoveDIR::Up)); // Should not Throw 3,8 is free
    CHECK_NOTHROW(boardWalk.move(1, {2, 9}, Board::MoveDIR::Up)); // Should not Throw 3,9 is free
    // Another step forward
    CHECK_NOTHROW(boardWalk.move(1, {3, 0}, Board::MoveDIR::Up)); // Should not Throw 4,0 is free
    CHECK_NOTHROW(boardWalk.move(1, {3, 1}, Board::MoveDIR::Up)); // Should not Throw 4,1 is free
    CHECK_NOTHROW(boardWalk.move(1, {3, 2}, Board::MoveDIR::Up)); // Should not Throw 4,2 is free
    CHECK_NOTHROW(boardWalk.move(1, {3, 3}, Board::MoveDIR::Up)); // Should not Throw 4,3 is free
    CHECK_NOTHROW(boardWalk.move(1, {3, 4}, Board::MoveDIR::Up)); // Should not Throw 4,4 is free
    CHECK_NOTHROW(boardWalk.move(1, {3, 5}, Board::MoveDIR::Up)); // Should not Throw 4,5 is free
    CHECK_NOTHROW(boardWalk.move(1, {3, 6}, Board::MoveDIR::Up)); // Should not Throw 4,6 is free
    CHECK_NOTHROW(boardWalk.move(1, {3, 7}, Board::MoveDIR::Up)); // Should not Throw 4,7 is free
    CHECK_NOTHROW(boardWalk.move(1, {3, 8}, Board::MoveDIR::Up)); // Should not Throw 4,8 is free
    CHECK_NOTHROW(boardWalk.move(1, {3, 9}, Board::MoveDIR::Up)); // Should not Throw 4,9 is free
    // Another step forward
    CHECK_NOTHROW(boardWalk.move(1, {4, 0}, Board::MoveDIR::Up)); // Should not Throw 5,0 is free
    CHECK_NOTHROW(boardWalk.move(1, {4, 1}, Board::MoveDIR::Up)); // Should not Throw 5,1 is free
    CHECK_NOTHROW(boardWalk.move(1, {4, 2}, Board::MoveDIR::Up)); // Should not Throw 5,2 is free
    CHECK_NOTHROW(boardWalk.move(1, {4, 3}, Board::MoveDIR::Up)); // Should not Throw 5,3 is free
    CHECK_NOTHROW(boardWalk.move(1, {4, 4}, Board::MoveDIR::Up)); // Should not Throw 5,4 is free
    CHECK_NOTHROW(boardWalk.move(1, {4, 5}, Board::MoveDIR::Up)); // Should not Throw 5,5 is free
    CHECK_NOTHROW(boardWalk.move(1, {4, 6}, Board::MoveDIR::Up)); // Should not Throw 5,6 is free
    CHECK_NOTHROW(boardWalk.move(1, {4, 7}, Board::MoveDIR::Up)); // Should not Throw 5,7 is free
    CHECK_NOTHROW(boardWalk.move(1, {4, 8}, Board::MoveDIR::Up)); // Should not Throw 5,8 is free
    CHECK_NOTHROW(boardWalk.move(1, {4, 9}, Board::MoveDIR::Up)); // Should not Throw 5,9 is free
    // Another step forward
    CHECK_NOTHROW(boardWalk.move(1, {5, 0}, Board::MoveDIR::Up)); // Should not Throw 6,0 is free
    CHECK_NOTHROW(boardWalk.move(1, {5, 1}, Board::MoveDIR::Up)); // Should not Throw 6,1 is free
    CHECK_NOTHROW(boardWalk.move(1, {5, 2}, Board::MoveDIR::Up)); // Should not Throw 6,2 is free
    CHECK_NOTHROW(boardWalk.move(1, {5, 3}, Board::MoveDIR::Up)); // Should not Throw 6,3 is free
    CHECK_NOTHROW(boardWalk.move(1, {5, 4}, Board::MoveDIR::Up)); // Should not Throw 6,4 is free
    CHECK_NOTHROW(boardWalk.move(1, {5, 5}, Board::MoveDIR::Up)); // Should not Throw 6,5 is free
    CHECK_NOTHROW(boardWalk.move(1, {5, 6}, Board::MoveDIR::Up)); // Should not Throw 6,6 is free
    CHECK_NOTHROW(boardWalk.move(1, {5, 7}, Board::MoveDIR::Up)); // Should not Throw 6,7 is free
    CHECK_NOTHROW(boardWalk.move(1, {5, 8}, Board::MoveDIR::Up)); // Should not Throw 6,8 is free
    CHECK_NOTHROW(boardWalk.move(1, {5, 9}, Board::MoveDIR::Up)); // Should not Throw 6,9 is free

    // Another step forward
    CHECK_NOTHROW(boardWalk.move(1, {6, 0}, Board::MoveDIR::Up)); // Should not Throw 7,0 is free
    CHECK_NOTHROW(boardWalk.move(1, {6, 1}, Board::MoveDIR::Up)); // Should not Throw 7,1 is free
    CHECK_NOTHROW(boardWalk.move(1, {6, 2}, Board::MoveDIR::Up)); // Should not Throw 7,2 is free
    CHECK_NOTHROW(boardWalk.move(1, {6, 3}, Board::MoveDIR::Up)); // Should not Throw 7,3 is free
    CHECK_NOTHROW(boardWalk.move(1, {6, 4}, Board::MoveDIR::Up)); // Should not Throw 7,4 is free
    CHECK_NOTHROW(boardWalk.move(1, {6, 5}, Board::MoveDIR::Up)); // Should not Throw 7,5 is free
    CHECK_NOTHROW(boardWalk.move(1, {6, 6}, Board::MoveDIR::Up)); // Should not Throw 7,6 is free
    CHECK_NOTHROW(boardWalk.move(1, {6, 7}, Board::MoveDIR::Up)); // Should not Throw 7,7 is free
    CHECK_NOTHROW(boardWalk.move(1, {6, 8}, Board::MoveDIR::Up)); // Should not Throw 7,8 is free
    CHECK_NOTHROW(boardWalk.move(1, {6, 9}, Board::MoveDIR::Up)); // Should not Throw 7,9 is free

    // Another step forward
    CHECK_NOTHROW(boardWalk.move(1, {7, 0}, Board::MoveDIR::Up)); // Should not Throw 8,0 is free
    CHECK_NOTHROW(boardWalk.move(1, {7, 1}, Board::MoveDIR::Up)); // Should not Throw 8,1 is free
    CHECK_NOTHROW(boardWalk.move(1, {7, 2}, Board::MoveDIR::Up)); // Should not Throw 8,2 is free
    CHECK_NOTHROW(boardWalk.move(1, {7, 3}, Board::MoveDIR::Up)); // Should not Throw 8,3 is free
    CHECK_NOTHROW(boardWalk.move(1, {7, 4}, Board::MoveDIR::Up)); // Should not Throw 8,4 is free
    CHECK_NOTHROW(boardWalk.move(1, {7, 5}, Board::MoveDIR::Up)); // Should not Throw 8,5 is free
    CHECK_NOTHROW(boardWalk.move(1, {7, 6}, Board::MoveDIR::Up)); // Should not Throw 8,6 is free
    CHECK_NOTHROW(boardWalk.move(1, {7, 7}, Board::MoveDIR::Up)); // Should not Throw 8,7 is free
    CHECK_NOTHROW(boardWalk.move(1, {7, 8}, Board::MoveDIR::Up)); // Should not Throw 8,8 is free
    CHECK_NOTHROW(boardWalk.move(1, {7, 9}, Board::MoveDIR::Up)); // Should not Throw 8,9 is free

    // Another step forward
    CHECK_NOTHROW(boardWalk.move(1, {8, 0}, Board::MoveDIR::Up)); // Should not Throw 9,0 is free
    CHECK_NOTHROW(boardWalk.move(1, {8, 1}, Board::MoveDIR::Up)); // Should not Throw 9,1 is free
    CHECK_NOTHROW(boardWalk.move(1, {8, 2}, Board::MoveDIR::Up)); // Should not Throw 9,2 is free
    CHECK_NOTHROW(boardWalk.move(1, {8, 3}, Board::MoveDIR::Up)); // Should not Throw 9,3 is free
    CHECK_NOTHROW(boardWalk.move(1, {8, 4}, Board::MoveDIR::Up)); // Should not Throw 9,4 is free
    CHECK_NOTHROW(boardWalk.move(1, {8, 5}, Board::MoveDIR::Up)); // Should not Throw 9,5 is free
    CHECK_NOTHROW(boardWalk.move(1, {8, 6}, Board::MoveDIR::Up)); // Should not Throw 9,6 is free
    CHECK_NOTHROW(boardWalk.move(1, {8, 7}, Board::MoveDIR::Up)); // Should not Throw 9,7 is free
    CHECK_NOTHROW(boardWalk.move(1, {8, 8}, Board::MoveDIR::Up)); // Should not Throw 9,8 is free
    CHECK_NOTHROW(boardWalk.move(1, {8, 9}, Board::MoveDIR::Up)); // Should not Throw 9,9 is free
    // Last move out of bounds
    CHECK_THROWS(boardWalk.move(1, {7, 0}, Board::MoveDIR::Up)); // Should not Throw 8,0 is free
    CHECK_THROWS(boardWalk.move(1, {7, 1}, Board::MoveDIR::Up)); // Should not Throw 8,1 is free
    CHECK_THROWS(boardWalk.move(1, {7, 2}, Board::MoveDIR::Up)); // Should not Throw 8,2 is free
    CHECK_THROWS(boardWalk.move(1, {7, 3}, Board::MoveDIR::Up)); // Should not Throw 8,3 is free
    CHECK_THROWS(boardWalk.move(1, {7, 4}, Board::MoveDIR::Up)); // Should not Throw 8,4 is free
    CHECK_THROWS(boardWalk.move(1, {7, 5}, Board::MoveDIR::Up)); // Should not Throw 8,5 is free
    CHECK_THROWS(boardWalk.move(1, {7, 6}, Board::MoveDIR::Up)); // Should not Throw 8,6 is free
    CHECK_THROWS(boardWalk.move(1, {7, 7}, Board::MoveDIR::Up)); // Should not Throw 8,7 is free
    CHECK_THROWS(boardWalk.move(1, {7, 8}, Board::MoveDIR::Up)); // Should not Throw 8,8 is free
    CHECK_THROWS(boardWalk.move(1, {7, 9}, Board::MoveDIR::Up)); // Should not Throw 8,9 is free



}
/*

TEST_CASE("Testing regular soldiers")
{
    //CHECK();
}
TEST_CASE("Testing Commanders")
{
    //CHECK();
}
TEST_CASE("Full game demo")
{
           // CHECK();
}

     */
