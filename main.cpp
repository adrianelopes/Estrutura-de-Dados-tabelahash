#include <iostream>
#include <string>
#include "tabelahash.cpp"

using namespace std;

int main()
{
    // Capacidade esperada: 30 objetos
    TabelaHashDuplo<int, string> tabela(30);

    // Inserções de exemplo (chave => valor):
    // Caixa 0, segundo nível 0: 0 e 20
    tabela.inserir(0, "João");   // Nível 1: 0 MOD 10 = 0  e (0/10) MOD 3 = 0
    tabela.inserir(30, "Marco"); // Nível 1: 30 MOD 10 = 0  e (30/10) MOD 3 = 0

    // Caixa 0, segundo nível 2: 10
    tabela.inserir(20, "Marina"); // Nível 1: 10 MOD 10 = 0  e (20/10) MOD 3 = 2

    // Caixa 8, segundo nível 1: 18
    tabela.inserir(18, "Julia"); // Nível 1: 18 MOD 10 = 8  e (18/10) MOD 3 = 1

    // Caixa 8, segundo nível 2: 28 e 58
    tabela.inserir(28, "Antônio"); // Nível 1: 28 MOD 10 = 8  e (28/10) MOD 3 = 2
    tabela.inserir(58, "José");    // Nível 1: 58 MOD 10 = 8  e (58/10) MOD 3 = 2

    // Recuperação e exibição
    string valor;

    cout << "Caixa [0][0]: ";
    if (tabela.obter(0)) // João
        cout << *tabela.obter(0) << " -> ";
    if (tabela.obter(30)) // Marco
        cout << *tabela.obter(30);
    cout << endl;

    cout << "Caixa [0][2]: ";
    if (tabela.obter(20)) // Marina
        cout << *tabela.obter(20);
    cout << endl;

    cout << "Caixa [8][1]: ";
    if (tabela.obter(18)) // Julia
        cout << *tabela.obter(18);
    cout << endl;

    cout << "Caixa [8][2]: ";
    if (tabela.obter(28)) // Antônio
        cout << *tabela.obter(28) << " -> ";
    if (tabela.obter(58)) // José
        cout << *tabela.obter(58);
    cout << endl;

    return 0;
}
