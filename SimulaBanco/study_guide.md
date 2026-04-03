# Guia de Estudos Definitivo: SimulaBanco em C++

Este documento é a análise profunda e técnica da arquitetura do seu projeto "SimulaBanco". Ele repassa cada um dos conceitos da linguagem C++ que foram aplicados para garantir que sua base sobre Programação Orientada a Objetos (OOP) fique extremamente sólida para consultas futuras.

---

## 1. A Arquitetura Central (O Piloto do Projeto)
O projeto descreve o funcionamento de um sistema bancário moderno. Em vez de criar códigos repetitivos e funções soltas, foi utilizada uma abordagem orientada a objetos profissional:
* **Interfaces base:** `I_Printable` (Gerencia comunicação visual)
* **Classes base (Raiz):** `Account` (Implementa a regra de negócio básica de banco)
* **Classes Derivadas (Filhas):** `Savings_Account` (Conta Poupança), `Checking_Account` (Conta Corrente) e `Trust_Account` (Conta de Confiança).
* **Coleções e Gerenciamento:** O `main.cpp` e o `Account_Util.cpp` interagem com o sistema de forma universal, não importando o tipo de conta que seja.

---

## 2. Herança (Inheritance) - Reuso e Especialização
**Herança** é o mecanismo onde você diz para uma classe roubar (herdar) todos os atributos e habilidades de outra. Em C++, se estabelece uma relação **"É UM"** (Uma Conta Poupança *É UMA* Conta).

### Como foi usado no projeto:
```cpp
class Savings_Account : public Account { ... };
```
Ao ler isso, o compilador transfere os métodos padrão e o saldo de `Account` diretamente para a `Savings_Account`. 

### Conceitos C++ Chaves na Herança:
* **`protected` vs `private`**: Na sua classe pai `Account`, o saldo (`balance`) e o nome (`name`) foram definidos como `protected`. Se fossem `private`, as contas filhas não teriam acesso a eles. O `protected` é o meio-termo ideal: permite que os filhos herdem o acesso sem liberar a variável para o público externo (o `main.cpp`).
* **Delegação de Construtores**: No seu `Savings_Account.cpp`, você tem `Savings_Account(...) : Account{name, balance}`. Ao invés de criar o saldo e nome do zero, você invoca e repassa os dados para o construtor pai inicializá-los.
* **Aproveitamento de Métodos Pais**: No depósito da Poupança, você soma uma taxa e devolve a bola para o pai com o comando: `return Account::deposit(amount);`. Isso evita a duplicação do código que faz as verificações de saldo.

---

## 3. Polimorfismo (Polymorphism) - O Poder Dinâmico
O **Polimorfismo** (em grego "várias formas") é sem dúvida a funcionalidade mais brilhante usada no sistema. É a capacidade do C++ de tratar objetos "especiais" como sendo entidades "genéricas", enquanto ainda garante que as funções corretas operem em tempo real.

### Coleções Dinâmicas e o Padrão do Projeto
No seu `main.cpp`, você usa:
```cpp
std::vector<Account *> accounts;
accounts.push_back(new Savings_Account {"Superman"});
```
Perceba a genialidade: o vetor só sabe lidar com uma coisa genérica (`Account *`). Entretanto, você joga dentro dele vários objetos misturados (Conta Corrente, Confiança, etc). O C++ aceita, porque graças à herança, todas elas **são** Contas. O uso da palavra `new` aloca dinamicamente esses objetos e nós guardamos seus *ponteiros*.

### Late Binding (Amarração Tardia)
Quando você chama `acc->withdraw(500);` num loop no `Account_Util`, como o C++ sabe a qual classe pertence a função de saque a ser executada? E se for uma Poupança? E se for uma Conta Corrente com taxa fixa?
Essa decisão é tomada em **Runtime** (enquanto o programa roda, não ao compilar) baseada nos tipos fundamentais guardados, graças a um ponteiro especial inserido pelo compilador (uma *v-table*).

---

## 4. O Sistema de Palavras-chave do C++ (`virtual` e afins)

* **`virtual`**: Colocar isso na frente da declaração de `withdraw()` no `Account.h` é a chave do polimorfismo. Ele dá um comando específico ao C++: *"Sempre que este método for chamado usando um ponteiro/referência genérico (Account*), você DEVE parar, olhar pra memória pra descobrir que tipo real de conta mora ali e chamar a função especializada daquele tipo escondido."*
* **`override`**: Utilizado nas classes filhas (como em `Checking_Account.h`). É um protetor sintático. Ele alerta o compilador: *"Ei, eu juro solenemente que eu estou substituindo o método virtual do meu pai. Avise-me se eu tiver escrito o nome ou atributos do método de forma incorreta"*.
* **Funções Virtuais Puras (`= 0`) e Interfaces**: Se uma função é escrita como `virtual void print() = 0;`, chamamos de Função Pura (como no seu `I_Printable`). Isso converte a classe em uma **Classe Abstrata (Interface)**. O C++ proíbe o usuário de instanciar essa classe diretamente no `.cpp`. É como um documento de obrigações legais: todo mundo que assinar (herdar) esse contrato tem a obrigação de implementar a lógica de `print()`.
* **Destrutores Virtuais (`virtual ~Account() = default;`)**: Essa parte é vital. Quando criamos objetos dinâmicos através da palavra `new`, se quisermos destruí-los mais tarde através de um ponteiro pai em um vetor (usando `delete`), C++ começará deletando o contêiner do Pai (`Account`). Se o destrutor não for virtual, ele parará ali e parte da memória vitalícia da Filha será ignorada e perdida para sempre, causando um severo *memory leak*! Sendo `virtual`, o C++ busca a especialização e destrói de baixo para cima perfeitamente!

---

## 5. Sobrecarga de Operadores (Operator Overloading)
A interface `I_Printable` lida com uma peculiaridade da linguagem: nós queríamos usar a sintaxe limpa `std::cout << *acc;`. Para isso acontecer, precisamos re-programar a operação que lida com as setinhas `<<`.

* **O operador amigo (`friend`)**: Na definição da sobrecarga `friend std::ostream &operator<<`, tornamos essa operação global "amiga" da classe, a permitindo acessar qualquer estado.
* **Retornando a referência `std::ostream &`**: O seu método devolve e recebe parâmetros usando a conjunção imperativa E-comercial (`&`). Por quê? A engrenagem inteira do terminal do Linux reside neste objeto (`os`), nós não podemos nunca copiar esse objeto (o C++ te proibiria se não colocasse o `&`). Você pega e devolve a referência do stream terminal original para que comandos como `cout << a << b << c;` sejam encadeados uns nos outros.
* **O truque da sobrecarga com virtual**: Como funções globais do `operator<<` **não podem** portar o comando `virtual`, criamos uma função simples local virtual chamada `print()`. O operador global simplesmente chama `obj.print(os);`, e assim, a mágica do polimorfismo dinâmico passa a existir para consoles pela primeira vez no programa!
* **A função `inline`**: Na compilação nós inserimos a função em múltiplos lugares diferentes de arquivos. Graças ao qualificador `inline`, ensinamos o mecanismo Linker a não panicar frente às múltiplas declarações, mesclando-as globalmente juntas.

---

## 6. A Arquitetura Física `.h` versus `.cpp`
* **Arquivos Headers (`.h`)**: As diretrizes e contratos; O que existe de fato. Abrigam as *"Header Guards"* (`#ifndef _CONTA_H_`) para impedir duplo processamento ao longo do linker. Agregam valores base default e marcadores de estado explícitos (`virtual`, `override`, `static constexpr`).
* **Arquivos Logic (`.cpp`)**: Contém a materialização do raciocínio físico das operações. Empregando a mecânica Class Scope Resolution (`Account::deposit`), para alinhar globalmente um corpo lógico às declarações. Não levam qualificadores passivos, apenas a repetição sagrada do modificador constutivo (`const`) garantindo segurança de escopo. 

Esta estrutura é baseada inteiramente no seu desenvolvimento nos scripts do projeto! O uso combinado desses paradigmas produziu um trabalho profissional e conciso!
