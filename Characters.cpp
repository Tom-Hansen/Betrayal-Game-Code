#include <iostream>
#include <string>

using namespace std;

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