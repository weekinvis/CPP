#include <algorithm>
#include <vector>
#include "trataArq.hpp"
#include "comparacoes.hpp"

using namespace std;

extern void cmdCls();
extern string comando;
extern bool processaComando(string& comando);
extern bool possui(const string& comando, const string trecho);
extern void obtemComando(string& comando);
extern void criaArquivoIn();

int main(int argc, char** argv) {
    defineEntradaESaida(argv[0]);

    #ifdef _WIN32
        system("mkdir arqvs >nul 2>nul");
    #else
        system("mkdir -p arqvs");
    #endif

    criaArquivoIn();
    cmdCls();
    cout << "bdop - netstudent [digite help para ajuda...]" << endl;

    comando = "ler";
    processaComando(comando);

    while (comando != "sair") {
        cout << "> ";
        getline(cin, comando);
        if (!processaComando(comando)) {
            cout << "Erro" << endl;
        } else {
            cout << "OK" << endl;
        }
    }

    return 0;
}