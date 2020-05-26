//
// Created by LioraPinkhasov on 20/05/2020.
//

#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "Soldier.hpp"

using namespace std;
//using namespace Soldier;


/**
 * Position location;
        Board *board;
        unsigned int playerNumber; // Who own me?
        enum class Type {
            FootSolider, FootSoliderCommander, Sniper, SniperCommander, Paramedic, ParamedicCommander
        };
        Type type;
        //initial health points
        static const int InitialHealthPoints;
        int HP;
 */
using namespace WarGame;
Soldier::Soldier(int player)
{
    cout<< "Solider Built1" << endl;

}
Soldier::Soldier(int player, Type type, int HP) : playerNumber(player), type(type), HP(HP)
{
    cout<< "Solider Built2" << endl;
}

