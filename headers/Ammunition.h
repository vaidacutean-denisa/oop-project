#ifndef AMMUNITION_H
#define AMMUNITION_H

#include <iostream>

class Ammunition {
    std::string type;           // tipul munitiei
    int quantity;               // ar trebui sa fie cantitatea pe care o are player-ul in inventar (inexistent din pacate)

public:
    // constructors
    Ammunition(std::string type_, int quantity_);

    // op <<
    friend std::ostream& operator<<(std::ostream& os, const Ammunition& ammo);
};

#endif //AMMUNITION_H
