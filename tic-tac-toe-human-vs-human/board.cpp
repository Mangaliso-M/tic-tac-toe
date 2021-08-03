/**
 * @file board.cpp
 * @author Mangaliso Mngomezulu (219030015@stu.ukzn.ac.za, mangalisommngomezulu@gmail.com),
           BSc Computer Science and Information Technology, University Of KwaZulu Natal
 * @brief  
 * @version 0.1
 * @date 2021-07-13
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "board.h"
#include <iostream>
#include <cstring>
#include <sstream>

using namespace std;

/**
 * @brief Construct a new board::board object
 * 
 */

board::board(){

     //an array to keep the pieces used in the game

    lastPlayed = '?'; //either X or an O, only updates with a valid play
    firstPlayer = '?'; //either X or an O
    piecesOnTheBoard = 0; //a count of the pieces on the board
    gameOver = false; //false while no one has won
    xCount = 0; //a count of the Xs on the board
    oCount = 0; //a count of the Os on the board
    

    /**
     * @brief initialize the map such that all locations are mapped to the initial piece '?'
     * 
     */
    string locations[9] = {"aa", "ab", "ac", "ba", "bb", "bc", "ca", "cb", "cc"};
    for (int i = 0; i < 9; i ++){
        piecesMap[locations[i]]='?';
        //cout<<"Mapped: "<<locations[i]<<" to "<<" ?"<<endl;
    }
    
    //initialize the pieces, done explicitly, THERE IS ROOM FOR IMPROVEMENT
    for(int i = 0; i < 3; i ++){
        for(int j = 0; j < 3; j ++){
            if(i == 0){
                if(j == 0)
                    aa=pieces[i][j];
                else if(j == 1)
                    ab=pieces[i][j];
                else if(j == 2)
                    ac=pieces[i][j];
            }
            if(i == 1){
                if(j == 0)
                    ba=pieces[i][j];
                else if(j == 1)
                    bb=pieces[i][j];
                else if(j == 2)
                    bc=pieces[i][j];
            }
            if(i ==2){
                if(j == 0)
                    ca=pieces[i][j];
                else if(j == 1)
                    cb=pieces[i][j];
                else if(j == 2)
                    cc=pieces[i][j];
            }
        }
    }
}

/**
 * @brief display the board's current state and the guide on how to place the pieces.
 *        
 */

void board::toString(){
    
    string locationsArray[3][3] = { //this is just the guide, we donot have to read from the original map
                                   {"aa","ab","ac"},
                                   {"ba","bb","bc"},
                                   {"ca","cb","cc"}
                                   };
    cout<<"\nCurrent Board State          Piece Location Guide"<<endl<<endl;
    for(int i=0; i < 3; i++){
             cout<<"("<<pieces[i][0]<<")--("<<pieces[i][1]<<")--("<<pieces[i][2]<<")                "<<"("<<locationsArray[i][0]<<")--("<<locationsArray[i][1]<<")--("<<locationsArray[i][2]<<")"<<endl;
             
             if(i < 2)
                cout<<" |"<<"    "<<"|"<<"    "<<"|"<<"                  |"<<"    "<<" |"<<"    "<<" |"<<endl;  
    }
    cout<<endl;
}  

/**
 * @brief update and display the game stats
 * 
 */

void board::displayStats(){
    
    char nextPlayer = lastPlayed; //decide just below
    if(lastPlayed != '?'){
      nextPlayer = (lastPlayed == 'X'? 'O': 'X');
    }else{
        nextPlayer = '?';
    }
    cout<<"Next Player    : "<<nextPlayer<<endl;   
    cout<<"Game continues? "<<(gameOver == false? "Yes": "No")<<endl; 
    cout<<"X Piece Count  : "<<xCount<<endl; 
    cout<<"O Piece Count  : "<<oCount<<endl; 
    cout<<"Total Pieces   : "<<piecesOnTheBoard<<endl;
    cout<<"First Player   : "<<firstPlayer<<endl;
    cout<<"\n"<<endl;
    
}

/**
 * @brief place piece at desired location.
 * 
 * @param location  piece location, aa, bb, ab, etc.
 * @param piece the char piece to be put on the location
 * @return char 
 */

char board::placePieceAt(string location, char piece){
    
    string desiredLocation = location;

    if(location == "aa"){
       if(locationAvailable(desiredLocation, piece))
         pieces[0][0] = piece;
    }
    else if(location == "ab"){
        if(locationAvailable(desiredLocation, piece))
         pieces[0][1] = piece;
    }
    else if(location == "ac"){
        if(locationAvailable(desiredLocation, piece))
         pieces[0][2] = piece;
    }
    else if(location == "ba"){
        if(locationAvailable(desiredLocation, piece))
         pieces[1][0] = piece;
    }
    else if(location == "bb"){
        if(locationAvailable(desiredLocation, piece))
         pieces[1][1] = piece;
    }
    else if(location == "bc"){
        if(locationAvailable(desiredLocation, piece))
         pieces[1][2] = piece;
    }
    else if(location == "ca"){
        if(locationAvailable(desiredLocation, piece))
         pieces[2][0] = piece;
    }
    else if(location == "cb"){
        if(locationAvailable(desiredLocation, piece))
         pieces[2][1] = piece;
    }
    else if(location == "cc"){
        if(locationAvailable(desiredLocation, piece))
         pieces[2][2] = piece;
    }
    else{
        //give them infinitely many chances to fool around ('_')

        string locationTry ="";
        cout<<"\nInvalid location, please refer to location guide on the right handside of the actual board"<<endl;
        cout<<"Enter desired location again: ";
        cin>>locationTry;

        if(locationTry[0] < 'a' || locationTry[1] > 'c'){
            while(locationTry[0] < 'a' || locationTry[1] > 'c'){
                cout<<"\nInvalid location, please refer to location guide on the right handside of the actual board"<<endl;
                cout<<"Enter desired location again: ";
                cin>>locationTry;
            }
        }
        location = locationTry;
        
        placePieceAt(location,piece); //recursive!

    }
    return piece; //???????    
}

/**
 * @brief if the game is not over, if its the current players turn, if the chosen location is not occupied, place a piece in the location
 *         , update the map and game stats
 * 
 * @param desiredLocation the location in the form aa, ab, ac, ba, bb, bc, ca, cb, cc etc.
 * @param piece 
 * @return true 
 * @return false 
 */
 
bool board::locationAvailable(string desiredLocation, char piece){
  
  if(!gameOver){
     
        if(piecesMap[desiredLocation] == '?'){
            
            if(myTurn(lastPlayed, piece)){
                    
                    piecesMap[desiredLocation] = piece;

                    lastPlayed = piece;
                    piecesOnTheBoard ++;
                    
                     //TO-DO!! check if anyone has won after this point
                     /**
                      * @brief Check if we have a new winner
                      * 
                      */

                    if(piecesOnTheBoard == 9){
                        gameOver = true;
                    }
                    //first player or nth Player?
                    if(piecesOnTheBoard == 1){
                        firstPlayer = piece;
                    }

                    //X or O?
                    if(piece == 'X' || piece == 'x')
                        xCount++;
                    else if(piece == 'O' || piece == 'o' || piece =='0') //accidentally enters a 0? no problem
                        oCount++;
                    else{
                        cout<<"Unexpected piece played!"<<endl;
                        return false;
                    }
                    return true;
            }
            else{ //not possible since the game chooses the piece afer the first put.
                cout<<"Its not your turn, player "<<piece<<endl;
                return false;
            }
        }
        else if(piecesMap[desiredLocation] != '?'){
            cout<<desiredLocation<<" is already occupied!"<<endl;
            return false;
        }
  }
  else{
      cout<<"GAME OVER!!"<<endl;
      return false;
  }
  return false;
}

/**
 * @brief check if the player attempting to play is actually the one to be playing.
 * 
 * @param prev the last valid player
 * @param now the current attempting player
 * @return true  if prev and now are different
 * @return false if pre == now
 */

bool board::myTurn(char prev, char now){
    
    return prev != now;
}

/**
 * @brief Check if one player wins 
 * Possible ways to win: 
 * aa-ab-ac
 * aa-ba-ca
 * aa-bb-cc diagonal (catered for in a different method)
 * ba-bb-bc
 * ca-cb-cc
 * ca-bb-ac diagonal (catered for in another method)
 * ab-bb-cb
 * ac-bc-cc
 */

/**
 * @brief check if there is a win from the horizontal and vertical perspectives
 * 
 * @return true  if 3 pieces in a row or column are the same
 * @return false  otherwise
 */
bool board::verticalAndHorizontalWin(){
    
    char horizontalBeginner = pieces[0][0];
    char verticalBeginner = pieces[0][0];
    char locationFirstChar = 'a'; //just a default
    char locationSecondChar = 'a'; //default

    //for each of the 3 rows, loop in each row to find possible winner
    for(int i = 0; i < 3; i++){
        horizontalBeginner = pieces[i][0];
        verticalBeginner = pieces[0][i];
       
        if(horizontalBeginner != '?'){
            
            //horizontal win
            if(horizontalBeginner == pieces[i][1] && horizontalBeginner == pieces[i][2]){

                //we need the first char of the location to make an informative reason
                if(i == 0){
                    locationFirstChar = 'a';
                }
                else if( i == 1){
                    locationFirstChar = 'b';
                }
                else locationFirstChar = 'c';
                
                //call the win describer method
                string winDescription = stateWinReason(horizontalBeginner,locationFirstChar,i,true,false, false);
                cout<<winDescription<<endl;

                gameOver = true;
                return true;
            }
        }
        
        if(verticalBeginner != '?'){ 
            
            //vertical win
            if(verticalBeginner == pieces[1][i] && verticalBeginner == pieces[2][i]){
                
                //locationFirstChar is always a, so we are concerned by about the second char
                if(i == 0){
                    locationSecondChar = 'a'; // the second one, i.e in aa, it's a in ac it's c
                }
                else if( i == 1){
                    locationSecondChar = 'b';
                }
                else locationSecondChar = 'c';
            
                //call the win describer method
                string winDescription = stateWinReason(verticalBeginner,locationSecondChar,i,false,true, false);
                cout<<winDescription<<endl;

                gameOver = true;
                return true;
            }     
        }
    }
    return false;
}

/**
 * @brief use the pieceLocation and piece map to check if there has been a diagonal winner
 *        possible diagonal wins: aa-bb-cc and ca-bb-ac only!
 * @return true if one of the winning patterns is detected.
 * @return false  if none of the winning parttens are detected.
 */

bool board::diagonalWin(){
   
    char locationFirstChar = 'a'; //just a default

   if(piecesMap["aa"] != '?'){ //if not empty
        if(piecesMap["aa"] == piecesMap["bb"] && piecesMap["bb"] ==  piecesMap["cc"]){
            gameOver = true;
            locationFirstChar = 'a';

            //call the win description
            string winDescription = stateWinReason(piecesMap["aa"],locationFirstChar,0,false,false, true); //piecesMap["aa"] is the first piece
            cout<<winDescription<<endl;
            
            return true;
        }
   }
   if(piecesMap["ca"] != '?'){ //if not empty, multiple ifs
        if(piecesMap["ca"] == piecesMap["bb"] && piecesMap["bb"] ==  piecesMap["ac"]){
            gameOver = true;
            locationFirstChar = 'c';

            //call the win description
            string winDescription = stateWinReason(piecesMap["ca"],locationFirstChar,2,false,false, true); //piecesMap["aa"] is the first piece
            cout<<winDescription<<endl;

            return true;    
        }
   } 
   return false;

}

/**
 * @brief take a possibly incorrect playerChoice and decide what the approiate player choice could be.
  *       for a wrong try, give 2 opportinities to the player to make the right choice, otherwise assume a default choice of X
 * 
 * @param playerChoice X or O
 * @return a char that is valid, either O or X 
 */

char board::decidePieceXO(char  playerChoice){
    
    char nextPiece = playerChoice;

    if(nextPiece == 'o' || nextPiece == '0' || nextPiece == 'O')
        nextPiece = 'O';
    else if (nextPiece == 'x' || nextPiece == 'X' )
        nextPiece = 'X';
    else{
          //ask for the first piece correct piece input 2 times
          char tryChar = '?';
          int tryCount = 0;
          bool done = false;

          for(tryCount = 0; tryCount < 2; tryCount ++){ //ask 2 times, set a default otheriwise
              
              cout<<"Please enter first player's piece (X or O): ";
              cin>>tryChar;

              if(tryChar == 'O' || tryChar == '0' || tryChar == 'o' || tryChar == 'X' || tryChar == 'x'){

                  if(tryChar == 'O' || tryChar == '0' || tryChar == 'o'){
                      nextPiece= 'O'; 
                      break;
                  }
                  else if(tryChar == 'x' || tryChar == 'X'){
                        nextPiece='X'; 
                        break;
                  }
              }
              else{
                  cout<<"Wrong choice"<<endl;
              }
          }
          cout<<"Since you could not choose yourself, the default choice will be: X"<<endl;
          nextPiece = 'X'; //default choice
      }
       // nextPiece = 'X';//forced! neccesary? no

    return nextPiece;
}


/**
 * @brief use the given parameters to describe the win, classify it as a diagonal, row or column and the locations involved, then the piece
 * 
 * @param winnerChar X or O
 * @param rowOrCol 0,1,2
 * @param horizontal true if horizintal the win is on  row, false otherwise
 * @param vertical  true if the win is on a column, false otherwise
 * @param diagonal true if the win is on a diagonal, false otherwise
 * @return string  i.e [WIN] <row/column/diagonal>: <First piece location>-<Second Piece Location>-<Third Piece Location>, with piece: X
 */

string board::stateWinReason(char winnerChar, char locationFirstChar, int rowOrCol, bool horizontal, bool vertical, bool diagonal){
   
   stringstream winReason;

   char locationDescriptors[3] = {'a','b','c'};
   char nextThreeChars[3]; //with these 3, we can pair with the LocationDescriptors to form location string, i.e aa, ab, ac, ca, bb, etc.

    if(horizontal){
        
        //if it is horizontal, then the next Three chars are a, b, c, we the locationFirstChar is fixed
        winReason<<"[WIN], row: ";

        for(int i = 0; i < 3; i++){

            if(i < 2)
               winReason<<locationFirstChar<<locationDescriptors[i]<<"-";
            else
               winReason<<locationFirstChar<<locationDescriptors[i]; //donot add the hyphen
        }
        winReason<<", with piece: "<<winnerChar;
    }
    else if(vertical){

        //if it is vertical, then the first chars vary while the Second char is fixed, i.e, ab, bb, cb the b is a constant
        winReason<<"[WIN], column: ";

        for(int i = 0; i < 3; i++){

            if(i < 2)
               winReason<<locationDescriptors[i]<<locationFirstChar<<"-";
            else
               winReason<<locationDescriptors[i]<<locationFirstChar; //donot add the hyphen
        }
        winReason<<", with piece: "<<winnerChar;
    }
    if(diagonal){

        //only 2 cases, aa-bb-cc or ca-bb-ac
        if(locationFirstChar == 'a'){
            winReason<<"[WIN], diagonal: aa-bb-cc, with piece: "<<winnerChar<<endl;
        }else if(locationFirstChar == 'c'){
            winReason<<"[WIN], diagonal: ca-bb-ac, with piece: "<<winnerChar<<endl;
        }
    }

   winReason<<""<<endl;
   return winReason.str(); //the string value of the winning reason
}
