#ifndef METHODAREA_H_
#define METHODAREA_H_

#include <map>
#include "arquivoClasse.hpp"
#include "leClasse.hpp"
using namespace std;


class MethodArea {
public:
    
    map<string, ArquivoClasse*> classes;
    void adicionaClasse(ArquivoClasse*);
    ArquivoClasse* getArquivoClasse(string);
};

#endif