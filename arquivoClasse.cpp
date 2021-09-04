#include <iostream>
#include "arquivoClasse.h"
#include "leClasse.h"
#include "tipos.h"
using namespace std;

ArquivoClasse::ArquivoClasse() {}

// Construtor
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

void ArquivoClasse::setMagicNumber(FILE * fp) {
    LeClasse magic_Number;
    
    magicNumber = magic_Number.readU4(fp);
}


void ArquivoClasse::setMinorVersion(FILE * fp) {
    LeClasse minor_Version;
    minorVersion = minor_Version.readU2(fp);
}

void ArquivoClasse::setMajorVersion(FILE * fp) {
    LeClasse major_Version;
    majorVersion = major_Version.readU2(fp);
}

void ArquivoClasse::setConstantPoolSize(FILE * fp) {
    LeClasse cpSize;
    constantPoolSize = cpSize.readU2(fp);
}

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


void ArquivoClasse::setAccessFlags(FILE * fp) {
    LeClasse flags;
    accessFlags = flags.readU2(fp);
}

void ArquivoClasse::setThisClass(FILE * fp) {
    LeClasse this_Class;
    thisClass = this_Class.readU2(fp);
}

void ArquivoClasse::setSuperClass(FILE * fp) {
    LeClasse super_Class;
    superClass = super_Class.readU2(fp);
}

void ArquivoClasse::setInterfacesCount(FILE * fp) {
    LeClasse interfaces_Count;
    interfacesCount = interfaces_Count.readU2(fp);
}

void ArquivoClasse::setInterfaces(FILE * fp) {
    int contador = interfacesCount;
    for (int i = 0; i < contador; i++) {
        u2 interface = LeClasse().readU2(fp);
        interfaces.push_back(interface);
    }
}

void ArquivoClasse::setFieldsCount(FILE * fp) {
    LeClasse fields_count;
    fieldsCount = fields_count.readU2(fp);
}

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

void ArquivoClasse::setMethodsCount(FILE * fp) {
    LeClasse methods_count;
    methodsCount = methods_count.readU2(fp);
}


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

void ArquivoClasse::setAttributesCount(FILE * fp) {
    LeClasse attributes_count;
    attributesCount = attributes_count.readU2(fp);
}

void ArquivoClasse::setAttributes(FILE * fp) {
    int contador = attributesCount;
    for (int i = 0; i < contador; i++) {
        attributes.push_back(LeClasse().getAttributeInfo(fp,constantPool));
    }
}

u4 ArquivoClasse::getMagicNumber() {
    return magicNumber;
}

u2 ArquivoClasse::getMinorVersion() {
    return minorVersion;
}

u2 ArquivoClasse::getMajorVersion() {
    return majorVersion;
}

u2 ArquivoClasse::getConstantPoolSize() {
    return constantPoolSize;
}

vector<cp_info> ArquivoClasse::getConstantPool() {
    return constantPool;
}

u2 ArquivoClasse::getAccessFlags() {
    return accessFlags;
}

u2 ArquivoClasse::getThisClass() {
    return thisClass;
}

u2 ArquivoClasse::getSuperClass() {
    return superClass;
}

u2 ArquivoClasse::getInterfacesCount() {
    return interfacesCount;
}

vector<u2> ArquivoClasse::getInterfaces() {
    return interfaces;
}

u2 ArquivoClasse::getFieldsCount() {
    return fieldsCount;
}

vector<field_info> ArquivoClasse::getFields() {
    return fields;
}

u2 ArquivoClasse::getMethodsCount() {
    return methodsCount;
}

vector<method_info> ArquivoClasse::getMethods() {
    return methods;
}

u2 ArquivoClasse::getAttributesCount(){
    return attributesCount;
}

vector<attribute_info> ArquivoClasse::getAttributes(){
    return attributes;
}