#include "Perks.h"

std::ostream& operator<<(std::ostream& os, const Perks& perk) {
    os << "Perks - Type: " << perk.type << '\n'
       << "Position: (" << perk.x << ", " << perk.y << ")" << '\n'
       << "Duration: " << perk.duration << " seconds";
    return os;
}

void Perks::applyPerk(Player& player) const {
    if (type == "health") {
        player.applyHealthBoost(20);
        // std::cout << "Health boost applied.\n";
        if (player.getHealth() > 75)
            std::cout << "You're at " << player.getHealth() << " health. You're in good shape!\n";
        else if (player.getHealth() > 35)
            std::cout << "You've got " << player.getHealth() << " health. Keep pushing!\n";
        else
            std::cout << player.getHealth() << " health left. You're hanging by a thread, but hey, it's a strong thread! Maybe avoid the next hit?\n";
    }
    else if (type == "speed") {
        player.applySpeedBoost(4.5f);
        std::cout << "Speed boost activated. Time to leave everyone in the dust.\n";
    }
    else {
        player.applyDamageBoost(1.5f);
        std::cout << "Your hits just got a bit more.. convincing.\n";
    }
}

