
/**
 * @file main.cpp
 * @author Mangaliso Mngomezulu (219030015@stu.ukzn.ac.za, mangalisommngomezulu@gmail.com), 
           BSc Computer Science and Information Technology, University Of KwaZulu Natal
 * @brief 
 * @version 0.1
 * @date 2021-07-13
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include "board.h"
#include "player.h"

using namespace std;

int main()
{
 cout<<"\n############ Tic Tac Toe ############\n"<<endl;
 

 //for the delay
 auto start = std::chrono::system_clock::now();


 board bo;
 bo.toString();
 bo.displayStats();
 
 
  
 //create a board pointer and print the board
 board *boardPointer;
 boardPointer = &bo;

 player player1(boardPointer);

 //create artificial player(s) here.
 //player1.printBoard(); // the test has shown that the player can watch the game and see all changes that the board object makes public.
 
 

 char nextPiece='X';
 cout<<"First Player Piece: ";
 cin>>nextPiece;
 
 nextPiece = bo.decidePieceXO(nextPiece);


 while(true){ //gameover not having expected value!
    
    //set the piece of the player to be the next Piece, this player plays against itsself
    player1.setMyPiece(nextPiece);


    //delay
    std::this_thread::sleep_for(std::chrono::seconds(6));

    if(bo.verticalAndHorizontalWin() || bo.diagonalWin()){
       bo.toString();
       bo.displayStats();
       break;
    }
    

    string nextLocation;

    //player must choose thier next piece location here/ artificial player or real human
    nextLocation=player1.choosePieceLocation(); //test?
    cout<<"Next Piece Location: "<<nextLocation<<endl;
    //cin>>nextLocation; //remove for testing
    
    bo.placePieceAt(nextLocation, nextPiece);
    bo.toString();
    bo.displayStats();
    bo.verticalAndHorizontalWin();

    nextPiece = (nextPiece == 'X'? 'O':'X');
    //cout<<"oCout"<<bo.getOCount()<<endl;
 }
 
 //player1.printBoard();
  

  //for the delay time
 auto end = std::chrono::system_clock::now();

 return 0;
}
