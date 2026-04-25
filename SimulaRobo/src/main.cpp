#include "Sensor.h"
#include "SensorDistancia.h"
#include "SensorGiroscopio.h"
#include "SensorLuz.h"
#include <iostream>
#include <string>
#include <thread> // Necessário para o sleep
#include <chrono> // Necessário para definir o tempo (segundos)

struct RobotState {
    bool estaEscuro = false;
    bool pertoDeObstaculo = false;
    bool estaEstavel = true;
    bool detectouLuz = false;
};

enum EstadoRobo {
    PERIGO,
    ESCURO,
    INSTAVEL,
    NORMAL
};

double mediaDados(Sensor& s);

int main(){

    std::unique_ptr<SensorDistancia> sensorDistancia = std::make_unique<SensorDistancia> (100, 100);
    std::unique_ptr<SensorLuz> sensorLuz = std::make_unique<SensorLuz> (100, 1023, 0);
    std::unique_ptr<SensorGiroscopio> sensorGiroscopio = std::make_unique<SensorGiroscopio> (100, 250, -250);

    RobotState meuRobo;
    EstadoRobo estadoAtual;

    bool ativo = true;
    while(ativo){
        double mediaDist = mediaDados(*sensorDistancia);
        double mediaLuz = mediaDados(*sensorLuz);
        double mediaGiro = mediaDados(*sensorGiroscopio);

        std::cout << "\nRelatorio Sensores\n";
        std::cout << "Sensor Distancia: " << mediaDist << std::endl;
        std::cout << "Sensor Luz: " << mediaLuz << std::endl;
        std::cout << "Sensor Giro: " << mediaGiro << std::endl;

        if (mediaDist < 10.00) {
            meuRobo.pertoDeObstaculo = true;
        } else {
            meuRobo.pertoDeObstaculo = false;
        }

        if (mediaLuz < 100.00) {
            meuRobo.estaEscuro = true;
        } else {
            meuRobo.estaEscuro = false;
        }

        if (mediaGiro < 50.00 && mediaGiro > 0) {
            meuRobo.estaEstavel = true;
        } else {
            meuRobo.estaEstavel = false;
        }

        if (meuRobo.pertoDeObstaculo) {
            estadoAtual = PERIGO;
        } else if (meuRobo.estaEscuro) {
            estadoAtual = ESCURO;
        } else if (!meuRobo.estaEstavel) {
            estadoAtual = INSTAVEL;
        } else {
            estadoAtual = NORMAL;
        }

        switch (estadoAtual) {
            case PERIGO:
                std::cout << "ALERTA: Obstaculo muito proximo!" << std::endl;
                break;

            case ESCURO:
                std::cout << "AVISO: Ambiente escuro detectado." << std::endl;
                break;

            case INSTAVEL:
                std::cout << "INSTAVEL: Movimento instavel (giroscopio alto)." << std::endl;
                break;

            case NORMAL:
                std::cout << "NORMAL: Operando normalmente." << std::endl;
                break;

            default:
                std::cout << "STATUS: Desconhecido." << std::endl;
                break;
        }

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