/**
 * Header file for the board of the war game.
 * 
 * You can copy this file to a new file called Board.hpp, and extend it as you like.
 * 
 * @author Oz Levi 
 * @author Erel Segal-Halevi
 * @since  2020-05
 */
#pragma once
#include <string>
#include <vector>
#include <stdexcept>
#include "Soldier.hpp"
#include "utils.h"


namespace WarGame {
    //class Soldier;// Forward decleration

    class Board {
  private:
    std::vector<std::vector<Soldier*>> matrix; // Vector matrix to find Locations in O(1)

  public:
    enum class MoveDIR { Up = 0, Down, Right, Left
    };

    Position dirs[4] =
    {
            {-1, 0},
            {1, 0},
            {0, 1},
            {0, -1},
    };
    Board() :matrix(8, std::vector<Soldier*>(8, nullptr)){}
    Board(uint numRows, uint numCols) :
            matrix(numRows, std::vector<Soldier*>(numCols, nullptr))
            {}

    // operator for putting soldiers on the game-board during initialization.
    WarGame::Soldier*& operator[](std::pair<int,int> location);
    
    // operator for reading which soldiers are on the game-board.
    WarGame::Soldier* operator[](std::pair<int,int> location) const;
    
    // The function "move" tries to move the soldier of player "player"
    //     from the "source" location to the "target" location,
    //     and activates the special ability of the soldier.
    // If the move is illegal, it throws "std::invalid_argument". 
    // Illegal moves include:
    //  * There is no soldier in the source location (i.e., the soldier pointer is null);
    //  * The soldier in the source location belongs to the other player.
    //  * There is already another soldier (of this or the other player) in the target location.
    // IMPLEMENTATION HINT: Do not write "if" conditions that depend on the type of soldier!
    // Your code should be generic. All handling of different types of soldiers 
    //      must be handled by polymorphism.
    void move(unsigned int player_number, std::pair<int,int> source, MoveDIR direction);

    // returns true iff the board contains one or more soldiers of the given player.
    bool has_soldiers(unsigned int player_number) const
    {

        int num_of_rows = matrix.size();
        int num_of_collumns = matrix[0].size();

        for( int r = 0 ; r < num_of_rows ; r++ )
        {
            for( int c = 0 ; c < num_of_collumns ; c++)
            {
                if(matrix[r][c] != nullptr) // If there is a Soldier on this  spot
                {
                   if(matrix[r][c]->playerNumber == player_number)
                       return true;
                }
            }
        }
        return false;
    }

    ~Board()
    {
        int num_of_rows = matrix.size();
        int num_of_collumns = matrix[0].size();

        for( int r = 0 ; r < num_of_rows ; r++ )
        {
         for( int c = 0 ; c < num_of_collumns ; c++)
         {
             if(matrix[r][c] != nullptr) // If there is a Soldier on this  spot ,  delete it.
             {
                 delete matrix[r][c];
             }
         }
        }

    }
};

}