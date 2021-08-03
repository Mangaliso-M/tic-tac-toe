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
    int movesPlayed;

    map<string , bool> availableLocations; //string for location i.e aa, true if available false otherwise
    map<string , bool> availableWinningPatterns;//string for pattern, i.e aa-bb-cc, true if it can still win in the given situation, false ortherwise
    map<string, bool> nextPlacementWins; // locations for which the next placement wins, if its your turn, you win, else defense priority
   
    board * pBoard;
    
    public:
        
        player(board *boardObj);

        char setMyPiece(char piece);
        char setFirstPlayer(char firstPlayer);

        void initializeWinningPatterns(); //(done)read the file and create a map with all the possible wiinning patterns
        void updateWinningPatterns(); //(done)each pattern consists of three marbles, if a foregin marble resides in on of the patterns 3 locations, the partten is nolonger available
        void updateAvailableLocations(); //(done)take the map from the board, use it to make the decision
        string choosePieceLocation(); //(done)in the event of no possible winning patterns, or the first move
        
        string nextLocationPlacementWins(); //the location that will win the game for the next opponent
        
        void printBoard(); //(done)
        void play(); //(not done)weigh your options and make a move
        
};

#endif // ! PLAYER_H
