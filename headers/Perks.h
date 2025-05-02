#ifndef PERKS_H
#define PERKS_H

#include <string>
#include "Player.h"

class Perks {
    float x, y;                     // de inlocuit cu vector pentru pozitie
    float duration;                 // concept doar teoretic so far
    std::string  type;

public:
    // constructors
    Perks(float x_, float y_, float duration_, std::string  type_) : x(x_), y(y_), duration(duration_), type(std::move(type_)) {}

    // methods
    void applyPerk(Player& player) const;

    // op <<
    friend std::ostream& operator<<(std::ostream& os, const Perks& perk);
};


#endif //PERKS_H
