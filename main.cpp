/**Compilado no Windows 10 utilizando gcc,
 * g++ -std=c++11 *.cpp -o leitor
 * isso cria um executável chamado leitor
 * execução: ./leitor.exe "nome do arquivo de teste"
 * o arquivo de teste deve estar na mesma pasta do executavel
 * só coloquei para printar na telas uns testes de valores     **/ 


#include <iostream>
#include <string>
#include <vector>
#include "arquivoClasse.hpp"
#include "leClasse.hpp"
#include "exibidor.hpp"
using namespace std;


int main(int argc, char *argv[]){

    const char *nome_classe = argv[1];
    const char *saida = argv[2];
    FILE *fp = fopen(nome_classe, "rb");
    if (fp == NULL) {
        cout << "Erro ao abrir o arquivo : " << nome_classe << endl;
        exit;
    }
    
    ArquivoClasse * classe = new ArquivoClasse(fp);
    
    FILE *fp1 = fopen(saida, "rb+");
    if(fp1 == NULL){
        fp1 = fopen(saida, "wb");
    }
    Exibidor * exibidor = new Exibidor(*classe,fp1);
    fclose(fp);
    fclose(fp1);
    return 0;
}