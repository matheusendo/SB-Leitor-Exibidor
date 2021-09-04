#include <iostream>
#include "arquivoClasse.hpp"
#include "leClasse.hpp"
#include "tipos.hpp"
using namespace std;

/** \file arquivoClasse.cpp
 * Arquivo referente à classe arquivoClasse, que possui mesma estrutura de um arquivo .class.
 * Métodos get e set para todos seus campos.
 */

ArquivoClasse::ArquivoClasse() {}

/**
Construtor, utiliza os métodos set para setar seus atributos.
@param *fp ponteiro para o arquivo .class sendo lido.
*/
ArquivoClasse::ArquivoClasse(FILE * fp) {
    this->setMagicNumber(fp);
    this->setMinorVersion(fp);
    this->setMajorVersion(fp);
    this->setConstantPoolSize(fp);
    this->setConstantPool(fp);
    this->setAccessFlags(fp);
    this->setThisClass(fp);
    this->setSuperClass(fp);
    this->setInterfacesCount(fp);
    this->setInterfaces(fp);
    this->setFieldsCount(fp);
    this->setFields(fp);
    this->setMethodsCount(fp);
    this->setMethods(fp);
    this->setAttributesCount(fp);
    this->setAttributes(fp);
}

/**
Seta o valor do magicNumber a partir da leitura do arquivo .class com o método readU4.
@param *fp ponteiro para o arquivo .class sendo lido.
*/

void ArquivoClasse::setMagicNumber(FILE * fp) {
    LeClasse magic_Number;
    
    magicNumber = magic_Number.readU4(fp);
}

/**
Seta o valor do minorVersion a partir da leitura do arquivo .class com o método readU2.
@param *fp ponteiro para o arquivo .class sendo lido.
*/

void ArquivoClasse::setMinorVersion(FILE * fp) {
    LeClasse minor_Version;
    minorVersion = minor_Version.readU2(fp);
}

/**
Seta o valor do majorVersion a partir da leitura do arquivo .class com o método readU2.
@param *fp ponteiro para o arquivo .class sendo lido.
*/

void ArquivoClasse::setMajorVersion(FILE * fp) {
    LeClasse major_Version;
    majorVersion = major_Version.readU2(fp);
}

/**
Seta o valor do constantPoolSize a partir da leitura do arquivo .class com o método readU2.
@param *fp ponteiro para o arquivo .class sendo lido.
*/

void ArquivoClasse::setConstantPoolSize(FILE * fp) {
    LeClasse cpSize;
    constantPoolSize = cpSize.readU2(fp);
}

/**
Seta a constantPool com estrutura cp_info a partir de valores obtidos da leitura do arquivo .class. Utiliza constantPoolSize para saber
o número de entradas da tabela, o método readU1 lê a tag e dependendo da tag utiliza um método get
para a info apropriada.
@param *fp ponteiro para o arquivo .class sendo lido.
*/

void ArquivoClasse::setConstantPool(FILE * fp) {
    int cpSize = constantPoolSize - 1;
    
    for (int cp = 0; cp < cpSize; cp++) {
        uint8_t tag = LeClasse().readU1(fp);
        cp_info cpInfo;
        cpInfo.tag = tag;
        switch(tag){
            case 1:
                cpInfo.info.utf8_info = LeClasse().getUtf8Info(fp);
                constantPool.push_back(cpInfo);
            break;
            case 3:
                cpInfo.info.integer_info = LeClasse().getIntegerInfo(fp);
                constantPool.push_back(cpInfo);
            break;
            case 4:
                cpInfo.info.float_info = LeClasse().getFloatInfo(fp);
                constantPool.push_back(cpInfo);
            break;
            case 5:
                cpInfo.info.long_info = LeClasse().getLongInfo(fp);
                constantPool.push_back(cpInfo);
                cp_info cpInfo1;
                cpInfo1.tag = 0;
                constantPool.push_back(cpInfo1);
                cp++;
            break;
            case 6:
                cpInfo.info.double_info = LeClasse().getDoubleInfo(fp);
                constantPool.push_back(cpInfo);
                cp_info cpInfo2;
                cpInfo2.tag = 0;
                constantPool.push_back(cpInfo2);
                cp++;
            break;
            case 7:
                cpInfo.info.class_info = LeClasse().getClassInfo(fp);
                constantPool.push_back(cpInfo);
            break;
            case 8:
                cpInfo.info.string_info = LeClasse().getStringInfo(fp);
                constantPool.push_back(cpInfo);
            break;
            case 9:
                cpInfo.info.fieldref_info = LeClasse().getFieldRefInfo(fp);
                constantPool.push_back(cpInfo);
            break;
            case 10:
                cpInfo.info.methodref_info = LeClasse().getMethodRefInfo(fp);
                constantPool.push_back(cpInfo);
            break;
            case 11:
                cpInfo.info.interfaceMethodref_info = LeClasse().getInterfaceMethodRefInfo(fp);
                constantPool.push_back(cpInfo);
            break;
            case 12:
                cpInfo.info.nameAndType_info = LeClasse().getNameAndTypeInfo(fp);
                constantPool.push_back(cpInfo);
            break;
            case 15:
                cpInfo.info.methodHandle_info = LeClasse().getMethodHandleInfo(fp);
                constantPool.push_back(cpInfo);
            break;
            case 16:
                cpInfo.info.methodType_info = LeClasse().getMethodTypeInfo(fp);
                constantPool.push_back(cpInfo);
            break;
            case 18:
                cpInfo.info.invokeDynamic_info = LeClasse().getInvokeDynamic_info(fp);
                constantPool.push_back(cpInfo);
            break;
            
        }

    }
}

/**
Seta o valor de accessFlags a partir da leitura do arquivo .class com o método readU2.
@param *fp ponteiro para o arquivo .class sendo lido.
*/

void ArquivoClasse::setAccessFlags(FILE * fp) {
    LeClasse flags;
    accessFlags = flags.readU2(fp);
}

/**
Seta o valor de thisClass a partir da leitura do arquivo .class com o método readU2.
@param *fp ponteiro para o arquivo .class sendo lido.
*/

void ArquivoClasse::setThisClass(FILE * fp) {
    LeClasse this_Class;
    thisClass = this_Class.readU2(fp);
}

/**
Seta o valor de superClass a partir da leitura do arquivo .class com o método readU2.
@param *fp ponteiro para o arquivo .class sendo lido.
*/

void ArquivoClasse::setSuperClass(FILE * fp) {
    LeClasse super_Class;
    superClass = super_Class.readU2(fp);
}

/**
Seta o valor de interfacesCount a partir da leitura do arquivo .class com o método readU2.
@param *fp ponteiro para o arquivo .class sendo lido.
*/

void ArquivoClasse::setInterfacesCount(FILE * fp) {
    LeClasse interfaces_Count;
    interfacesCount = interfaces_Count.readU2(fp);
}

/**
Seta a tabela de interfaces a partir de valores obtidos da leitura do arquivo .class. Utiliza interfacesCount para saber
o número de entradas da tabela, o método readU2 lê o valor.
@param *fp ponteiro para o arquivo .class sendo lido.
*/

void ArquivoClasse::setInterfaces(FILE * fp) {
    int contador = interfacesCount;
    for (int i = 0; i < contador; i++) {
        u2 interface = LeClasse().readU2(fp);
        interfaces.push_back(interface);
    }
}

/**
Seta o valor de fieldsCount a partir da leitura do arquivo .class com o método readU2.
@param *fp ponteiro para o arquivo .class sendo lido.
*/

void ArquivoClasse::setFieldsCount(FILE * fp) {
    LeClasse fields_count;
    fieldsCount = fields_count.readU2(fp);
}

/**
Seta tabela de fields com estruturas field_info a partir de valores obtidos da leitura do arquivo .class. Utiliza fieldsCount para saber
o número de entradas da tabela, o método readU2 lê as informações de field_info access_flags, name_index, descriptor_index e 
attributtes_count, o último é utilizado para saber o número de atributos do field, cada atributo tem estrutura attribute_info.
 Utiliza o malloc para alocar memória com o tamanho adequado, para cada entrada de atributos utiliza o método getAttributeInfo para pegar as informações dos atributos.
@param *fp ponteiro para o arquivo .class sendo lido.
*/

void ArquivoClasse::setFields(FILE * fp) {
    int contador = fieldsCount;
    for (int i = 0; i < contador; i++) {
        field_info fieldInfo;
        fieldInfo.access_flags = LeClasse().readU2(fp);
        fieldInfo.name_index = LeClasse().readU2(fp);
        fieldInfo.descriptor_index = LeClasse().readU2(fp);
        fieldInfo.attributes_count = LeClasse().readU2(fp);
        int contador = fieldInfo.attributes_count;
        fieldInfo.attributes = (attribute_info*) malloc(contador * sizeof(attribute_info));

        for (int j = 0; j < contador; j++) {
            fieldInfo.attributes[j] = LeClasse().getAttributeInfo(fp,constantPool);
            
        }
        fields.push_back(fieldInfo);
    }
}

/**
Seta o valor de methodsCount a partir da leitura do arquivo .class com o método readU2.
@param *fp ponteiro para o arquivo .class sendo lido.
*/

void ArquivoClasse::setMethodsCount(FILE * fp) {
    LeClasse methods_count;
    methodsCount = methods_count.readU2(fp);
}

/**
Seta tabela de methods com estruturas method_info a partir de valores obtidos da leitura do arquivo .class. Utiliza methodsCount para saber
o número de entradas da tabela, o método readU2 lê as informações de method_info access_flags, name_index, descriptor_index e 
attributtes_count, o último é utilizado para saber o número de atributos de method, cada atributo tem estrutura attribute_info. 
Utiliza o malloc para alocar memória com o tamanho adequado, para cada entrada de atributos utiliza o método getAttributeInfo para pegar as informações dos atributos.
@param *fp ponteiro para o arquivo .class sendo lido.
*/

void ArquivoClasse::setMethods(FILE * fp) {
    int contador = methodsCount;
    for (int i = 0; i < contador; i++) {
        method_info methodInfo;
        methodInfo.access_flags = LeClasse().readU2(fp);
        methodInfo.name_index = LeClasse().readU2(fp);
        methodInfo.descriptor_index = LeClasse().readU2(fp);
        methodInfo.attributes_count = LeClasse().readU2(fp);
        int contador = methodInfo.attributes_count;
        methodInfo.attributes = (attribute_info*) malloc(contador * sizeof(attribute_info));
        for (int j = 0; j < contador; j++) {
            methodInfo.attributes[j] = LeClasse().getAttributeInfo(fp,constantPool);
            
        }
        methods.push_back(methodInfo);
    }
}

/**
Seta o valor de AttributesCount a partir da leitura do arquivo .class com o método readU2.
@param *fp ponteiro para o arquivo .class sendo lido.
*/

void ArquivoClasse::setAttributesCount(FILE * fp) {
    LeClasse attributes_count;
    attributesCount = attributes_count.readU2(fp);
}

/**
Seta tabela de attributes com estruturas attribute_info a partir de valores obtidos da leitura do arquivo .class. Utiliza attributesCount para saber
o número de entradas da tabela, utiliza o método getAttributeInfo para pegar as informações dos atributos.
@param *fp ponteiro para o arquivo .class sendo lido.
*/

void ArquivoClasse::setAttributes(FILE * fp) {
    int contador = attributesCount;
    for (int i = 0; i < contador; i++) {
        attributes.push_back(LeClasse().getAttributeInfo(fp,constantPool));
    }
}

/**
Retorna o valor de magicNumber.
*/

u4 ArquivoClasse::getMagicNumber() {
    return magicNumber;
}

/**
Retorna o valor de minorVersion.
*/

u2 ArquivoClasse::getMinorVersion() {
    return minorVersion;
}

/**
Retorna o valor de majorVersion.
*/

u2 ArquivoClasse::getMajorVersion() {
    return majorVersion;
}

/**
Retorna o valor de constantPoolSize.
*/

u2 ArquivoClasse::getConstantPoolSize() {
    return constantPoolSize;
}

/**
Retorna a tabela(vector) constantPool.
*/

vector<cp_info> ArquivoClasse::getConstantPool() {
    return constantPool;
}

/**
Retorna o valor de acessFlags.
*/

u2 ArquivoClasse::getAccessFlags() {
    return accessFlags;
}

/**
Retorna o valor de thisClass.
*/

u2 ArquivoClasse::getThisClass() {
    return thisClass;
}

/**
Retorna o valor de superClass.
*/

u2 ArquivoClasse::getSuperClass() {
    return superClass;
}

/**
Retorna o valor de interfacesCount.
*/

u2 ArquivoClasse::getInterfacesCount() {
    return interfacesCount;
}

/**
Retorna a tabela(vector) interfaces.
*/

vector<u2> ArquivoClasse::getInterfaces() {
    return interfaces;
}

/**
Retorna o valor de fieldsCount.
*/

u2 ArquivoClasse::getFieldsCount() {
    return fieldsCount;
}

/**
Retorna a tabela(vector) fields.
*/

vector<field_info> ArquivoClasse::getFields() {
    return fields;
}

/**
Retorna o valor de methodsCount.
*/

u2 ArquivoClasse::getMethodsCount() {
    return methodsCount;
}

/**
Retorna a tabela(vector) methods.
*/

vector<method_info> ArquivoClasse::getMethods() {
    return methods;
}

/**
Retorna o valor de attributesCount.
*/

u2 ArquivoClasse::getAttributesCount(){
    return attributesCount;
}

/**
Retorna a tabela(vector) attributes.
*/

vector<attribute_info> ArquivoClasse::getAttributes(){
    return attributes;
}