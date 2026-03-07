#ifndef ROBO_H
#define ROBO_H  

#include <vector>

class robo {
    int x, y; 
public:
    robo(int x = 1, int y = 1); 

    int getX() const { return x; };
    int getY() const { return y; };

    bool tentar_mover(char comando, std::vector<std::vector<int>>& mapa); ///???
};

#endif