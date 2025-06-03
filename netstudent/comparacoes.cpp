#include "trataArq.hpp"
#include "comparacoes.hpp"

bool comparaNotasFinais(const materia& a, const materia& b) 
{
    return a.getSomaNotas() > b.getSomaNotas();
}

bool comparaPorNome(const materia& a, const materia& b) 
{
    return a.getNome() < b.getNome();
}

bool comparaPorAulasDadas(const materia& a, const materia& b)
{
    return a.getAulasDadas() > b.getAulasDadas();
}

bool comparaPorFaltas(const materia& a, const materia& b)
{
    return a.getFaltas() > b.getFaltas();
}