#ifndef STATUS_EFFECT_H
#define STATUS_EFFECT_H

struct StatusEffect {
    enum class Tipo { VENENO, ATORDOADO };
    Tipo tipo;
    int duracao; // turns remaining
    int valor;   // damage per tick (VENENO); unused for ATORDOADO
};

#endif
