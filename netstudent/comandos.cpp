#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <functional>
#include <vector>
#include <fstream>
#include <algorithm>
#include "trataArq.hpp"
#include "comparacoes.hpp"

using namespace std;

static vector<materia> materias;
string comando;

void cmdCls() {
    system("cls || clear");
}

void cmdExit() {
    comando = "sair";
}

void cmdHelp() {
    cout << "\nAjuda:\n"
         << "'sair' -> Encerra a execução do programa.\n"
         << "'ler' -> Lê o arquivo atual e carrega os dados nas classes.\n"
         << "'sort [nome|nf|falta|aula]' -> Ordena os dados por critério.\n"
         << "'media [nf|falta]' -> Exibe médias gerais.\n"
         << "'mostrar' ou 'ls' -> Imprime todos os dados.\n"
         << "'criarin' -> Cria ou limpa o arquivo de entrada.\n"
         << "'cls' -> Limpa a tela do terminal.\n\n";
}

void cmdCriarIn() {
    ofstream arquivo(ENTRADA);
    arquivo.close();
}

void cmdLer() {
    materias = lerDadosTratados();
    if (materias.empty()) {
        cerr << "Erro: Nenhum dado foi lido." << endl;
    }
}

void cmdSort(const string& arg) {
    if (arg.find("nome") != string::npos) {
        sort(materias.begin(), materias.end(), comparaPorNome);
    } else if (arg.find("nf") != string::npos) {
        sort(materias.begin(), materias.end(), comparaNotasFinais);
    } else if (arg.find("falta") != string::npos) {
        sort(materias.begin(), materias.end(), comparaPorFaltas);
    } else if (arg.find("aula") != string::npos) {
        sort(materias.begin(), materias.end(), comparaPorAulasDadas);
    } else {
        cerr << "Parametro invalido. Esperado nome, nf, falta ou aula." << endl;
    }
}

void cmdMedia(const string& arg) {
    if (materias.empty()) {
        cerr << "Erro: Nenhuma matéria disponível." << endl;
        return;
    }

    if (arg.find("nf") != string::npos) {
        double soma = 0.0;
        for (const auto& m : materias) soma += m.getSomaNotas();
        cout << "Media das notas finais: " << soma / materias.size() << endl;
    } else if (arg.find("falta") != string::npos) {
        int faltas = 0, aulas = 0;
        for (const auto& m : materias) {
            faltas += m.getFaltas();
            aulas += m.getAulasDadas();
        }
        cout << "Media das faltas: " << (double)(faltas) / aulas << endl;
    } else {
        cerr << "Erro: parâmetro inválido para media." << endl;
    }
}

void cmdMostrar(const string&) {
    cmdCls();
    for (auto& m : materias)
        m.getData();
}

static const map<string, function<void()>> comandosSemArg = {
    {"cls", cmdCls},
    {"exit", cmdExit},
    {"sair", cmdExit},
    {"ajuda", cmdHelp},
    {"help", cmdHelp},
    {"ler", cmdLer},
    {"criarin", cmdCriarIn}
};

static const map<string, function<void(const string&)>> comandosComArg = {
    {"sort", cmdSort},
    {"ordenar", cmdSort},
    {"media", cmdMedia},
    {"mostrar", cmdMostrar},
    {"ls", cmdMostrar}
};

bool processaComando(string& comandoCompleto) {
    comandoCompleto += " ";                                             // garante que havera, no minimo, um espaco
    string cmd = comandoCompleto.substr(0, comandoCompleto.find(' '));  // extrai tudo o que esta antes do primeiro espaco.
    string arg = comandoCompleto.substr(comandoCompleto.find(' ') + 1); // tudo apos o primeiro espaco
    cmd = cmd.empty() ? comandoCompleto : cmd;                          // se cmd estiver vazio, ele assume comando completo

    auto itSemArg = comandosSemArg.find(cmd);
    if (itSemArg != comandosSemArg.end()) {
        itSemArg->second();
        return true;
    }

    auto itComArg = comandosComArg.find(cmd);
    if (itComArg != comandosComArg.end()) {
        itComArg->second(arg);
        return true;
    }

    cerr << "Comando não encontrado!" << endl;
    return false;
}
