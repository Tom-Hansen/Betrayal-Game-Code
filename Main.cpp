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
  std::cout << "Welcome to the digital version of Betrayal in the house on the hill! To start please select how many players are participating? (2-5 Players) \n";

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
