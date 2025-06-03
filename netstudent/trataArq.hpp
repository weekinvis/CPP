#pragma once
#ifndef bdop_trataArq_h__
#define bdop_trataArq_h__

#define ENTRADA "E:\\CPP\\netstudent\\arqvs\\in.txt"
#define SAIDA   "E:\\CPP\\netstudent\\arqvs\\out.txt"

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

const std::vector<std::string> colunas = {
    "Nome", "N1", "F1", "AD1", "NR1", "NT1", 
    "N2", "F2", "AD2", "NR2", "NT2", 
    "N3", "F3", "AD3", "NR3", "NT3", 
    "NRF", "FF", "ADF", "%", "SIT"};
// pt

class materia {
    private:
        int nTrimestres = 3;
        std::string nome;
        std::vector<float> notasTrim = std::vector<float>(nTrimestres + 1, 0.0);
        std::vector<float>  notasRec = std::vector<float>(nTrimestres    , 0.0);  
        std::vector<int>  aulasDadas = std::vector<int>  (nTrimestres + 1, 0);
        std::vector<int>      faltas = std::vector<int>  (nTrimestres + 1, 0);

    public:
        materia(std::string nome, std::vector<float> notasTrim, std::vector<float> notasRec, std::vector<int> faltas, std::vector<int> aulasDadas)  
        {   
            this->nome = nome;
            this->notasTrim = notasTrim;
            this->notasRec = notasRec;
            this->faltas = faltas;
            this->aulasDadas = aulasDadas;

            for(int p = 0; p < nTrimestres; p++) {
                this->notasTrim[nTrimestres] += this->notasTrim[p];
                this->aulasDadas[nTrimestres] += this->aulasDadas[p];
                this->faltas[nTrimestres] += this->faltas[p];
            }

        }

        void getData()
        {
            using std::cout;
            using std::endl;
            using std::setw;
            using std::left;
            using std::right;

            const int labelWidth = 12;  // Largura para rótulos
            const int dataWidth = 6;     // Largura para dados
            const int headerWidth = 8;   // Largura para cabeçalhos de trimestre

            cout << endl << "Materia: " << nome << endl << endl;

            // Cabeçalho dos trimestres
            cout << left << setw(labelWidth) << " " << "|";
            for (int i = 0; i < nTrimestres; ++i) {
                cout << right << setw(headerWidth) << "T" + std::to_string(i+1) << "|";
            }
            cout << right << setw(headerWidth) << "Total" << "|" << endl;

            // Linha separadora
            cout << std::string(labelWidth + (nTrimestres + 1) * (headerWidth + 1), '-') << endl;

            // Notas
            cout << left << setw(labelWidth) << "Notas" << "|";
            for (int i = 0; i < nTrimestres; ++i) {
                cout << right << setw(headerWidth) << notasTrim[i] << "|";
            }
            cout << right << setw(headerWidth) << notasTrim[nTrimestres] << "|" << endl;

            // Faltas
            cout << left << setw(labelWidth) << "Faltas" << "|";
            for (int i = 0; i < nTrimestres; ++i) {
                cout << right << setw(headerWidth) << faltas[i] << "|";
            }
            cout << right << setw(headerWidth) << faltas[nTrimestres] << "|" << endl;

            // Aulas Dadas
            cout << left << setw(labelWidth) << "Aulas Dadas" << "|";
            for (int i = 0; i < nTrimestres; ++i) {
                cout << right << setw(headerWidth) << aulasDadas[i] << "|";
            }
            cout << right << setw(headerWidth) << aulasDadas[nTrimestres] << "|" << endl;

            cout << endl << "---------------------------------------------" << endl;
        }

        std::string getNome() const {
            return this->nome;
        }

        float getSomaNotas() const {
            return this->notasTrim[nTrimestres];
        }

        int getAulasDadas() const {
            return this->aulasDadas[nTrimestres];
        }

        int getFaltas() const {
            return this->faltas[nTrimestres];
        }

};

std::vector<materia> lerDadosTratados();

#endif
