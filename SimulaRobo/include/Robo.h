#ifndef ROBO_H
#define ROBO_H
#include <string>

struct RobotState {
    bool estaEscuro = false;
    bool pertoDeObstaculo = false;
    bool estaEstavel = true;
    bool detectouLuz = false;
};

enum RobotStateEnum {
    PERIGO,
    ESCURO,
    INSTAVEL,
    NORMAL
};

class Robo {
private:    
    double distancia;
    double luz;
    double giro;
    RobotState meuRobo;
    RobotStateEnum estadoAtual;
protected:
public:
    /* Lista de inicialização */
    Robo(double d, double l, double g) : distancia(d), luz(l), giro(g) {}

    std::string lerData();
    void atualizar(double a, double b, double c);
};

#endif