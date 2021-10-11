#include "methodArea.hpp"
#include <vector>

ArquivoClasse * MethodArea::getArquivoClasse(string nome) {
    return classes[nome];
}

void MethodArea::adicionaClasse(ArquivoClasse * classe) {
    vector<cp_info> cPool = classe->getConstantPool();
    cp_info cp = cPool[classe->getThisClass()-1];
    string nome = LeClasse().getUtf8(cPool[cp.info.class_info.name_index-1]);
    if (this->classes.count(nome) == 0) {
        this->classes.insert(make_pair(nome, classe));
    }
}