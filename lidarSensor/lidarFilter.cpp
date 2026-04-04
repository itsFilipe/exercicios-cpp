#include "lidarFilter.h"
#include <algorithm>

LidarFilter::LidarFilter(int minDistance, int maxDistance) {
    this->minDistance = minDistance;
    this->maxDistance = maxDistance;
}

std::unique_ptr<std::vector<int>> LidarFilter::applyFilter(std::unique_ptr<std::vector<int>> rawData) {
    // Se por acaso o ponteiro vier vazio, ignoramos
    if (!rawData) return rawData;

    // Erase-Remove Idiom: Joga todo "lixo" pro final do array e nos dá a posição final válida
    auto new_end = std::remove_if(rawData->begin(), rawData->end(), [this](int dist) {
        return dist < this->minDistance || dist > this->maxDistance; // Condição de Ruído
    });

    // Apaga definitivamente da memória o "lixo" do final
    rawData->erase(new_end, rawData->end());

    // Retorna a posse do ponteiro agora contendo apenas os dados limpos
    return rawData;
}
