
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
#include "board.h"

using namespace std;

int main()
{
 cout<<"\n############ Tic Tac Toe ############\n"<<endl;

 board bo;
 bo.toString();
 bo.displayStats();
 
 
 

 char nextPiece='X';
 cout<<"First Player Piece: ";
 cin>>nextPiece;
 
 nextPiece = bo.decidePieceXO(nextPiece);


 while(true){ //gameover not having expected value!
    
    if(bo.verticalAndHorizontalWin() || bo.diagonalWin()){
       bo.toString();
       bo.displayStats();
       break;
    }
    

    string nextLocation;

    //player must choose thier next piece location here/ artificial player or real human
    cout<<"Next Piece Location: ";
    cin>>nextLocation;
    
    bo.placePieceAt(nextLocation, nextPiece);
    bo.toString();
    bo.displayStats();
    bo.verticalAndHorizontalWin();

    nextPiece = (nextPiece == 'X'? 'O':'X');
   
 }
 
 return 0;
}
