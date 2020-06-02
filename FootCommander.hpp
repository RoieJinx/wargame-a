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
    class FootCommander: public Soldier
    {
        static const int Damage = 20;
        static const int MAX_HP = 150;

       // FootCommander: initial health points=150, damage per activity=20.

    public:
        FootCommander(int player) : Soldier(player, Type::FootCommander, MAX_HP)
        {
            cout << "  con FootCommander1" << endl;
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