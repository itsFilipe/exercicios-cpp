#include <iostream>
#include <string>
#include <vector>

class Player {
public:
    std::string name;
    int health;
    int xp;

    void talk(std::string texto_to_say) { std::cout << name << " says " << texto_to_say << "\n"; }
    bool is_dead();
};

int main() {
    Player hero;

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

    hero.name = "Filipe";
    hero.xp = 2;
    hero.health = 100;

    hero.talk("Hello you");

    std::cout << "My name is " << hero.name;
    std::cout << " and my current xp and healh is " << hero.xp << "/" << hero.health << "\n";

    std::cout << "Enemy is arriving...\n";

    //enemy foi criado na heap, ponteiro recebeu endereço, por ser ponteiro usa-se -> ou dereferência * e utiliza .   
    Player *enemy = new Player;
    enemy->name = "Enemy";
    //ou
    (*enemy).talk("I will destroy you!");
    (*enemy).health = 100;

    delete enemy;

    return 0;
}