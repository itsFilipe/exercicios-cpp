#ifndef SAVE_MANAGER_H
#define SAVE_MANAGER_H

#include "Heroi.h"

namespace SaveManager {
    void salvar(const Heroi& h, int round);
    bool carregar(Heroi& h, int& round);
}

#endif
