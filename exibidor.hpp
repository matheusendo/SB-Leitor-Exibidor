#ifndef __EXIBIDOR_H__
#define __EXIBIDOR_H__

#include "arquivoClasse.hpp"
#include <stdio.h>

using namespace std;

class Exibidor{

private:
    ArquivoClasse classe;
    vector<string> instructions;
    string getMajorVersionAjustado(u2 majorVersion);
    string getStringConstantPool(cp_info cpInfo, vector<cp_info> constantPool);
    string getAccessFlags(u2 accessFlags);
    string getInstruction(u1 index);
    void printAttribute(string attributeName, int index, attribute_info attributeInfo, FILE *file, ArquivoClasse arq_classe);
    void printGeneralInfo(ArquivoClasse arq_classe, FILE *file);
    void printConstantPool(ArquivoClasse arq_classe, FILE *file);
    void printInterfaces(ArquivoClasse arq_classe, FILE *file);
    void printFields(ArquivoClasse arq_classe, FILE *file);
    void printMethods(ArquivoClasse arq_classe, FILE *file);
    void printAttributes(ArquivoClasse arq_classe, FILE *file);
    void setInstructions();


public:
    Exibidor(ArquivoClasse arq_classe, FILE *file);
};

#endif