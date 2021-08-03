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
#include <iostream>
#include <cstring>
#include <fstream> // for the winning patterns
#include <time.h> //random seed generator


using namespace std;


/**
 * @brief Construct a new player::player object, pass a board object to the player, link the player with the board
 * 
 */
player::player(board *boardObj){
     
     pBoard = boardObj; //initialise the board pointer for this player object, the player will need to use all information that the board makes public.
    
    //use its map to populate the maps for the player as needed
    updateAvailableLocations();
    initializeWinningPatterns();
    updateWinningPatterns();
}


/**
 * @brief read the winning-patterns.txt file and populate the map that will have the possible winning patters as i.e aa-bb-cc-r where the last char 
          classifies the pattern as a row, column or diagonal and the first three pairs of letters are locations such that if they have the same pieces
          the player with those pieces wins. The last char is added for statistical purposes when giving game stats later.

          The function will be called before any placements are done, so by then, all the possible winning patterns are available
 *  
 */
void player::initializeWinningPatterns(){  //file name is: winning-patterns.txt
    
    string lineRead;
    ifstream winningPatterns("winning-patterns.txt");

    while(getline(winningPatterns, lineRead)){ 
           availableWinningPatterns[lineRead]=true; //visit the local file and check it's structure
    }

    winningPatterns.close();
     
}

/**
 * @brief read the map with locations form the board and populate this map flagging each location as occupied or not, using booleans as values and keys being the locations
 * 
 */
void player::updateAvailableLocations(){
    
    map<string, char> locationsFromBoard =  (*pBoard).getPiecesMap();
    
    //locationsFromBoard["cc"]='X'; //test  works fine!

    for(auto element: locationsFromBoard){ //comes as an ordered pair
        
        if(locationsFromBoard[element.first] == '?'){   //if the location is not occupied in the original map from the board, then it is free
            availableLocations[element.first]=true;   //element.first is the first part of the pair which is a location
        }
        else availableLocations[element.first]=false;   //this allows the method to be called even later in the execution of the program and still give non false results.
        
       // cout<<element.first<<"="<<availableLocations[element.first]<<endl;
    }
    
}


/**
 * @brief updates the winning patterns based on what pieces are in the location and if a win is possible for that pattern for both playrs, X and O
 * 
*/

void player::updateWinningPatterns(){

  //availableWinningPatterns
  movesPlayed = 0;
  char pieceToMatch='?'; 
  string patternWithClassifier; //the pattern is of the form aa-bb-cc-r where r is the classifier for row in this case, the letters a,b,c can appear in any order as long as they make a winning pattrn
  bool allTheSame=true;
  string currentLocation; 
  char piece1, piece2, piece3;

  //if all the pieces in a winning pattern are the same, then the winning pattern is still avalable, empty spaces donot affect it's avability
  //availableWinningPatterns
  

  for(auto pattern: availableWinningPatterns){
       
       allTheSame = true; //for each iteration, initially

       patternWithClassifier = pattern.first; 
       piece1 = (*pBoard).getPiecesMap()[patternWithClassifier.substr(0,2)]; //the first location
       piece2 = (*pBoard).getPiecesMap()[patternWithClassifier.substr(3,2)]; //the second location
       piece3 = (*pBoard).getPiecesMap()[patternWithClassifier.substr(6,2)]; //the third location
          
       
       if(piece1 != '?'){
           if(piece2 != '?'){
               if(piece1 != piece2) allTheSame = false;
           }if(piece3 != '?'){
               if(piece1 != piece3) allTheSame = false;
           }
       }
       if(piece2 != '?'){
           if(piece1 != '?'){
               if(piece1 != piece2) allTheSame = false;
           }if(piece3 != '?'){
               if(piece3 != piece2) allTheSame = false;
           }
       }
       if(piece3 != '?'){
           if(piece1 != '?'){
               if(piece1 != piece3) allTheSame = false;
           }if(piece2 != '?'){
               if(piece2 != piece3) allTheSame = false;
           }
       }

       availableWinningPatterns[patternWithClassifier] = allTheSame ? true : false;
 
     }
}

/**
 * @brief 
 * 
 * @return string 
 */

string player::choosePieceLocation(){
    
    updateAvailableLocations(); //update them before choosing the next one

    //try to put the piece in a certain winning pattern, not just anywhere [TEST, NEXT TASK]
    string nextLoc="";
    string proposedLocation = "";
    char piece='?';
    char pieceInPattern = ' ';
    bool pieceFound = false;
    bool piecePlaced = false;
    
    //for the first move, pick a random location
    if(movesPlayed == 0){
        string locations[9] = {"aa", "ab", "ac", "ba", "bb", "bc", "ca", "cb", "cc"}; //indexes 0...9
        srand(time(NULL)); //initialiaze a random seed, to ensure "randomness"
        int random = rand() % 10;
        cout<<"First Location was chosed randomly: "<<locations[random]<<", random = "<<random<<endl;
         movesPlayed ++;
        return locations[random];
    }
    
    string winnerOrBlock = nextLocationPlacementWins(); //return the string from here if it not empty
    if(winnerOrBlock!=""){
        movesPlayed ++;
        return winnerOrBlock;
    } 
        

    //update and return the next location
    for(auto availablePattern: availableWinningPatterns){
        pieceFound = false;
        piece='?';
        if(availableWinningPatterns[availablePattern.first]==true){

            //check the piece in the winning pattern
            for(int i=0; i < 7; i+=3){
                
                proposedLocation=availablePattern.first.substr(i,2);
                piece = (*pBoard).getPiecesMap()[proposedLocation];

                if(piece == 'X' || piece == 'O'){
                    pieceFound = true;
                    break; // once we find the piece we stop
                }    
            }

            if(pieceFound == true || piece == '?'){
                if(piece == myPiece || piece == '?'){ //is the player's piece matching the piece in the pattern?
                    for(int i=0; i< 7; i+=3){
                        proposedLocation=availablePattern.first.substr(i,2);
                        piece = (*pBoard).getPiecesMap()[proposedLocation];

                        if(piece == '?'){ //no piece in that location, but the location is in a winning pattern.
                                piecePlaced = true; //we need to know if the piece was placed or not
                                cout<<"We found a matching pattern for the piece"<<endl; 
                                nextLoc = proposedLocation;
                                movesPlayed ++;
                                return nextLoc; 
                        }
                    }        
                }
                else continue;
            }
            else continue;
        }
    }
   
    if(!piecePlaced){  //it means all the winning patterns have been exhausted, so placing the pieces anywhere is not a loss. So place the pieces anywhere.
        for(auto location: availableLocations){
            if(availableLocations[location.first]==true){
                nextLoc = location.first;
                movesPlayed++;
                return nextLoc;
            }
        }
    }
   movesPlayed ++; 
   return nextLoc;  
    
}

/**
 * @brief set the piece for the player
 * 
 * @param piece 
 * @return char 
 */
char player::setMyPiece(char piece){
    myPiece = piece;
    return myPiece;
}

/**
 * @brief return a location that wins the current player the game or helps them block a winning location for the opponent.
          placing a piece that wins for the current player has a higher priority than defending.

          for each pattern:
            check if it has two same pieces.
            if true, return the location in that pattern without a piece
        else return an empty location.
 * 
 * @return string 
 */
string player::nextLocationPlacementWins(){

        updateWinningPatterns(); //update the winning  patterns so that we only search for the next winning location in a winning pattern.
        
        string pieceLocation;
        char piece;
        int pieceCount=0; // if it is 2 for a winning pattern, it means that 1 more piece into the pattern results in a win.
        string winningOrBlockingLoc="";

        for(auto availablePattern: availableWinningPatterns){
        
            if(availableWinningPatterns[availablePattern.first]==true){
                pieceCount = 0;
                for(int i=0; i < 7; i+=3){             
                    pieceLocation=availablePattern.first.substr(i,2);
                    piece = (*pBoard).getPiecesMap()[pieceLocation];

                    if(piece == '?') 
                        winningOrBlockingLoc=pieceLocation; //this will be true only once for a pattern 1 placement away from a win.

                    if(piece == 'X' || piece == 'O'){ //for a winning pattern, these should be the same
                        pieceCount += 1;
                    }
                }
                if(pieceCount == 2){
                    cout<<"Next placement wins at "<<winningOrBlockingLoc<<endl;
                    return winningOrBlockingLoc;
                }
                    
            }
        }

        //if the for loop ends without a return, we donot have anything to rush blocking or taking advantage of
        string nothing ="";
        return nothing;
}


void player::printBoard(){

    cout<<"The board as seen by the player"<<endl;
    (*pBoard).toString();

}
