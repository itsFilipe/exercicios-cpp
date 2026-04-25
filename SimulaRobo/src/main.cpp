#include "../include/Sensor.h"
#include "../include/SensorDistancia.h"
#include "../include/SensorGiroscopio.h"
#include "../include/SensorLuz.h"
#include "../include/Robo.h"

#include <iostream>
#include <string>
#include <thread> // Necessário para o sleep
#include <chrono> // Necessário para definir o tempo (segundos)

double mediaDados(Sensor& s);

int main(){

    std::unique_ptr<SensorDistancia> sensorDistancia = std::make_unique<SensorDistancia> (100, 100);
    std::unique_ptr<SensorLuz> sensorLuz = std::make_unique<SensorLuz> (100, 1023, 0);
    std::unique_ptr<SensorGiroscopio> sensorGiroscopio = std::make_unique<SensorGiroscopio> (100, 250, -250);
    std::unique_ptr<Robo> roboPtr = std::make_unique<Robo> (0, 0, 0);

    bool ativo = true;
    while(ativo){
        double mediaDist = mediaDados(*sensorDistancia);
        double mediaLuz = mediaDados(*sensorLuz);
        double mediaGiro = mediaDados(*sensorGiroscopio);

        std::cout << "\nRelatorio Sensores\n";
        std::cout << "Sensor Distancia: " << mediaDist << std::endl;
        std::cout << "Sensor Luz: " << mediaLuz << std::endl;
        std::cout << "Sensor Giro: " << mediaGiro << std::endl;

        roboPtr->atualizar(mediaDist, mediaLuz, mediaGiro);

        std::string msg;
        msg = roboPtr->lerData();
        std::cout << msg << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(3));
    }

    return 0;
}

double mediaDados(Sensor& s){
    auto sensorAux = s.readData();
    double media {0};
    if(sensorAux->size() != 0){
        for(size_t i = 0; i < sensorAux->size(); i++){
            media += (*sensorAux)[i];
        }
        media = media / sensorAux->size();
    } else {
        std::cout << "Nao ha elementos.";
    }

    return media;
}