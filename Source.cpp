// AERSP 424 Final Project

#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <thread>
#include <chrono>

#define COLOR_TEXT(color) "\033[38;5;" #color "m"
#define BRIGHT "\033[1m"
#define RESET_COLOR "\033[0m"


using namespace std;

int Omen = 1; // This sets up the Omen variable which basically oversees the progress of the game

class Dice //This contains individual die rolls that are sent back to the dice function
{
public:
    int roll() 
    {
        int test = rand();        // To increase randomness of the dice rolls, a seed is used based on another random number multiplied by the time
        srand(test * time(NULL));
        int die = rand() % 3;     // Dice in Betrayal go from 0 to 2
        return die;
    }
};

class Character {
public:
    string name;
    int might;
    int speed;
    int knowledge;
    int sanity;

    Character(const string& n, int m, int sp, int kn, int sa)
        : name(n), might(m), speed(sp), knowledge(kn), sanity(sa) {}
};

class Player {
public:
    string name;
    Character character; // Store the selected character for each player
    int distance;

    Player(const string& n, Character& c, int howFar)
        : name(n), character(c), distance(howFar) {}
};

class Room {
public:
    string name;
    string description;
    int number;

    Room(const string& n, const string& desc, const int& num)
        : name(n), description(desc), number(num) {}
};

class Event {
public:
    string name;
    string readout;
    string help;
    string hurt;
    int RollFor;
    int helpNum;
    int hurtNum;
    string goodOutput;
    string badOutput;

    Event(const string& n, const string& out, const string& plus, const string& minus, const int& rollnum, const int& helpAmount, const int& hurtAmount, const string& goodOut, const string& badOut)
        : name(n), readout(out), help(plus), hurt(minus), RollFor(rollnum), helpNum(helpAmount), hurtNum(hurtAmount), goodOutput(goodOut), badOutput(badOut) {}

    //int doEvent(Dice& rolling, int trait, int playerNumber) {
    //    int result = rolling.roll();
    //    cout << "Player " << playerNumber << " is facing Event " << name << ": " << readout << endl;
    //    cout << "Rolling " << trait << " dice." << endl;
    //    this_thread::sleep_for(chrono::seconds(1));
    //    cout << "You rolled " << result << '\n';
    //    return result;
    //}
};

class Item {
public:
    string name;
    string readout;
    string trait;
    int buff;

    Item(const string& n, const string& out, const string& traitEffect, const int& traitBuff)
        : name(n), readout(out), trait(traitEffect), buff(traitBuff) {}
};

class Omens {
public:
    string name;
    string readout;
    string trait;
    int buff;
    string trait2;
    int buff2;

    Omens(const string& n, const string& out, const string& traitEffect, const int& traitBuff, const string& traitEffect2, const int& traitBuff2)
        : name(n), readout(out), trait(traitEffect), buff(traitBuff), trait2(traitEffect2), buff2(traitBuff2) {}
};

int getPlayerCount() {
    int count = 0;
    while (true) {
        if (cin >> count) { // If the player entered an integer, this will make sure it's <5 and >2
            if (count >= 2 && count <= 5) {
                return count;
            }
            else {
                cout << "Error. Player count must be at least 2 and at most 5. Try again." << endl;
            }
        }
        else { // This is a catch for if the entered value isn't an integer
            cout << "Error: Invalid input. Please enter a valid integer." << endl;
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discarding invalid input to avoid spamming the console with error messages
        }
    }
}

void characterSelecter(int num, vector<Player>& players) {
    vector<Character> characters = {
        {"Father Rhinehardt", 2, 3, 4, 6},
        {"Zoe Ingstrom", 3, 4, 3, 5},
        {"Brandon Jaspers", 4, 4, 3, 4},
        {"Heather Granville", 3, 4, 5, 3},
        {"Madame Zostra", 4, 3, 4, 4},
        {"Monster", 4, 4, 4, 4}
    };

    cout << "Five characters are available:" << endl;

    for (size_t i = 0; i < 5; ++i) {
        cout << i + 1 << ". " << characters[i].name << endl;
        cout << "    Might: " << characters[i].might << endl;
        cout << "    Speed: " << characters[i].speed << endl;
        cout << "    Knowledge: " << characters[i].knowledge << endl;
        cout << "    Sanity: " << characters[i].sanity << endl;
    }

    for (int k = 0; k < num; k++) {
        int output = k + 1;
        cout << endl;
        cout << "Player " << output << ", enter the number of your choice: ";
        int choice = 0;
        cin >> choice;

        while (choice < 1 || choice > 5) {
            cout << "ERROR: The character options range from 1 to 5. Try again." << endl;
            cout << endl;
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Player " << output << ", enter the number of your choice: ";
            cin >> choice;
        }

        players.push_back(Player("Player " + to_string(output), characters[choice - 1], 0));

        cout << COLOR_TEXT(44) << BRIGHT << "Player " << output << RESET_COLOR << ", you selected " << COLOR_TEXT(9) << BRIGHT << characters[choice - 1].name <<  "." << RESET_COLOR << endl;
    }
}

vector<Player> welcome() {
    int players = 0;
    cout << endl;
    cout << "Welcome to the C++ version of the board game Betrayal at House on the Hill. This game can be played with 2-5 players." << endl;
    cout << endl;

    cout << "How many players are there? ";
    players = getPlayerCount(); // calls the getPlayerCount function

    vector<Player> selectedPlayers;
    cout << "Next, select your characters. Each character has different traits, which will have minor impacts on the gameplay." << endl;
    cout << endl;
    characterSelecter(players, selectedPlayers);
    return selectedPlayers;
}

int dice(int num, int n)
{
    //num = # of dice to roll based on skill or event information
    int total = 0;

    if (n == 666)
    {
        cout << COLOR_TEXT(9) << BRIGHT << "The Monster " << n << RESET_COLOR << " is rolling " << num << " dice." << endl;
        cout << endl;
        for (int j = 0; j < num; j++) {
            {
                Dice* rolling = new Dice;

                int result = rolling->roll();
                cout << "The Monster rolled " << result << '\n';
                this_thread::sleep_for(chrono::seconds(1));
                total += result;
            }
        }
    }
    if (n != 666)
        {
            cout << COLOR_TEXT(44) << BRIGHT << "Player " << n << RESET_COLOR << " is rolling " << num << " dice." << endl;
            cout << endl;
            for (int j = 0; j < num; j++) {
                {
                    Dice* rolling = new Dice;

                    int result = rolling->roll();
                    cout << "You rolled " << result << '\n';
                    this_thread::sleep_for(chrono::seconds(1));
                    total += result;
                }
            }
        }
    return(total);
}

void secondHalf(vector<Player>& players)
{
    //Possibly do a method where players build up distance over time based on their speed rolls being added up?
    //The monster can spawn with a random distance within and do its own speed rolls to 
    cout << endl;
    cout << "----------------------------------------------------------" << endl;
    cout << endl;
    cout << "You could not beat the omen";
    this_thread::sleep_for(chrono::seconds(1));
    cout << ".";
    this_thread::sleep_for(chrono::seconds(1));
    cout << ".";
    this_thread::sleep_for(chrono::seconds(1));
    cout << "." << endl;
    this_thread::sleep_for(chrono::seconds(2));
    cout << endl;

    cout << "Several rooms away, you hear a deep, inhuman scream.\nYou do not know what made that noise, but you don't need to find out.\n";
    this_thread::sleep_for(chrono::seconds(3));
    cout << "It's coming toward you.\n";
    this_thread::sleep_for(chrono::seconds(2));
    cout << "You need to get out of here.\n";
    this_thread::sleep_for(chrono::seconds(2));
    cout << "However, not all hope is lost. \nAs you look around hopelessly, you find a key on the ground.\nIt is the key to unlock the jammed front door.\n";
    cout << "The race is on." << endl;
    cout << endl;
    cout << "----------------------------------------------------------" << endl;
    cout << endl;

    cout << "For the second half of the game, you will continue to make speed rolls. \nYou have built up a distance over the first half of the game, now you must backtrack to 0.";
    cout << "If the monster ends up at the same distance as you, you and the monster make a might roll. \nWhoever rolls higher loses 3 from their distance. \nIf the monster reaches 0, the front door, before any players do, you lose.";

    cout << "The Monster has 4 speed, might, sanity, and knowledge." << endl;

    int monstDist = (rand() % 40); // 1.5 * the average distance of the highest-speed player during an average game, rounded up to 40 to give players a bit more of a chance

    vector<Character> characters = {
    {"Father Rhinehardt", 2, 3, 4, 6},
    {"Zoe Ingstrom", 3, 4, 3, 5},
    {"Brandon Jaspers", 4, 4, 3, 4},
    {"Heather Granville", 3, 4, 5, 3},
    {"Madame Zostra", 4, 3, 4, 4},
    {"Monster", 4, 4, 4, 4}
    };
    players.push_back(Player("Monster ", characters[5], monstDist));

    int n = 1;
    int move = 0;
    int keepGoing = 1;
    int playerMight = 0;
    int monstMight = 0;
    static int monstSpeed = 4;
    
    while (keepGoing ==1)
    {
        for (Player& player : players) { // runs through each player in the list
        int speed = player.character.speed; // Uses the player's speed trait to choose the number of dice to roll
        cout << "Make a speed roll." << endl;
        int rollResult = dice(speed, n);
        cout << "This brings the roll to a total of " << rollResult << endl;
        cout << endl;
        player.distance = player.distance - rollResult;

        cout << player.character.name << " is now " << player.distance << " from the exit." << endl;

        this_thread::sleep_for(chrono::seconds(1));

        if (player.distance == monstDist)
        {
            playerMight = dice(player.character.might, n);
            monstMight = dice(monstSpeed, 666);
            if (monstMight >= playerMight)
            {
                monstDist = monstDist - 3;
            }
            else
            {
                player.distance = player.distance - 3;
            }
        }
        if (monstDist == 0)
        {
            cout << "The monster reaches the exit, barricading it shut. \nThere is no other way out.\n\n";
            this_thread::sleep_for(chrono::seconds(3));
            cout << "Game over.";
            keepGoing = 0;
            break;
        }
        if (player.distance == 0)
        {
            cout << "You make it to the door, and insert the key.\n";
            this_thread::sleep_for(chrono::seconds(3));
            cout << "It turns.\nSlowly, the door opens, and you smell the fresh air.\nThe monster shrieks in the moonlight, running deep into the house.\n\nYou have escaped.";
        }

        cout << endl;
        cout << "Press any key and enter to continue. ";
        cin >> move;
        cin.clear(); // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        cout << endl;
        cout << "----------------------------------------------------------" << endl;
        cout << endl;
        n++;
    }
        
    }
}

void turns(vector<Player>& players, vector<Event>& events, vector<Room>& rooms, vector<Item>& items, vector<Omens>& omens) // Brings the player's character list and the cards into the turns function. This basically controls the gameplay
{
    cout << "We will now move on to the first turn. \nYou will roll a speed roll, meaning you will roll the number of dice corresponding to the number of your speed trait." << endl;
    cout << endl;
    int move;
    cout << "Press any key and enter to continue. ";
    cin >> move;
    cin.clear(); // Clear the error flag
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
    cout << endl;

    int n = 1; // output for player number
    int haunt = 1; // This is the haunt number which will increase whenever a haunt roll is successful
    int round = 1; // Keeps track of round numbers

    while (haunt >= Omen)
    {
         n = 1;
         cout << "----------------------------------------------------------" << endl;
         cout << endl;
         cout << COLOR_TEXT(82) << BRIGHT <<  "                       R O U N D   " << round << RESET_COLOR << endl;
         cout << endl;
         cout << "----------------------------------------------------------" << endl;
         for (Player& player : players) { // runs through each player in the list
           int speed = player.character.speed; // Uses the player's speed trait to choose the number of dice to roll
           cout << "Make a speed roll. If it is larger than 0, you may move to a new room." << endl;
           int rollResult = dice(speed, n);
           cout << "This brings you to a total of " << COLOR_TEXT(165) << BRIGHT << rollResult << RESET_COLOR << endl;
           cout << endl;
           if (rollResult > 0)
           {
               player.distance = player.distance + rollResult;

               this_thread::sleep_for(chrono::seconds(1));

               int roomIndex = rand() % rooms.size();
               Room& selectedRoom = rooms[roomIndex];
               cout << "Player " << n << " entered " << selectedRoom.name << ": " << selectedRoom.description << endl;
               int roomNum = selectedRoom.number;
               cout << endl;
               cout << "Press any key and enter to continue. ";
               cin >> move;
               cin.clear(); // Clear the error flag
               cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
               cout << endl;
               cout << "----------------------------------------------------------" << endl;
               cout << endl;

               if (roomNum == 0) {
                   int eventIndex = rand() % events.size();
                   this_thread::sleep_for(chrono::seconds(1));
                   Event& selectedEvent = events[eventIndex];
                   cout << "Player " << n << " pulls an event card: " << selectedEvent.name << ". " << endl;
                   cout << selectedEvent.readout << endl;
                   cout << endl;
                   cout << "Press any key and enter to continue. ";
                   cin >> move;
                   cin.clear(); // Clear the error flag
                   cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                   cout << endl;
                   cout << "----------------------------------------------------------" << endl;
                   cout << endl;

                   int eventRoll = 0;
                   if (selectedEvent.help == "sa")
                   {
                       eventRoll = dice(player.character.sanity, n);
                       if (eventRoll >= selectedEvent.RollFor)
                       {
                           player.character.sanity = player.character.sanity + selectedEvent.helpNum;
                           cout << selectedEvent.goodOutput;
                       }
                   }
                   if (selectedEvent.help == "sp")
                   {
                       eventRoll = dice(player.character.speed, n);
                       if (eventRoll >= selectedEvent.RollFor)
                       {
                           player.character.speed = player.character.speed + selectedEvent.helpNum;
                           cout << selectedEvent.goodOutput;
                       }
                   }
                   if (selectedEvent.help == "m")
                   {
                       eventRoll = dice(player.character.might, n);
                       if (eventRoll >= selectedEvent.RollFor)
                       {
                           player.character.might = player.character.might + selectedEvent.helpNum;
                           cout << selectedEvent.goodOutput;
                       }
                   }
                   if (selectedEvent.help == "k")
                   {
                       eventRoll = dice(player.character.knowledge, n);
                       if (eventRoll >= selectedEvent.RollFor)
                       {
                           player.character.knowledge = player.character.knowledge + selectedEvent.helpNum;
                           cout << selectedEvent.goodOutput;
                       }
                   }
                   if (selectedEvent.hurt == "sa" && eventRoll < selectedEvent.RollFor)
                   {
                       player.character.sanity = player.character.sanity - selectedEvent.hurtNum;
                       cout << selectedEvent.badOutput;
                   }
                   if (selectedEvent.hurt == "sp" && eventRoll < selectedEvent.RollFor)
                   {
                       player.character.speed = player.character.speed - selectedEvent.hurtNum;
                       cout << selectedEvent.badOutput;
                   }
                   if (selectedEvent.hurt == "m" && eventRoll < selectedEvent.RollFor)
                   {
                       player.character.might = player.character.might - selectedEvent.hurtNum;
                       cout << selectedEvent.badOutput;
                   }
                   if (selectedEvent.hurt == "k" && eventRoll < selectedEvent.RollFor)
                   {
                       player.character.knowledge = player.character.knowledge - selectedEvent.hurtNum;
                       cout << selectedEvent.badOutput;
                   }
                   if (selectedEvent.hurt == "p" && eventRoll < selectedEvent.RollFor)
                   {
                       if (player.character.might > player.character.speed)
                       {
                           player.character.might = player.character.might - selectedEvent.hurtNum;
                           cout << selectedEvent.badOutput;
                       }
                       else
                       {
                           player.character.speed = player.character.speed - selectedEvent.hurtNum;
                           cout << selectedEvent.badOutput;
                       }
                   }
                   if (selectedEvent.hurt == "me" && eventRoll < selectedEvent.RollFor)
                   {
                       if (player.character.knowledge > player.character.sanity)
                       {
                           player.character.knowledge = player.character.knowledge - selectedEvent.hurtNum;
                           cout << selectedEvent.badOutput;
                       }
                       else
                       {
                           player.character.sanity = player.character.sanity - selectedEvent.hurtNum;
                           cout << selectedEvent.badOutput;
                       }
                   }
               }
               else if (roomNum == 1) {
                   int itemIndex = rand() % items.size();
                   Item& selectedItem = items[itemIndex];
                   cout << "Player " << n << " found an item in the room: " << selectedItem.name << ". " << endl;
                   cout << selectedItem.readout << endl;
                   if (selectedItem.trait == "sa")
                   {
                       player.character.sanity = player.character.sanity + selectedItem.buff;
                   }
                   else if (selectedItem.trait == "sp")
                   {
                       player.character.speed = player.character.speed + selectedItem.buff;
                   }
                   else if (selectedItem.trait == "m")
                   {
                       player.character.might = player.character.might + selectedItem.buff;
                   }
                   else if (selectedItem.trait == "k")
                   {
                       player.character.knowledge = player.character.knowledge + selectedItem.buff;
                   }
               }
               else {
                   int omenIndex = rand() % omens.size();
                   Omens& selectedOmen = omens[omenIndex];
                   cout << "Player " << n << " picked up an Omen card: " << selectedOmen.name << ". " << endl;
                   cout << selectedOmen.readout << endl;
                   if (selectedOmen.trait == "sa")
                   {
                       player.character.sanity = player.character.sanity + selectedOmen.buff;
                   }
                   if (selectedOmen.trait == "sp")
                   {
                       player.character.speed = player.character.speed + selectedOmen.buff;
                   }
                   if (selectedOmen.trait == "m")
                   {
                       player.character.might = player.character.might + selectedOmen.buff;
                   }
                   if (selectedOmen.trait == "k")
                   {
                       player.character.knowledge = player.character.knowledge + selectedOmen.buff;
                   }
                   if (selectedOmen.trait2 == "sa")
                   {
                       player.character.sanity = player.character.sanity + selectedOmen.buff2;
                   }
                   if (selectedOmen.trait2 == "sp")
                   {
                       player.character.speed = player.character.speed + selectedOmen.buff2;
                   }
                   if (selectedOmen.trait2 == "m")
                   {
                       player.character.might = player.character.might + selectedOmen.buff2;
                   }
                   if (selectedOmen.trait2 == "k")
                   {
                       player.character.knowledge = player.character.knowledge + selectedOmen.buff2;
                   }
                   cout << endl;
                   cout << "You will now attempt a Haunt roll, where you roll 6 dice. \nIf you roll more than the current Omen level of " << COLOR_TEXT(44) << BRIGHT << Omen << RESET_COLOR << ", the game continues." << endl;
                   cout << "If you roll less than the Omen level, things will change..." << endl;
                   cout << endl;
                   cout << "Press any key and enter to continue to the Haunt roll. ";
                   cin >> move;
                   cin.clear(); // Clear the error flag
                   cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                   cout << endl;
                   cout << "----------------------------------------------------------" << endl;
                   cout << endl;
                   haunt = 0;
                   haunt = dice(6, n);
                   if (haunt >= Omen)
                   {
                       cout << endl;
                       cout << "You rolled a total of " << COLOR_TEXT(208) << BRIGHT << haunt << RESET_COLOR << ", which is greater than or equal to the Omen number of " << COLOR_TEXT(44) << BRIGHT << Omen << RESET_COLOR << ". \nThe game continues." << endl;
                       Omen++;
                       cout << endl;
                       cout << "The omen level is now " << COLOR_TEXT(44) << BRIGHT << Omen << RESET_COLOR << ".";
                   }
                   else // If the haunt roll fails to be larger than the Omen number, this triggers the second half of the game.
                   {
                       cout << "You rolled a total of " << COLOR_TEXT(208) << BRIGHT << haunt << RESET_COLOR << ", which is less than the Omen number of " << COLOR_TEXT(44) << BRIGHT << Omen << RESET_COLOR << "." << endl;
                       secondHalf(players);
                   }
           }
           }

           cout << endl;
           cout << endl;
           cout << "Player " << n << " (" << player.character.name << ")'s traits are now as follows:" << endl;
           cout << "Speed: " << player.character.speed << endl;
           cout << "Might: " << player.character.might << endl;
           cout << "Sanity: " << player.character.sanity << endl;
           cout << "Knowledge: " << player.character.knowledge << endl;

           int Move3 = 0;
           cout << "Press any character and enter to continue the game.";
          
           cin >> Move3;
           cin.clear(); // Clear the error flag
           cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
           cout << endl;

           n += 1;
           }
         round++;
    }
}

void introMessage()
{
    cout << "Now that characters are chosen, let's begin our journey." << endl;
    cout << endl;
    cout << "You and your companions are caught in a bad storm. It was raining so hard you had to pull over. \nYou sought refuge in a mysterious mansion atop a hill. \nThe door creaked open, but as you entered, it slammed shut, locking you inside the ominous, dimly lit hallway, leaving you trapped and shrouded in a sense of foreboding. \n";
}

int main()
{
    vector<Player> PlayerList = welcome(); // gets the characters and brings back their list into main.

    int Move; // This is just a variable that the user will enter to move on to the next part of the game. It serves no purpose other than to pause the lines of words.

    cout << endl;
    cout << "Press any key and enter to continue on to the game. ";
    cin >> Move;
    cin.clear(); // Clear the error flag
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
    cout << endl;
    cout << "----------------------------------------------------------" << endl;
    cout << endl;

    introMessage(); // Begins with an intro message

    int move2; // Another game-pausing variable

    cout << endl;
    cout << "Press any key and enter to continue the game. ";
    cin >> move2;
    cin.clear(); // Clear the error flag
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
    cout << endl;
    cout << "----------------------------------------------------------" << endl;
    cout << endl;

    vector<Event> events = {
        {"Creepy Crawlies", "A thousand bugs spill onto your skin, under your clothes, and in your hair. \nMake a sanity roll of 5 or more.", "sa", "sa", 5, 1, 1, "\nYou blink, and they're gone. Gain 1 sanity.", "\nLose 1 sanity."},
        {"Something Slimy", "What’s around your ankle? \nA bug? \nA tentacle? \nA dead hand clawing? \nMake a speed roll of 4 or more.", "sp", "m", 4, 1, 1, "\nYou break free. Gain 1 speed.", "\nLose 1 might."},
        {"Burning Man", "A man on the fire runs through the room. \nHis skin bubbles and cracks, falling away from him and leaving a fiery skull that clatters to the ground, bounces, and disappears. \nMake a sanity roll of 4 or more.", "sa", "p", 4, 1, 1, "\nYou feel a little hot under the collar, but otherwise fine. Gain 1 Sanity.", "\nYou burst into flames! Take 1 die of physical damage."},
        {"The Voice", "'I'm under the floor, buried under the floor...' \nThe voice whispers once, then is gone. \nAttempt a knowledge roll of 4 or more.", "k", " ", 4, 1, 0, "\nYou pry open the floorboards, finding documents on the house's history. Gain 1 knowledge.", "\nYou pry open the floorboards to look for the source, but to no avail."},
        {"Funeral", "You see an open coffin.\nYou're inside it.\nYou must attempt a sanity roll of 4 or more.", "sa", "sa", 4, 1, 1, "\nYou blink, and it's gone. Gain 1 sanity.", "\nThe vision disturbs you. Lose 1 sanity."},
        {"Possession", "A shadow separated from the wall. As you stand in shock, the shadow surrounds you and chills you to the core. \nAttempt a sanity roll of 4 or more.", "sa", "sa", 4, 1, 2, "\nYou resist the shadow’s corruption. Gain 1 sanity.", "\nThe shadow drains your energy. Lose 2 sanity."},
        {"Creepy Puppet", "You see one of those dolls that give you the willies. It jumps at you with a tiny spear. \nAttempt a might roll of 4 or more.", "m", "p", 4, 0, 1, "\nYou fend off the doll and lock it in a chest.", "\nYou take 1 physical damage from the doll, before it falls lifeless on the floor."},
        {"Hideous Shriek", "It starts like a whisper, but ends in a soul-rendering shriek. \nAttempt a Sanity roll of 4 or more.", "sa", "me", 4, 0, 1, "\nYou resist the sound.", "\nTake 1 mental damage."},
        {"Debris", "Plaster falls from the walls and ceiling. \nYou must attempt a speed roll of 3 or more.", "sp", "p", 3, 1, 2, "\nYou dodge the plaster. \nGain 1 speed.", "\nYou're buried in the debris. \nTake 2 physical damage."},
        {"Image in the Mirror", "There is an old mirror in this room. Your frightened reflection moves on its own. \nYou realize it is you from another time. \nYour reflection writes on the mirror: \n\nT H I S   W I L L   H E L P", "m", " ", 0, 1, 0, "\nYou feel strengthened. Gain 1 might.", "\n"},
        {"Phone Call", "A phone rings in the room. You feel compelled to answer it. \nAttempt a sanity roll of 4 or more.", "sa", "p", 4, 1, 2, "\nA sweet little granny voice says: 'Tea and cakes! Tea and cakes! You were always my favorite.'", "\nA sweet little granny voice says: 'Bad little children must be punished!' Take 1 physical damage."},
        {"Night View", "You see a vision of a ghostly couple walking the grounds, silently strolling in their wedding best. \nYou must attempt a knowledge roll of 5 or more.", "k", " ", 5, 1, 0, "\nYou recognize the ghosts as former inhabitants of the house. You call their names, and they turn to you, whispering dark secrets of the house. \nGain 1 knowledge.", "\nYou pull back in horror, unable to watch."},
        {"Mist from the Walls", "Mists pours out from the walls. There are faces in the mist, human and... inhuman.\nAttempt a sanity roll of 4 or more.", "sa", "me", 4, 0, 1, "\nThe faces are tricks of light and shadow. \nAll is well.", "\nTake 1 mental damage."},
    };

    vector<Room> rooms = {
        {"Game Room", "You step into an eerie, suffocating chamber cloaked in dust. \nA dim light reveals a colossal table nestled in the shadows, where five ominous silhouettes engage in a macabre card game. \nAs you cautiously draw near, a chilling realization grips you - the figures are mere remnants of souls lost to the sinister game. \nAbruptly, the lights extinguish, plunging you into a darkness that smothers any semblance of hope, casting a foreboding shroud over your uncertain fate.", 0},
        {"Crypt", "You step into a chilling crypt, its stillness heavy with ancient whispers. \nDim lantern light reveals a looming stone sarcophagus surrounded by decaying coffins. \nThe air is filled with an oppressive despair, and as the feeble glow extinguishes, you find yourself enveloped in an impenetrable darkness, where the line between the living and the dead becomes an ominous blur. \nYou feel something grab onto your shoulder, draining away your sanity.", 0},
        {"Organ Room", "You step into what seems to be an Organ Room. \nA grand pipe organ looms in the dim light, casting elongated shadows. \nAs you approach, ghostly melodies emanate, shivers coursing through you.", 0},
        {"Chapel", "You enter a solemn Chapel, the air hushed with sacred reverence. \nSoft candlelight flickers, casting dancing shadows on time-worn pews. \nStained glass windows tell stories of ancient devotion, and the echoes of whispered prayers linger in the silence.", 0},
        {"Vault", "Before you lies the Vault, an enigmatic chamber guarded by symbols of wisdom. \nTo enter, you must roll the dice of knowledge, a single chance to unlock its secrets. \nSuccess opens the door to a realm where wisdom becomes your guide through uncharted corridors of the unknown.", 1},
        {"Store Room", "You enter the forgotten Storeroom, where the air holds the musty scent of antiquity. \nDust-covered relics on creaking shelves whisper tales of a forgotten past. \nAmid the shadows, hidden value awaits those who dare to unearth the secrets within.", 1},
        {"Servant's Quarters", "The next room of this eerie mansion you discover is the quiet Servant's Quarter, frozen in a bygone era. \nWorn belongings and faded portraits tell tales of dedicated service. \nThe room stands as a silent testament to lives woven into the history of a place, their untold stories lingering in the air.", 2},
        {"Pentagram Chamber", "The second you enter the room, you wish you hadn't. \nYou knew you made a mistake. \nIn the ominous Pentagram Chamber, a glowing symbol on the floor casts demonic shadows on cryptic walls. \nEach step heightens the foreboding, turning the room into a nexus of mystic forces where the mundane and arcane blur. \nYou find yourself at the brink of insanity.", 2},
        {"Gymnasium", "You step into the Gymnasium, the air filled with the echoes of past exertion. \nSilent weights and exercise machines stand witness to the dedication that once filled the space, turning it into a testament to the pursuit of physical prowess.", 2},
    };

    vector<Item> items = {
        {"Angel Feather", "A perfect feather fluttering in your hand. \nGain 1 sanity.", "sa", 1},
        {"Sacrificial Dagger", "A twisted shard of iron covered in mysterious symbols and stained with blood. \nGain 2 might.", "m", 2},
        {"Medical Kit", "A doctor's bag, depleted in some critical resources. \nGain 2 physical traits.", "p", 2},
        {"Rabbit's Foot", "Not so lucky for the rabbit. \nGain 1 speed.", "sp", 1},
    };

    vector<Omens> omens = {
        {"Spear", "A weapon pulsing with power. \nGain 1 might.", "m", 1, " ", 0},
        {"Mad Man", "A raving, forthing madman becomes your companion. \nGain 2 might and lose 1 sanity.", "m", 2, "sa", -1},
        {"Dog", "This mangy dog seems friendly. \nAt least you hope it is. \nIt becomes your companion. Gain 1 sanity and 1 might.", "sa", 1, "m", 1},
        {"Mask", "A somber mask to hide your intentions. \nPutting on the mask will result in gaining 2 knowledge, but losing 2 sanity.", "k", 2, "sa", -2},
        {"Book", "A diary, or lab notes? \nAncient script, or modern ravings? \nGain 2 knowledge now.", "k", 2, " ", 0},
        {"Weightless Boots", "They're lighter than air... well not really. \nBut they seem to make you walk faster. \nGain 1 speed now.", "sp", 1, " ", 0},
        {"Army helmet", "A relic from an old war. A solider must have lived here. \nGain 2 might now.", "m", 2, " ", 0},
        {"Soft music", "You hear soft, orchestral music emininating from all around you. It soothes you. \nGain 2 sanity now.", "sa", 1, " ", 0},
    };

    turns(PlayerList, events, rooms, items, omens);
}