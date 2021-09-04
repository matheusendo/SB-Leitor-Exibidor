/**Compilado no Windows 10 utilizando gcc,
 * g++ -std=c++11 *.cpp -o leitor
 * isso cria um executável chamado leitor
 * execução: ./leitor.exe "nome do arquivo de teste"
 * o arquivo de teste deve estar na mesma pasta do executavel
 * só coloquei para printar na telas uns testes de valores     **/ 


#include <iostream>
#include <string>
#include <vector>
#include "arquivoClasse.h"
#include "leClasse.h"
using namespace std;


int main(int argc, char *argv[]){

    const char *nome_classe = argv[1];
    FILE *fp = fopen(nome_classe, "rb");
    if (fp == NULL) {
        cout << "Erro ao abrir o arquivo : " << nome_classe << endl;
        exit;
    }
    ArquivoClasse * classe = new ArquivoClasse(fp);
    cout<<"Magic number = "<<classe->getMagicNumber()<<endl;
    cout<<"Minor version = "<<classe->getMinorVersion()<<endl;
    cout<<"Major version = "<<classe->getMajorVersion()<<endl;
    cout<<"Interfaces count = "<<classe->getInterfacesCount()<<endl;
    cout<<"Fields count = "<<classe->getFieldsCount()<<endl;
    cout<<"Methods count = "<<classe->getMethodsCount()<<endl;
    return 0;
}