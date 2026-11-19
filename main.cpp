#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <climits>

using namespace std;

// Converte a opção do menu para a base númerica

int obterBase(int opcao) {
    switch (opcao) {
        case 1: return 10; // Decimal
        case 2: return 2;  // Binario
        case 3: return 8;  // Octal
        case 4: return 16; // Hexadecimal
        default: return 0; // Opcao invalida
    }
}

// Converte um caractere para seu valor numerico
// Exemplos: '9' = 9, 'A' = 10, 'F' = 15
int valorDigito(char c) {
    if (c >= '0' && c <= '9')
        return c - '0';

    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;

    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;

    return -1; // Caractere invalido
}

// Converte um numero de qualquer base para decimal
unsigned long long paraDecimal(string numero, int base) {
    unsigned long long resultado = 0;

    for (char c : numero) {
        int digito = valorDigito(c);

        // Verifica se o digito pertence a base escolhida
        if (digito < 0 || digito >= base) {
            throw invalid_argument("Digito invalido para esta base!");
        }

        // Verifica se o valor ultrapassaria o limite
        if (resultado > (ULLONG_MAX - digito) / base) {
            throw out_of_range("Numero muito grande!");
        }

        // Desloca o valor anterior e adiciona o digito
        // Exemplo decimal 123:
        // 0*10+1 = 1
        // 1*10+2 = 12
        // 12*10+3 = 123
        resultado = resultado * base + digito;
    }

    return resultado;
}

// Converte um numero decimal para qualquer base
string deDecimal(unsigned long long numero, int base) {
    const string simbolos = "0123456789ABCDEF";

    // O numero zero precisa de tratamento especial
    if (numero == 0)
        return "0";

    string resultado = "";

    // Divide repetidamente pela base desejada
    while (numero > 0) {
        int resto = numero % base;

        // Transforma o resto em caractere
        resultado += simbolos[resto];

        numero /= base;
    }

    // Os restos foram obtidos na ordem inversa
    reverse(resultado.begin(), resultado.end());

    return resultado;
}

int main() {
    int origem, destino;
    string numero;

    cout << "===== CONVERSOR DE BASES NUMERICAS =====\n";

    cout << "\nBases disponiveis:\n";
    cout << "1 - Decimal (base 10)\n";
    cout << "2 - Binario (base 2)\n";
    cout << "3 - Octal (base 8)\n";
    cout << "4 - Hexadecimal (base 16)\n";

    // Escolhe a base em que o numero esta escrito
    cout << "\nEscolha a base de ENTRADA: ";
    cin >> origem;

    // Escolhe a base para a qual deseja converter
    cout << "Escolha a base de SAIDA: ";
    cin >> destino;

    int baseOrigem = obterBase(origem);
    int baseDestino = obterBase(destino);

    // Valida as opcoes selecionadas
    if (baseOrigem == 0 || baseDestino == 0) {
        cout << "\nErro: opcao de base invalida!\n";
        return 1;
    }

    cout << "\nDigite o numero que deseja converter: ";
    cin >> numero;

    // Permite apenas inteiros nao negativos
    if (numero.empty()) {
        cout << "\nErro: numero vazio!\n";
        return 1;
    }

    try {
        // Etapa 1: converter a entrada para decimal
        unsigned long long decimal =
            paraDecimal(numero, baseOrigem);

        // Etapa 2: converter decimal para a base escolhida
        string convertido =
            deDecimal(decimal, baseDestino);

        cout << "\n===== RESULTADO =====\n";
        cout << "Numero original: " << numero << "\n";
        cout << "Base de entrada: " << baseOrigem << "\n";
        cout << "Base de saida: " << baseDestino << "\n";
        cout << "Resultado: " << convertido << "\n";

    } catch (const exception& erro) {
        cout << "\nErro: " << erro.what() << "\n";
        return 1;
    }

    return 0;
}
