#include <cstdlib>
#include "tipos.h"
#include "leClasse.h"

using namespace std;

LeClasse::LeClasse(){}

u1 LeClasse::readU1(FILE *fp) {
    u1 toReturn = 0;
    fread(&toReturn, sizeof(u1), 1, fp);
    return toReturn;
}

u2 LeClasse::readU2(FILE *fp) {
    u2 toReturn = 0;
    for (int i = 0; i < 2; i++) {
        toReturn += readU1(fp) << (8 - 8*i);
    }
    return toReturn;
}

u4 LeClasse::readU4(FILE *fp) {
    u4 toReturn = 0;
    for (int i = 0; i < 4; i++) {
        toReturn += readU1(fp) << (24 - 8*i);
    } 
    return toReturn;
}

CONSTANT_Utf8_info LeClasse::getUtf8Info(FILE *fp){
    CONSTANT_Utf8_info toReturn;
    toReturn.length = readU2(fp);
    int contador = toReturn.length;
    toReturn.bytes = (u1*) malloc(contador * sizeof(u1));
    for (int i = 0; i < contador; i++) {
        toReturn.bytes[i] = readU1(fp);
    }
    return toReturn;
}

CONSTANT_Integer_info LeClasse::getIntegerInfo(FILE *fp) {
    CONSTANT_Integer_info toReturn;
    toReturn.bytes = readU4(fp);
    return toReturn;
}

CONSTANT_Float_info LeClasse::getFloatInfo(FILE *fp) {
    CONSTANT_Float_info toReturn;
    toReturn.bytes = readU4(fp);
    return toReturn;
}

CONSTANT_Long_info LeClasse::getLongInfo(FILE *fp) {
    CONSTANT_Long_info toReturn;
    toReturn.high_bytes = readU4(fp);
    toReturn.low_bytes = readU4(fp);
    return toReturn;
}

CONSTANT_Double_info LeClasse::getDoubleInfo(FILE *fp) {
    CONSTANT_Double_info toReturn;
    toReturn.high_bytes = readU4(fp);
    toReturn.low_bytes = readU4(fp);
    return toReturn;
}

CONSTANT_Class_info LeClasse::getClassInfo(FILE *fp) {
    CONSTANT_Class_info toReturn;
    toReturn.name_index = readU2(fp);
    return toReturn;
}

CONSTANT_String_info LeClasse::getStringInfo(FILE *fp) {
    CONSTANT_String_info toReturn;
    toReturn.string_index = readU2(fp);
    return toReturn;
}

CONSTANT_Fieldref_info LeClasse::getFieldRefInfo(FILE *fp) {
    CONSTANT_Fieldref_info toReturn;
    toReturn.class_index = readU2(fp);
    toReturn.name_and_type_index = readU2(fp);
    return toReturn;
}

CONSTANT_Methodref_info LeClasse::getMethodRefInfo(FILE *fp) {
    CONSTANT_Methodref_info toReturn;
    toReturn.class_index = readU2(fp);
    toReturn.name_and_type_index = readU2(fp);
    return toReturn;
}

CONSTANT_InterfaceMethodref_info LeClasse::getInterfaceMethodRefInfo(FILE *fp) {
    CONSTANT_InterfaceMethodref_info toReturn;
    toReturn.class_index = readU2(fp);
    toReturn.name_and_type_index = readU2(fp);
    return toReturn;
}

CONSTANT_NameAndType_info LeClasse::getNameAndTypeInfo(FILE *fp) {
    CONSTANT_NameAndType_info toReturn;
    toReturn.name_index = readU2(fp);
    toReturn.descriptor_index = readU2(fp);
    return toReturn;
}

CONSTANT_MethodHandle_info LeClasse::getMethodHandleInfo(FILE *fp){
    CONSTANT_MethodHandle_info toReturn;
    toReturn.reference_kind = readU1(fp);
    toReturn.reference_index = readU2(fp);
    return toReturn;
}

CONSTANT_MethodType_info LeClasse::getMethodTypeInfo(FILE *fp){
    CONSTANT_MethodType_info toReturn;
    toReturn.descriptor_index = readU2(fp);
    return toReturn;
}

CONSTANT_InvokeDynamic_info LeClasse::getInvokeDynamic_info(FILE *fp){
    CONSTANT_InvokeDynamic_info toReturn;
    toReturn.bootstrap_method_attr_index = readU2(fp);
    toReturn.name_and_type_index = readU2(fp);
    return toReturn;
}


string LeClasse::getUtf8(cp_info cpInfo){
    string toReturn;
    int contador = cpInfo.info.utf8_info.length;
    for (int i = 0 ; i < contador; i++){
        toReturn.push_back(cpInfo.info.utf8_info.bytes[i]);
    }
    return toReturn;
}

ExceptionTable LeClasse::getExceptionTable(FILE *fp) {
    ExceptionTable toReturn;
    toReturn.start_pc = readU2(fp);
    toReturn.end_pc = readU2(fp);
    toReturn.handler_pc = readU2(fp);
    toReturn.catch_type = readU2(fp);
    return toReturn;
}

attribute_info LeClasse::getAttributeInfo(FILE *fp, vector<cp_info> constantPool){
    attribute_info attributeInfo;
    attributeInfo.attribute_name_index = LeClasse().readU2(fp);
    attributeInfo.attribute_length = LeClasse().readU4(fp);
    string name = getUtf8(constantPool[attributeInfo.attribute_name_index-1]); 
    if(name == "Code"){
        attributeInfo.info.code_info = LeClasse().getCodeAttribute(fp,constantPool);

    }else if (name == "LineNumberTable") {
        attributeInfo.info.lineNumberTable_info = LeClasse().getLineNumberTableAttribute(fp);

    } else if (name == "LocalVariableTable") {
        attributeInfo.info.localVariableTable_info = LeClasse().getLocalVariableAttribute(fp);

    } else if (name == "Exceptions") {
        attributeInfo.info.exceptions_info = LeClasse().getExceptionsAttribute(fp);

    } else if (name == "SourceFile") {
        attributeInfo.info.sourceFile_info = LeClasse().getSourceFileAttribute(fp);

    }  else if (name == "Deprecated") {
        attributeInfo.info.deprecated_info = LeClasse().getDeprecatedAttribute(fp);

    } else if (name == "InnerClasses") {
        attributeInfo.info.innerClasses_info = LeClasse().getInnerClassesAttribute(fp);

    } else if (name == "Synthetic") {
        attributeInfo.info.synthetic_info = LeClasse().getSyntheticAttribute(fp);

    }  else if (name == "ConstantValue") {
        attributeInfo.info.constantValue_info = LeClasse().getConstantValueAttribute(fp);

    } else {
        cout << "Arquivo .class possui uma um atributo nao implementado." << endl;
        
    }
    return attributeInfo;
}


Code_attribute LeClasse::getCodeAttribute(FILE *fp, vector<cp_info> cp){
    Code_attribute toReturn;
    toReturn.max_stack = readU2(fp);
    toReturn.max_locals = readU2(fp);
    
    toReturn.code_length = readU4(fp);
    int contador = toReturn.code_length;
    toReturn.code = (u1*) malloc(contador * sizeof(u1));
    for (int i = 0; i < contador; i++) {
        toReturn.code[i] = readU1(fp);
    }
    
    toReturn.exception_table_length = readU2(fp);
    contador = toReturn.exception_table_length;
    toReturn.exception_table = (ExceptionTable*) malloc(contador * sizeof(ExceptionTable));
    for (int i = 0; i < contador; i++) {
        toReturn.exception_table[i] = getExceptionTable(fp);
    }
    
    toReturn.attributes_count = readU2(fp);
    contador = toReturn.attributes_count;
    toReturn.attributes = (attribute_info*) malloc(contador * sizeof(attribute_info));
    for (int i = 0; i < contador; i++) {
        toReturn.attributes[i] = getAttributeInfo(fp,cp);
    }
    
    return toReturn;
}

LineNumberTable LeClasse::getLineNumberTable(FILE *fp) {
    LineNumberTable toReturn;
    toReturn.start_pc = readU2(fp);
    toReturn.line_number = readU2(fp);
    return toReturn;
}

LineNumberTable_attribute LeClasse::getLineNumberTableAttribute(FILE * fp){
    LineNumberTable_attribute toReturn;
    toReturn.line_number_table_length = readU2(fp);
    int contador = toReturn.line_number_table_length;
    toReturn.line_number_table = (LineNumberTable*) malloc(contador * sizeof(LineNumberTable));
    for (int i = 0; i < contador; i++) {
        toReturn.line_number_table[i] = getLineNumberTable(fp);
    }
    return toReturn;
}

LocalVariableTable LeClasse::getLocalVariableTable(FILE *fp) {
    LocalVariableTable toReturn;
    toReturn.start_pc = readU2(fp);
    toReturn.length = readU2(fp);
    toReturn.name_index = readU2(fp);
    toReturn.descriptor_index = readU2(fp);
    toReturn.index = readU2(fp);
    return toReturn;
}

LocalVariableTable_attribute LeClasse::getLocalVariableAttribute(FILE *fp) {
    LocalVariableTable_attribute toReturn;
    toReturn.local_variable_table_length = readU2(fp);
    int contador = toReturn.local_variable_table_length;
    toReturn.local_variable_table = (LocalVariableTable*) malloc(contador * sizeof(LocalVariableTable));
    for (int i = 0; i < contador; i++) {
        toReturn.local_variable_table[i] = getLocalVariableTable(fp);
    }
    return toReturn;
}

Exceptions_attribute LeClasse::getExceptionsAttribute(FILE *fp) {
    Exceptions_attribute toReturn;
    toReturn.number_of_exceptions = readU2(fp);
    int contador = toReturn.number_of_exceptions;
    toReturn.exception_index_table = (u2*) malloc(contador * sizeof(u2));
    for (int i = 0; i < contador; i++) {
        toReturn.exception_index_table[i] = readU2(fp);
    }
    return toReturn;
}

SourceFile_attribute LeClasse::getSourceFileAttribute(FILE *fp) {
    SourceFile_attribute toReturn;
    toReturn.sourcefile_index = readU2(fp);
    return toReturn;
}

Deprecated_attribute LeClasse::getDeprecatedAttribute(FILE *fp) {
    Deprecated_attribute toReturn;
    return toReturn;
}

Class LeClasse::getClass(FILE *fp) {
    Class toReturn;
    toReturn.inner_class_info_index = readU2(fp);
    toReturn.outer_class_info_index = readU2(fp);
    toReturn.inner_name_index = readU2(fp);
    toReturn.inner_class_access_flags = readU2(fp);
    return toReturn;
}

InnerClasses_attribute LeClasse::getInnerClassesAttribute(FILE *fp) {
    InnerClasses_attribute toReturn;
    toReturn.number_of_classes = readU2(fp);
    int contador = toReturn.number_of_classes;
    toReturn.classes = (Class*) malloc(contador * sizeof(Class));
    for (int i = 0; i < contador; i++) {
        toReturn.classes[i] = getClass(fp);
    }
    return toReturn;
}

Synthetic_attribute LeClasse::getSyntheticAttribute(FILE *fp) {
    Synthetic_attribute toReturn;
    return toReturn;
}

ConstantValue_attribute LeClasse::getConstantValueAttribute(FILE *fp) {
    ConstantValue_attribute toReturn;
    toReturn.constantvalue_index = readU2(fp);
    return toReturn;
}