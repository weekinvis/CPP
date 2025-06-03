#include <algorithm>
#include <vector>
#include "trataArq.hpp"
#include "comparacoes.hpp"
#include "comandos.hpp"

using namespace std;

extern string comando;

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