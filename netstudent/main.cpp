#include <algorithm>
#include <vector>
#include "trataArq.hpp"
#include "comparacoes.hpp"

using namespace std;

extern bool processaComando(string& comando, vector<materia>& materias);
extern bool possui(const string& comando, const string trecho);
extern void obtemComando(string& comando);
extern void criaArquivoIn();

int main(int argc, char** argv)
{
    defineEntradaESaida(argv[0]);
    #ifdef _WIN32
        system("mkdir arqvs >nul 2>nul");
    #else
        system("mkdir -p arqvs");
    #endif

    criaArquivoIn();

    vector<materia> materias;
    string comando = "ler";
    bool okComando;

    system("clear || cls");

    cout << "bdop - netstudent [digite help para ajuda...]" << endl;

    processaComando(comando, materias);
    
    do {
        obtemComando(comando);
        okComando = processaComando(comando, materias);
        if(okComando) cout << "OK" << endl;
        else cout << "ERRO" << endl;

    } while(comando != "sair");

    return 0;
}