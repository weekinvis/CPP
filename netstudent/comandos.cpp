#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "trataArq.hpp"
#include "comparacoes.hpp"
#include "algorithm"
#include <map>
#include <functional>

using namespace std;

bool possui(const string& comando, const string trecho) {
    return comando.find(trecho) != string::npos;
}

void obtemComando(string& comando) {
    cout << ">>> ";
    getline(cin, comando);

    for(int p = 0; p < comando.length(); p++) {
        comando[p] = tolower(comando[p]);
    }
}

bool processaComando(string& comando, vector<materia>& materias) {

    static const map<string, function<void()>> comandosSemArg;

    if(comando == "sair" || comando == "exit") {
        comando = "sair";
        return true;
    }

    if(comando == "criarin") {
        ofstream arquivo(ENTRADA);
        arquivo.close();
        return true;
    }

    if(comando == "ler") {
        materias = lerDadosTratados();
        if(materias.empty()) {
            return false;
        }
        return true;
    }
    
    if(comando == "cls") {
        system("clear || cls");
        return true;
    }

    if(comando == "help") {
        cout << endl << "Ajuda: " << endl;
        cout << "'Sair' -> Encerra a execucao do programa." << endl;
        cout << "'Ler' -> Le o arquivo atual de input e formata, salvando os dados em uma classe." << endl;
        cout << "'Sort' ou 'Ordenar' (pam) -> Ordena pelo pam (nome, nf, nts fns, falta ou aula)." << endl;
        cout << "'Mostrar' ou 'ls' -> Imprime todas as notas." << endl;
        cout << "'criarIn' -> Cria ou, se ja existir, limpa o arquivo de entrada." << endl;
        cout << "'cls' -> Limpa a tela do terminal." << endl;
        cout << "'Media' (pam) -> Imprime a media dos parametros (nf, falta)," << endl << endl;
        return true;
    }
    
    if(possui(comando, "sort") || possui(comando, "ordenar")) {
        if(possui(comando, "nome")) {
            sort(materias.begin(), materias.end(), comparaPorNome);
            return true;
        }
        if(possui(comando, "nf") || possui(comando, "nts fns")) {
            sort(materias.begin(), materias.end(), comparaNotasFinais);
            return true;
        }
        if(possui(comando, "falta")) {
            sort(materias.begin(), materias.end(), comparaPorFaltas);
            return true;
        }
        if(possui(comando, "aulas") || possui(comando, "aula")) {
            sort(materias.begin(), materias.end(), comparaPorAulasDadas);
            return true;
        }
        cout << "Esperado nome, nf, nts fns, falta ou aula." << endl;
        return false;

    }
    
    if(possui(comando, "media")) {
        if(possui(comando, "nf")) {
            double media = 0.0;
            int i = 0;
            for(materia mt : materias) {
                media += mt.getSomaNotas();
                i++;
            }
            if(i == 0) {
                cerr << "Nao eh possivel calcular a media. Nao existem notas." << endl;
                return false;
            }
            cout << "Media geral: " << media / i << endl;
            return true;
        }
        if(possui(comando, "falta")) {
            int aulasDadas = 0;
            int faltas = 0;
            int i = 0;
            for(materia mt : materias) {
                aulasDadas += mt.getAulasDadas();
                faltas += mt.getFaltas();
                i++;
            }
            if(i == 0) {
                cerr << "Nao eh possivel calcular a media. Nao existem materias." << endl;
                return false;
            }
            cout << "Media de faltas gerais: " << faltas / (1.0 * aulasDadas) << endl;
            return true;
        }
    }

    if(comando == "mostrar" || comando == "ls") {
        system("cls || clear");
        for(materia mt : materias) {
            mt.getData();
        }
        return true;
    }

    cout << "Comando nao encontrado!" << endl;
    return false;

}
