//
// Created by LioraPinkhasov on 20/05/2020.
//

#ifndef WATGAME_SOLDIER_HPP
#define WATGAME_SOLDIER_HPP
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
//#include "Board.hpp"
#include "utils.h"

using namespace std;

namespace WarGame {
class Board;

    class Soldier {


    public:
        //Position location;
        unsigned int playerNumber; // Who own me?
        enum class Type {
            FootSolider, FootCommander, Sniper, SniperCommander, Paramedic, ParamedicCommander
        };
        Type type;
        //initial health points
        static const int Damage;
        static const int InitialHealthPoints;
        int HP;

        //damage per activity

        ///// Methods /////
        protected:
        Soldier(int player);
        Soldier(int player, Type type, int HP);
        virtual void attack(std::vector<std::vector<Soldier*>> matrix) = 0;
        virtual void Heal(int health) = 0;// Uses special ability of the solider
    };
}
#endif //WATGAME_SOLDIER_HPP

/*
 *         protected: int PlayerNum;
                   pair<int,int> location;

        public: int life;
                int power;

                //geters
                void GetLifeData(int PlayerNum);
                void GetPowerData(int PlayerNum);

                //seters
                int SetLifeData(int PlayerNum, int Life);
                int SetPowerData(int PlayerNum, int Power);



 */