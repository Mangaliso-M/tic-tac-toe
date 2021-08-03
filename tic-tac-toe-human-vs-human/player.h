/**
 * @file player.h
 * @author Mangaliso Mngomezulu (219030015@stu.ukzn.ac.za, mangalisommngomezulu@gmail.com)
           BSc Computer Science and Information Technology, University Of KwaZulu Natal
 * @brief 
 * @version 0.1
 * @date 2021-07-13
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef  PLAYER_H
#define PLAYER_H


#include <map>
#include <string>
#include "board.h"

using namespace std; 

class player{
    
    char myPiece;
    bool firstPlayer;

    map<string , bool> availableLocations; //string for location i.e aa, true if available false otherwise
    map<string , bool> availableWinningPatterns;//string for pattern, i.e aa-bb-cc, true if it can still win in the given situation, false ortherwise
    map<string , bool> myNextPlacementWins; //string for location, if the next move of the player wins, falgged as true, false otherwise
    map<string , bool> opponentNextPlacementWins; // string for location, if the opponent wins by making a placement to that location, falgged as true, false otherwise
    board * pBoard;
    
    public:
        
        player();

        char setMyPiece(char piece);
        char setFirstPlayer(char firstPlayer);

        bool initializeWinningPatterns(); //read the file and create a map with all the possible wiinning patterns
        bool updateWinningPatterns(); //each pattern consists of three marbles, if a foregin marble resides in on of the patterns 3 locations, the partten is nolonger available
        bool updateAvailableLocations(); //take the map from the board, use it to make the decision
        string choosePieceLocation(); //in the event of no possible winning patterns, or the first move
        
        bool updateMyWinningPlacements(); //update the map 
        bool updateOpponentsWinningPlacements(); //update the map 
        
        void printBoard(board *pBoard); 
        void play(); //weigh your options and make a move
        
};

#endif // ! PLAYER_H
