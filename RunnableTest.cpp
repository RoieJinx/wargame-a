//
// Created by roie on 25/05/2020.
#include "Board.hpp"
#include "Soldier.hpp"
#include "FootSoldier.hpp"

using namespace WarGame;
int main()
{
    cout << "Enter test" << endl;
    Board gameBoard;
    gameBoard[{0,0}] = new FootSoldier(1);
    cout<< "1 has soliders? "<< gameBoard.has_soldiers() << endl;
    cout << "End Test" << endl;
    return 0;

}

//

