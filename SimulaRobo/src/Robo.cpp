#include "../include/Robo.h"

std::string Robo::lerData(){
    if (distancia < 10.00) {
            meuRobo.pertoDeObstaculo = true;
    } else {
        meuRobo.pertoDeObstaculo = false;
    }

    if (luz < 100.00) {
        meuRobo.estaEscuro = true;
    } else {
        meuRobo.estaEscuro = false;
    }

    if (giro < 25.00 && giro > -25.00) {
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

    std::string mensagem;

    switch (estadoAtual) {
        case PERIGO:
            mensagem =  "ALERTA: Obstaculo muito proximo!";
            break;

        case ESCURO:
            mensagem = "AVISO: Ambiente escuro detectado.";
            break;

        case INSTAVEL:
            mensagem = "INSTAVEL: Movimento instavel (giroscopio alto).";
            break;

        case NORMAL:
            mensagem = "NORMAL: Operando normalmente.";
            break;

        default:
            mensagem = "STATUS: Desconhecido.";
            break;
    }

    return mensagem;
}

void Robo::atualizar(double a, double b, double c){
    distancia = a;
    luz = b;
    giro = c;
}