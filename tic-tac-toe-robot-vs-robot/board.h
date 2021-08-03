/**
 * @file board.h
 * @author Mangaliso Mngomezulu (219030015@stu.ukzn.ac.za, mangalisommngomezulu@gmail.com), 
           BSc Computer Science and Information Technology, University Of KwaZulu Natal
 * @brief 
 * @version 0.1
 * @date 2021-07-13
 * 
 * @copyright Copyright (c) 2021
 * 
*/

#ifndef BOARD_HEADER
#define BOARD_HEADER

#include <string>
#include <sstream>
#include <map>

using namespace std;

class board{

    char pieces[3][3]=  {{'?','?','?'},
                        {'?','?','?'},
                        {'?','?','?'}};; //an array to keep the pieces used in the game

    char aa, ab, ac, ba, bb, bc, ca, cb, cc; // each piece has a unique location
    char lastPlayed; //either X or an O, only updates with a valid play, initially a '?'
    char firstPlayer; //either X or an O, initially '?'
    int  piecesOnTheBoard; //a count of the pieces on the board

    int xCount; //a count of the Xs on the board
    int oCount; //a count of the Os on the board
    map<string,char> piecesMap; //a location is mapped to a piece on the board
    stringstream winReason; //which player won and what is the identified winning pattern, i.e diagonal aa-bb-cc, player X


    public:
        bool gameOver; //false while no one has won
        board(); //create a board with the pieces initialized to ?
       // ~board(); //board object desstructor
        //bool gameToStillContinue(); //true if no one has won yet, false otherwise
        char placePieceAt(string location, char piece); //locations are passed here and a piece that is to play is put at that location
        char getFirstPlayerPiece(char firstPlayerPiece); //first player will be asked their piece of choice, we only ask the players once and only the first player is asked.
        void toString();
        void displayStats();
        bool locationAvailable(string desiredLocation, char piece);
        bool myTurn(char prev, char now);
        bool verticalAndHorizontalWin();
        bool diagonalWin();
        char decidePieceXO(char  playerChoice);
        string stateWinReason(char winnerChar, char locationFirstChar, int rowOrCol, bool horizontal, bool vertical, bool diagonal);
        
        //getters
        int getOCount();
        map<string,char> getPiecesMap();
};

#endif