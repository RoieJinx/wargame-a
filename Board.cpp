//
// Created by LioraPinkhasov on 20/05/2020.
//
#include "Board.hpp"

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
void WarGame::Board::move(unsigned int player_number, std::pair<int,int> source, MoveDIR direction)
{



    // 1. Check if there is a solider in the source location, and if the player own this solider
    //
    if((*(this))[source] == nullptr || (*(this))[source]->playerNumber != player_number )
        throw  std::invalid_argument("Invalid Argument!");
    Position after_move = (source + dirs[static_cast<int>(direction)]);

    /**
     * Check out of boundd after move
     * */

    // 2. Check if destination location is valid.
    if((*(this))[after_move] == nullptr)// If the pointer is free and do not contain a soldier.
    {
        // 3. Move the solider & Activate speacial ability
        std::swap((*(this))[after_move],(*(this))[source]);
        (*(this))[after_move]->attack(this,after_move); // Use attack
    }
    else
        {
        throw  std::invalid_argument("Invalid Argument!");
    }
}
// operator for putting soldiers on the game-board during initialization.
//board[{0,1}] = new FootSoldier(1);
WarGame::Soldier*& WarGame::Board::operator[](std::pair<int,int> location)
{
    return matrix[location.first][location.second];
}

// operator for reading which soldiers are on the game-board.
WarGame::Soldier*  WarGame::Board::operator[](std::pair<int,int> location) const
{
    return matrix[location.first][location.second];
}

