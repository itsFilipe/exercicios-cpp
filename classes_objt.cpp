#include <iostream>
#include <string>
#include <vector>

class Player {
    std::string name;
    int health;
    int xp;

    void talk(std::string);
    bool is_dead();
};

int main() {
    Player hero;
    Player enemy;

    /*
    -- É possivel criar array como qualquer outro tipo
    Player players[] {hero,enemy};

    -- possivel tbm criar por alocação
    Player *enemy {nullptr};
    enemy = new Player;

    delete enemy;

    --vector
    std::vector <Player> player_vec {hero};
    player_vec.push_back(hero);
    */

    return 0;
}