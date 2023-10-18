int main() 

//x = # of dies to roll based on skill or event information
for (j=0; j<x; j++) {
 {
    Dice* ptrDice = new Dice;
    for (int i=0; i<5; i++) {
        cout << "You rolled" << ptrDice->roll() << '\n';
    }
    delete ptrDice;
 }
}


class Dice() {
public:
    int roll() { return rand() % 6 + 1; }
};
