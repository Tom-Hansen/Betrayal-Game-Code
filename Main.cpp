#include <iostream>
#include <array>
#include <cstdlib>

#include "Dice.h"
#include "Events.h"
#include "Omens.h"
#include "Tiles.h"
#include "Characters.h"


int main()

int x;

{
  std::cout << "Welcome to the digital version of Betrayal at house on the hill! To start please select how many players are participating? (2-5 Players) \n";

// code to select how many players goes here
cin >> x; // Get user input
cout << "Number of players selected is " << x; // Display the # of players

// Loop Character choice for every player
  for (i=1; i<x; i++) {
    x = 1;
  std::cout << "Now each Player can pick a character. Each character has different stats which may affect how the game is played. \n"; 
  std::cout <<  Player " << x << " ,please select the character of your choice \n";
  players Participants[] = { players("name1"), players("name2") ,players("name3"), players("name4"), players("name5") }; //Players and stats pulled from Characters.h
  std::cout << "You have selected " << //Participant
  x + 1;
    
  }
  
}


// First half of the game

//Trigger a turn

//Role movement dice

//Discover new room
  //Trigger custom room tile
  //trigger item, event, or omen
    //if roll is needed, cause a roll and determine outcome of player roll
    //add item or physical/mental damage or adding

//return to turn trigger

 // Second half of the game
//Omen is decided (give like 3 options lmao)
  //Add a turn for the monster if applicable
      //monster is given a custom turn different from the humans
//Add combat to players' turn
