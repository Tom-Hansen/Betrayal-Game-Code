#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

class Character {
public:
    Character(const std::string& name);
    void SetSkills(int might, int speed, int knowledge, int sanity);
    int GetMight() const;
    int GetSpeed() const;
    int GetKnowledge() const;
    int GetSanity() const;

private:
    std::string name;
    int might;
    int speed;
    int knowledge;
    int sanity;
};

#endif
