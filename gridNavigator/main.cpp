#include <iostream>
#include "robo.h"

int main() {

    robo meu_robo; //ja esta instanciado com o construtor padrao, entao x=1 e y=1

    std::cout << meu_robo.getX() << std::endl;
    std::cout << meu_robo.getY() << std::endl;

    return 0;
}