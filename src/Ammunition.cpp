#include "Ammunition.h"

std::ostream& operator<<(std::ostream& os, const Ammunition& ammo) {
    os << "Ammo type = " << ammo.type << '\n'
       << "Quantity = " << ammo.quantity << "\n";
    return os;
}

Ammunition::Ammunition(std::string  type_, int quantity_)
    : type(std::move(type_)), quantity(quantity_) { }
