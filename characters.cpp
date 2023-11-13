#include "Character.h"

Character::Character(const std::string& name) : name(name), might(2), speed(3), knowledge(4), sanity(6) {
    // Predefined skills for Father Rhinehardt.
}

int Character::GetMight() const {
    return might;
}

int Character::GetSpeed() const {
    return speed;
}

int Character::GetKnowledge() const {
    return knowledge;
}

int Character::GetSanity() const {
    return sanity;
}
//----------------------------------------------------------------------------------------------------------
Character::Character(const std::string& name) : name(name), might(3), speed(4), knowledge(3), sanity(5) {
    // Predefined skills for Zoe Ingstrom.
}

int Character::GetMight() const {
    return might;
}

int Character::GetSpeed() const {
    return speed;
}

int Character::GetKnowledge() const {
    return knowledge;
}

int Character::GetSanity() const {
    return sanity;
}
//----------------------------------------------------------------------------------------------------------
Character::Character(const std::string& name) : name(name), might(4), speed(4), knowledge(3), sanity(4) {
    // Predefined skills for Brandon Jaspers
}

int Character::GetMight() const {
    return might;
}

int Character::GetSpeed() const {
    return speed;
}

int Character::GetKnowledge() const {
    return knowledge;
}

int Character::GetSanity() const {
    return sanity;
}
//----------------------------------------------------------------------------------------------------------
Character::Character(const std::string& name) : name(name), might(3), speed(4), knowledge(5), sanity(3) {
    // Predefined skills for Heather Granville
}

int Character::GetMight() const {
    return might;
}

int Character::GetSpeed() const {
    return speed;
}

int Character::GetKnowledge() const {
    return knowledge;
}

int Character::GetSanity() const {
    return sanity;
}
//----------------------------------------------------------------------------------------------------------
Character::Character(const std::string& name) : name(name), might(4), speed(3), knowledge(4), sanity(4) {
    // Predefined skills for Madame Zostra
}

int Character::GetMight() const {
    return might;
}

int Character::GetSpeed() const {
    return speed;
}

int Character::GetKnowledge() const {
    return knowledge;
}

int Character::GetSanity() const {
    return sanity;
}
