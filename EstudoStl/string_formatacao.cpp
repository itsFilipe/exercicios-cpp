#include <iostream>
#include <string>

// PROBLEMA 1 — Tipo errado para o retorno de find()
// std::string::find() retorna size_t (inteiro sem sinal).
// Usar int pode causar comportamento indefinido se o valor for grande
// ou se npos for comparado incorretamente.
// SOLUÇÃO: usar size_t u_caractere = s.find(":");
std::string ManterFrase(std::string s){
    int u_caractere = s.find(":");

    if (u_caractere != std::string::npos)
        // PROBLEMA 2 — Número mágico (+2)
        // O +2 assume que SEMPRE haverá ": " (dois-pontos + espaço) após a tag.
        // Se a string for "[WARNING]:SemEspaco", o resultado fica errado.
        // SOLUÇÃO: pular só o ':' com +1 e depois remover espaços extras com um loop:
        //   while (!s.empty() && s[0] == ' ') s.erase(0, 1);
        s = s.substr(u_caractere + 2);
    
    return s;
}

// PROBLEMA 3 — Sem validação de npos em PrintTag
// Se a string não contiver '[' ou ']', find() retorna npos.
// Fazer aritmética com npos causa overflow (é um valor enorme para size_t)
// e a chamada a substr() pode crashar ou gerar lixo.
// SOLUÇÃO: validar antes de calcular:
//   if (i_caractere == npos || u_caractere == npos || u_caractere <= i_caractere)
//       return "";
std::string PrintTag(std::string s){
    int i_caractere = s.find("[");
    int u_caractere = s.find("]");

    int total_caracteres = u_caractere - (i_caractere + 1);
    s = s.substr(i_caractere + 1, total_caracteres);
    return s;
}

// PROBLEMA 4 — Duplicação de lógica (código repetido)
// FormatarFrase refaz todo o trabalho de PrintTag manualmente.
// Isso viola o princípio DRY (Don't Repeat Yourself):
// se a lógica precisar mudar, você teria que alterar em dois lugares.
// SOLUÇÃO: reutilizar as funções já existentes:
//   std::string tag = PrintTag(s);
//   std::string mensagem = ManterFrase(s);
//   return mensagem + " (" + tag + ")";
//
// PROBLEMA 5 — Número mágico (+2) novamente
// s.substr(total_caracteres + 2) assume espaço fixo após o ']'.
// Mesma fragilidade da ManterFrase.
std::string FormatarFrase(std::string s){
    int i_caractere = s.find("[");
    int u_caractere = s.find("]");
    int total_caracteres = (u_caractere + 1) - i_caractere;
    int total_caracteres_tag = u_caractere - (i_caractere + 1);

    std::string tag = s.substr(i_caractere + 1, total_caracteres_tag);
    s = s.substr(total_caracteres + 2);
    s = s + " (" + tag + ")";
    return s;
}

int main() {
    // PROBLEMA 6 — Apenas um caso de teste
    // Testar só com "[INFO]: Operation completed" não revela os bugs acima.
    // SOLUÇÃO: testar também com entradas sem espaço, sem colchetes, etc.
    //   std::string frase2 = "[WARNING]:SemEspaco";
    std::string frase = "[INFO]: Operation completed";

    std::cout << ManterFrase(frase) << std::endl;
    std::cout << PrintTag(frase) << std::endl;
    std::cout << FormatarFrase(frase) << std::endl;
    
    return 0;
}


/* sem numeros magicos, seguro, legivel, facil de manter

#include <iostream>
#include <string>

// Procura o ':' e pega tudo após ele, limpando espaços extras automaticamente
std::string ManterFrase(std::string s){
    size_t u_caractere = s.find(":");

    if (u_caractere != std::string::npos) {
        s = s.substr(u_caractere + 1); // Pula apenas o ':'
        
        // Remove espaços em branco do início se eles existirem
        while (!s.empty() && s[0] == ' ') {
            s.erase(0, 1);
        }
    }
    return s;
}

// Garante que os colchetes existem antes de calcular o tamanho da tag
std::string PrintTag(std::string s){
    size_t i_caractere = s.find("[");
    size_t u_caractere = s.find("]");

    // Validação essencial para não quebrar o programa
    if (i_caractere == std::string::npos || u_caractere == std::string::npos || u_caractere <= i_caractere) {
        return ""; // Retorna vazio se a estrutura estiver errada
    }

    size_t total_caracteres = u_caractere - (i_caractere + 1);
    return s.substr(i_caractere + 1, total_caracteres);
}

// Reaproveita as funções que você já criou (Evita repetição de código)
std::string FormatarFrase(std::string s){
    std::string tag = PrintTag(s);
    std::string mensagem = ManterFrase(s);

    if (tag.empty()) return s; // Se não tem tag, retorna a frase original

    return mensagem + " (" + tag + ")";
}

int main() {
    // Teste com o formato original
    std::string frase1 = "[INFO]: Operation completed";
    // Teste com formato sem espaço (para testar a robustez)
    std::string frase2 = "[WARNING]:System overload"; 

    std::cout << "--- Teste 1 ---" << std::endl;
    std::cout << ManterFrase(frase1) << std::endl;
    std::cout << PrintTag(frase1) << std::endl;
    std::cout << FormatarFrase(frase1) << std::endl;

    std::cout << "\n--- Teste 2 (Mais difícil) ---" << std::endl;
    std::cout << FormatarFrase(frase2) << std::endl;
    
    return 0;
}
    
*/

