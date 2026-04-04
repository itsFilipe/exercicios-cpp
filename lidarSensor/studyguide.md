# Guia de Estudos: Lidar Sensor com Zero-Copy Pipeline

Este projeto serve como uma prova de conceito de como sistemas do mundo real (como carros autônomos ou robôs com ROS) processam enormes blocos de dados.

O foco central aqui é dominar o "repasse de responsabilidade" usando **Smart Pointers** (`std::unique_ptr`) baseados no princípio RAII, permitindo manipular grandes quantidades de dados com altíssima performance, sem duplicá-los ou causar travamentos de Memória RAM (Stack Overflows).

---

## 1. O Problema das Simulações Tradicionais (Sem Pointers)
Se um componente do carro chamado `Sensor` for gerar um milhão de leituras Lidar, tentar colocar um `std::vector<int> dados(1000000)` do modo padrão alocaria essas informações na *Stack* (a pilha rápida e minúscula do programa). 
Consequências:
- O PC "estouraria" causando fechamento fatal do script.
- Se passássemos esse "Vetor de um milhão" do `Lidar` pro `Filtro`, o compilador o **copiaria**, travando a CPU para escrever tudo na RAM duas vezes seguidas a cada milissegundo.

---

## 2. A Arquitetura Otimizada (O que construímos)

Construímos um **Pipeline (Escalonamento de Dados)** que divide responsabilidades:

1. **`LidarSensor`**: O Módulo Emissor. Ele é responsável por alocar os dados de forma correta e segura na **Heap** (memória que vai crescer livremente pela placa RAM). Ao invés de entregar o grande vetor de dados, ele joga o peso pra Heap e entrega a nós um Controle Direto e absoluto (`std::unique_ptr`).
2. **`LidarFilter`**: O Módulo Receptor / Processador. Pede a propriedade (Ownership) do ponteiro gerado para apagar os detritos e falsos ruídos do sensor ("limpar" tudo).
3. **`main.cpp`**: O Maestro. Gerencia o fluxo pedindo emprestado as instâncias.

---

## 3. O 'Pulo do Gato': Por dentro do Código

### A. Criando diretamente na Heap com Estabilidade
```cpp
// Em lidarSensor.cpp:
std::unique_ptr<std::vector<int>> vec_ptr = std::make_unique<std::vector<int>>(1000);
```
O método `ReadData` instancia 1000 leituras diretamente na Heap. Caso uma exceção fatal acontecesse depois de preencher 500 delas, o robô não perderia memória no desespero. O pacote é seguro.

### B. A "Transferência a Custo Zero" (`std::move`)
Este foi o objetivo absoluto onde passamos de um código amador para nível corporativo.
```cpp
// Em main.cpp:
// 1. Recebemos e nos tornamos o Dono Único dos dados cruz.
std::unique_ptr<std::vector<int>> raw_ptr = sensor.ReadData();

// 2. Não podemos ter dois donos! Passamos a bola (Move) pra mão da função Filtro.
// Nesse exato centésimo, `raw_ptr` fica "nulo" pois empurrou o pacote pra frente com sucesso:
std::unique_ptr<std::vector<int>> clean_ptr = filter.applyFilter(std::move(raw_ptr));
```
A função do Filtro recebeu aquela memória e *nunca abriu uma segunda via ou a copiou*.

### C. Tirando o Lixo Rápido (O Filtro C++)
```cpp
// Em lidarFilter.cpp:
// Ignora coisas fora de alcance nativamente
auto pos_desejada = std::remove_if(rawData->begin(), rawData->end(), [this](int dist) {
    return dist < min || dist > max;
});
rawData->erase(pos_desejada, rawData->end());
// O tamanho encolhe!
```
Ao invés de fazer um "for e if", nós usamos a biblioteca do C++ nativa para empurrar as distâncias invalidas para o abismo do array (`remove_if`) e então dar um machado que cota e anula aquele fim bruto (`erase`). A velocidade de processamento é drastica e eficiente.

---

## 4. O Ganho
- O Lidar pode bater milhões de quadros. E como tudo isso opera pela "troca de bastões", copiamos literalmente 0 Kilobytes de cópia adicional e a CPU não faz esforço secundário.
- Quando a variável de ponteiro morre pela finalização de seu uso na arquitetura, ela detona todo aquele lixo atrelado de forma automatizada (*Nenhum Leak de Memória*).
