#pragma once

#include <vector>
#include <list>
#include <functional>

using namespace std;

template <typename C, typename V>
class TabelaHashDuplo
{
public:
    explicit TabelaHashDuplo(size_t capacidade);
    ~TabelaHashDuplo();

    void inserir(const C &chave, const V &valor);
    V *obter(const C &chave);
    bool recuperar(const C &chave, V &saida);
    size_t tamanho() const;

private:
    const size_t tamanhoTotal;
    const size_t tamanhoNivel1;
    const size_t tamanhoNivel2;
    size_t tamanhoAtual;
    vector<vector<list<pair<C, V>>> *> tabelaNivel1;

    size_t funcaoHash1(const C &chave) const;
    size_t funcaoHash2(const C &chave) const;
};

// Construtor e destrutor
template <typename C, typename V>
// O primeiro nível tem 10 posições
TabelaHashDuplo<C, V>::TabelaHashDuplo(size_t capacidade)
    : tamanhoTotal(capacidade),
      tamanhoNivel1(10),
      tamanhoNivel2((capacidade + tamanhoNivel1 - 1) / tamanhoNivel1),
      tamanhoAtual(0)
{
    tabelaNivel1.resize(tamanhoNivel1, nullptr);
    for (size_t i = 0; i < tamanhoNivel1; ++i)
    {
        tabelaNivel1[i] = new vector<list<pair<C, V>>>(tamanhoNivel2);
    }
}

template <typename C, typename V>
TabelaHashDuplo<C, V>::~TabelaHashDuplo()
{
    for (auto ptr : tabelaNivel1)
        delete ptr;
}

template <typename C, typename V>
void TabelaHashDuplo<C, V>::inserir(const C &chave, const V &valor)
{
    // Calcula as chaves
    size_t i1 = funcaoHash1(chave);
    size_t i2 = funcaoHash2(chave);
    auto &caixa = (*tabelaNivel1[i1])[i2];

    // Procura a chave
    for (auto &par : caixa)
    {
        if (par.first == chave)
        {
            par.second = valor;
            return;
        }
    }
    caixa.emplace_back(chave, valor);
    ++tamanhoAtual;
}

template <typename C, typename V>
V *TabelaHashDuplo<C, V>::obter(const C &chave)
{
    // A função retorna o ponteiro para o valor ou nullptr se não achar
    size_t i1 = funcaoHash1(chave);
    size_t i2 = funcaoHash2(chave);
    auto &caixa = (*tabelaNivel1[i1])[i2];
    for (auto &par : caixa)
    {
        if (par.first == chave)
            return &par.second;
    }
    return nullptr;
}

template <typename C, typename V>
bool TabelaHashDuplo<C, V>::recuperar(const C &chave, V &saida)
{
    V *ptr = obter(chave);
    if (ptr)
    {
        saida = *ptr;
        return true;
    }
    return false;
}

// Função para obter tamanho
template <typename C, typename V>
size_t TabelaHashDuplo<C, V>::tamanho() const
{
    return tamanhoAtual;
}

// Primeira função hash consiste em: f(chave) = chave % 10
template <typename C, typename V>
size_t TabelaHashDuplo<C, V>::funcaoHash1(const C &chave) const
{
    return hash<C>{}(chave) % tamanhoNivel1;
}

// Segunda função hash consiste em: f(chave) = (chave/10) % (n/10)
template <typename C, typename V>
size_t TabelaHashDuplo<C, V>::funcaoHash2(const C &chave) const
{
    size_t h = hash<C>{}(chave);
    return (h / 10) % tamanhoNivel2;
}
