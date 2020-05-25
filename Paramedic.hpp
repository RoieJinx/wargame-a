#include <stdexcept>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "Soldier.hpp"

using namespace std;

class paramedic : public Soldier
{
public:
    //build a sniper
    paramedic(int t): Soldier(100,50,t,1,false){}


};