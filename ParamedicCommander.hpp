#pragma once

#include <stdexcept>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "Soldier.hpp"

/**
 * FootSoldier: initial health points=100, damage per activity=10.
 *FootSoldier - רגלי - יכול ללכת משבצת אחת לכל כיוון. יורה על החייל של האויב שנמצא הכי קרוב אליו (אם יש כמה - הוא יורה על אחד מהם שרירותית)
 *
 */

using namespace std;
namespace WarGame{
    class ParamedicCommander : public Soldier
    {
        static const int Damage = 0;
        static const int MAX_HP = 200;

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
    public:
        ParamedicCommander(int player) : Soldier(player, Type::ParamedicCommander, MAX_HP)
        {
            cout << "  con ParamedicCommander1" << endl;
        }

        void Heal(int hp)
        {
            HP = (HP + hp) % (MAX_HP + 1);
        }

        void attack(std::vector<std::vector<Soldier*>> matrix,std::pair<int,int> sLocation)
        {
            //findEnemy()


        }


    };
}