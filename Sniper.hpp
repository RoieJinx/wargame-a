#ifndef WATGAME_SOLDIER_SNIPER_HPP
#define WATGAME_SOLDIER_SNIPER_HPP

#include <stdexcept>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "Soldier.hpp"

using namespace std;

class Sniper : public Soldier
{
public:
    //build a sniper
    Sniper(int t): Soldier(100,50,t,2,false){}


};

#endif