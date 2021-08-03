/**
 * @file player.cpp
 * @author Mangaliso Mngomezulu (219030015@stu.ukzn.ac.za/mangalisommngomezulu@gmail.com), 
           BSc Computer Science and Information Technology, University Of KwaZulu Natal
 * @brief 
 * @version 0.1
 * @date 2021-07-13
 * 
 * @copyright Copyright (c) 2021
 * 
*/


#include "player.h"

/**
 * @brief Construct a new player::player object, pass a board object to the player, link the player with the board
 * 
 */
player::player(board boardObj){

    //initialise the board pointer here 
    //use its map to populate the maps for the player as needed
}



void player::printBoard(board *pBoard){

    (*pBoard).toString();

}