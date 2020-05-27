/**
  Demo for the war-game exercise.

  @author Oz Levi
  @since  2020-05
**/

#include <iostream>
#include "DemoGame.hpp"  

using namespace std;

int main() {
	WarGame::DemoGame demoGame;
	cout << "The winner is:\n " << demoGame.play() << endl;
    std::cout<<"Reach last line of main"<<endl;
    return 0;
}
