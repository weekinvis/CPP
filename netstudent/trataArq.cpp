#include "trataArq.hpp"
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;

void tratarDados() 
{
    ifstream arq(ENTRADA);
    ofstream sai(SAIDA);

    if(!arq.is_open()) {
        cerr << "Erro ao abrir o arquivo" << endl;
        return;
    }

    string linha;

    for(string s: colunas) {
        sai << s << " ";
    }

    while (getline(arq, linha)) {
        string tratada;
        sai << endl;

        for (size_t i = 0; i < linha.length(); ++i) {
            char c = linha[i];
            if (c == ' ') {
                if (i > 0 && i + 1 < linha.length() &&
                    isalpha(linha[i - 1]) || linha[i - 1] == '.' && isalpha(linha[i + 1])) {
                    tratada += '-'; 
                } else {
                    tratada += ' '; 
                }
            } else if (c != '\t') {
                tratada += c;
            } else {
                tratada += ' ';
            }
        }
        sai << tratada;
    }

    arq.close();
    sai.close();
    return;
}

std::vector<materia> lerDadosTratados()
{
    tratarDados();

    ifstream arq(SAIDA);
    string linha;

    if (!arq.is_open()) {
        cerr << "Erro ao abrir o arquivo tratado" << endl;
        return {};
    }

    getline(arq, linha); 
    vector<materia> materias;
    const int nTrimestres = 3;

    while (getline(arq, linha)) {
        istringstream iss(linha);
        string nome;
        iss >> nome;
        replace(nome.begin(), nome.end(), '-', ' ');

        vector<float> notasTrim(nTrimestres + 1);
        vector<float> notasRec(nTrimestres, 0.0);
        vector<int> faltas(nTrimestres + 1);
        vector<int> aulasDadas(nTrimestres + 1);

        for (int i = 0; i < nTrimestres + 1; ++i) {
            iss >> notasTrim[i] >> faltas[i] >> aulasDadas[i];
            string lixo;
            float nt;
            iss >> lixo >> nt; 
        }

        // cria e coloca
        materias.emplace_back(nome, notasTrim, notasRec, faltas, aulasDadas);
    }

    arq.close();
    return materias;
}

void criaArquivoIn() {
    std::ifstream check("arqvs/in.txt");

    if (!check.good()) {
        std::ofstream file("arqvs/in.txt");
    }
}