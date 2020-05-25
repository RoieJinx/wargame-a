//
// Created by LioraPinkhasov on 20/05/2020.
//

#ifndef WATGAME_PARAMEDICCOMMANDER_HPP
#define WATGAME_PARAMEDICCOMMANDER_HPP


#include <stdexcept>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "Soldier.hpp"

using namespace std;

class ParamedicCommander : public Soldier
{
public:
    //build a sniper
    ParamedicCommander(int t): Soldier(200,100,t,3,true){}


};


#endif //WATGAME_PARAMEDICCOMMANDER_HPP
