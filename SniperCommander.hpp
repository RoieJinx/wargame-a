#include <stdexcept>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "Soldier.hpp"

using namespace std;

class SniperCommander : public Soldier
{
public:
    //build a sniper
    SniperCommander(int t): Soldier(120,100,t,3,true){}


};