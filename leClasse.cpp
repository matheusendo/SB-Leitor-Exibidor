#include <cstdlib>
#include "tipos.hpp"
#include "leClasse.hpp"

using namespace std;

LeClasse::LeClasse(){}

/**
Lê 1 byte do arquivo .class.
@param *fp ponteiro para o arquivo .class sendo lido.
@return byte lido.
*/

u1 LeClasse::readU1(FILE *fp) {
    u1 toReturn = 0;
    fread(&toReturn, sizeof(u1), 1, fp);
    return toReturn;
}

/**
Lê 2 bytes do arquivo .class, considera a máquina littleendian.
@param *fp ponteiro para o arquivo .class sendo lido.
@return 2 bytes lidos.
*/

u2 LeClasse::readU2(FILE *fp) {
    u2 toReturn = 0;
    for (int i = 0; i < 2; i++) {
        toReturn += readU1(fp) << (8 - 8*i);
    }
    return toReturn;
}

/**
Lê 4 bytes do arquivo .class, considera a máquina littleendian.
@param *fp ponteiro para o arquivo .class sendo lido.
@return 4 bytes lidos.
*/

u4 LeClasse::readU4(FILE *fp) {
    u4 toReturn = 0;
    for (int i = 0; i < 4; i++) {
        toReturn += readU1(fp) << (24 - 8*i);
    } 
    return toReturn;
}

/**
Lê o arquivo .class com o método readU2 para pegar e setar o lenght, utiliza esse valor para saber o número de bytes. 
Utiliza o malloc para alocar memória com o tamanho adequado, para cada byte utiliza o método readU1 para ler.
@param *fp ponteiro para o arquivo .class sendo lido.
@return struct CONSTANT_Utf8_info.
*/

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

/**
Lê o arquivo .class com o método readU4 para pegar e setar o campo bytes da struct tipo CONSTANT_Integer_info. 
@param *fp ponteiro para o arquivo .class sendo lido.
@return struct CONSTANT_Integer_info.
*/

CONSTANT_Integer_info LeClasse::getIntegerInfo(FILE *fp) {
    CONSTANT_Integer_info toReturn;
    toReturn.bytes = readU4(fp);
    return toReturn;
}

/**
Lê o arquivo .class com o método readU4 para pegar e setar o campo bytes da struct tipo CONSTANT_Float_info. 
@param *fp ponteiro para o arquivo .class sendo lido.
@return struct CONSTANT_Float_info.
*/

CONSTANT_Float_info LeClasse::getFloatInfo(FILE *fp) {
    CONSTANT_Float_info toReturn;
    toReturn.bytes = readU4(fp);
    return toReturn;
}

/**
Lê o arquivo .class com o método readU4 para pegar e setar os campos high_bytes e low_bytes da struct tipo CONSTANT_Long_info. 
@param *fp ponteiro para o arquivo .class sendo lido.
@return struct CONSTANT_Long_info.
*/

CONSTANT_Long_info LeClasse::getLongInfo(FILE *fp) {
    CONSTANT_Long_info toReturn;
    toReturn.high_bytes = readU4(fp);
    toReturn.low_bytes = readU4(fp);
    return toReturn;
}

/**
Lê o arquivo .class com o método readU4 para pegar e setar os campos high_bytes e low_bytes da struct tipo CONSTANT_Double_info.  
@param *fp ponteiro para o arquivo .class sendo lido.
@return struct CONSTANT_Double_info.
*/

CONSTANT_Double_info LeClasse::getDoubleInfo(FILE *fp) {
    CONSTANT_Double_info toReturn;
    toReturn.high_bytes = readU4(fp);
    toReturn.low_bytes = readU4(fp);
    return toReturn;
}

/**
Lê o arquivo .class com o método readU2 para pegar e setar o campo name_index da struct tipo CONSTANT_Class_info. 
@param *fp ponteiro para o arquivo .class sendo lido.
@return struct CONSTANT_Class_info.
*/

CONSTANT_Class_info LeClasse::getClassInfo(FILE *fp) {
    CONSTANT_Class_info toReturn;
    toReturn.name_index = readU2(fp);
    return toReturn;
}

/**
Lê o arquivo .class com o método readU2 para pegar e setar o campo string_index da struct tipo CONSTANT_String_info. 
@param *fp ponteiro para o arquivo .class sendo lido.
@return struct CONSTANT_String_info.
*/

CONSTANT_String_info LeClasse::getStringInfo(FILE *fp) {
    CONSTANT_String_info toReturn;
    toReturn.string_index = readU2(fp);
    return toReturn;
}

/**
Lê o arquivo .class com o método readU2 para pegar e setar os campos class_index e 
name_and_type_index da struct tipo CONSTANT_Fieldref_info. 
@param *fp ponteiro para o arquivo .class sendo lido.
@return struct CONSTANT_Fieldref_info.
*/

CONSTANT_Fieldref_info LeClasse::getFieldRefInfo(FILE *fp) {
    CONSTANT_Fieldref_info toReturn;
    toReturn.class_index = readU2(fp);
    toReturn.name_and_type_index = readU2(fp);
    return toReturn;
}

/**
Lê o arquivo .class com o método readU2 para pegar e setar os campos class_index e 
name_and_type_index da struct tipo CONSTANT_Methodref_info. 
@param *fp ponteiro para o arquivo .class sendo lido.
@return struct CONSTANT_Methodref_info.
*/

CONSTANT_Methodref_info LeClasse::getMethodRefInfo(FILE *fp) {
    CONSTANT_Methodref_info toReturn;
    toReturn.class_index = readU2(fp);
    toReturn.name_and_type_index = readU2(fp);
    return toReturn;
}

/**
Lê o arquivo .class com o método readU2 para pegar e setar os campos class_index e 
name_and_type_index da struct tipo CONSTANT_InterfaceMethodref_info. 
@param *fp ponteiro para o arquivo .class sendo lido.
@return struct CONSTANT_InterfaceMethodref_info.
*/

CONSTANT_InterfaceMethodref_info LeClasse::getInterfaceMethodRefInfo(FILE *fp) {
    CONSTANT_InterfaceMethodref_info toReturn;
    toReturn.class_index = readU2(fp);
    toReturn.name_and_type_index = readU2(fp);
    return toReturn;
}

/**
Lê o arquivo .class com o método readU2 para pegar e setar os campos name_index e 
descriptor_index da struct tipo CONSTANT_NameAndType_info. 
@param *fp ponteiro para o arquivo .class sendo lido.
@return struct CONSTANT_NameAndType_info.
*/

CONSTANT_NameAndType_info LeClasse::getNameAndTypeInfo(FILE *fp) {
    CONSTANT_NameAndType_info toReturn;
    toReturn.name_index = readU2(fp);
    toReturn.descriptor_index = readU2(fp);
    return toReturn;
}

/**
Lê o arquivo .class com o método readU1 para pegar e setar o campo reference_kind e readU2 para
reference_index da struct tipo CONSTANT_MethodHandle_info. 
@param *fp ponteiro para o arquivo .class sendo lido.
@return struct CONSTANT_MethodHandle_info.
*/

CONSTANT_MethodHandle_info LeClasse::getMethodHandleInfo(FILE *fp){
    CONSTANT_MethodHandle_info toReturn;
    toReturn.reference_kind = readU1(fp);
    toReturn.reference_index = readU2(fp);
    return toReturn;
}

/**
Lê o arquivo .class com o método readU2 para pegar e setar o campo descriptor_index da struct tipo CONSTANT_MethodType_info. 
@param *fp ponteiro para o arquivo .class sendo lido.
@return struct CONSTANT_MethodType_info.
*/

CONSTANT_MethodType_info LeClasse::getMethodTypeInfo(FILE *fp){
    CONSTANT_MethodType_info toReturn;
    toReturn.descriptor_index = readU2(fp);
    return toReturn;
}

/**
Lê o arquivo .class com o método readU2 para pegar e setar os campos bootstrap_method_attr_index e 
name_and_type_index da struct tipo CONSTANT_InvokeDynamic_info. 
@param *fp ponteiro para o arquivo .class sendo lido.
@return struct CONSTANT_InvokeDynamic_info.
*/

CONSTANT_InvokeDynamic_info LeClasse::getInvokeDynamic_info(FILE *fp){
    CONSTANT_InvokeDynamic_info toReturn;
    toReturn.bootstrap_method_attr_index = readU2(fp);
    toReturn.name_and_type_index = readU2(fp);
    return toReturn;
}

/**
Pega o lenght de cpInfo, e utiliza esse valor para saber o número de bytes. 
Para cada byte faz um push.back na string com o byte lido.
@param struct cpInfo do tipo cp_info.
@return string formada a partir dos bytes de cpInfo.
*/

string LeClasse::getUtf8(cp_info cpInfo){
    string toReturn;
    int contador = cpInfo.info.utf8_info.length;
    for (int i = 0 ; i < contador; i++){
        toReturn.push_back(cpInfo.info.utf8_info.bytes[i]);
    }
    return toReturn;
}

/**
Lê o arquivo .class com o método readU2 para pegar e setar os campos start_pc, end_pc, handler_pc e 
catch_type da struct tipo ExceptionTable. 
@param *fp ponteiro para o arquivo .class sendo lido.
@return struct ExceptionTable.
*/

ExceptionTable LeClasse::getExceptionTable(FILE *fp) {
    ExceptionTable toReturn;
    toReturn.start_pc = readU2(fp);
    toReturn.end_pc = readU2(fp);
    toReturn.handler_pc = readU2(fp);
    toReturn.catch_type = readU2(fp);
    return toReturn;
}

/**
Lê o arquivo .class com o método readU2 para pegar e setar o campo attribute_name_index, e readU4 para 
attribute_length, utiliza o método getUtf8 para pegar a string name correspondente à entrada no constantPool
com o index name_index - 1. Se a string for Code, utiliza o método getCodeAttribute para receber e setar as informações do tipo
Code_Attribute, para os demais casos utiliza o get adequado para setar o campo.
@param *fp ponteiro para o arquivo .class sendo lido.
@param constantPool um vetor de cp_info.
@return struct attribute_info.
*/

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

/**
Lê o arquivo .class com o método readU2 para pegar e setar os campos max_stack e max_locals, e readU4 para 
code_length. Utiliza o valor de code_length para saber o número de bytes, aloca memória de acordo com esse número
através do malloc e para cada byte utiliza readU1 para ler o byte do arquivo e seta ao campo code de Code_attribute. 
Lê o arquivo com readU2 para pegar os valores de exception_table_length e attributes_count, utiliza essses valores
o número de exception_table e de attributes, aloca memória adequada e utiliza método getExceptionTable e getAttributeInfo para
pegar e setor esses campos.
@param *fp ponteiro para o arquivo .class sendo lido.
@param constantPool um vetor de cp_info.
@return struct Code_attribute.
*/

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

/**
Lê o arquivo .class com o método readU2 para pegar e setar os campos start_pc e 
line_number da struct tipo LineNumberTable. 
@param *fp ponteiro para o arquivo .class sendo lido.
@return struct LineNumberTable.
*/

LineNumberTable LeClasse::getLineNumberTable(FILE *fp) {
    LineNumberTable toReturn;
    toReturn.start_pc = readU2(fp);
    toReturn.line_number = readU2(fp);
    return toReturn;
}

/**
Lê o arquivo .class com o método readU2 para pegar e setar line_number_table_length, utiliza esse valor para saber o número de line_number_table. 
Utiliza o malloc para alocar memória com o tamanho adequado, para cada line_number_table utiliza o método getLineNumberTable 
que retorna um LineNumberTable e o seta no campo line_number_table.
@param *fp ponteiro para o arquivo .class sendo lido.
@return struct LineNumberTable_attribute.
*/

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

/**
Lê o arquivo .class com o método readU2 para pegar e setar os campos start_pc, length, name_index e 
descriptor_index e index da struct tipo LocalVariableTable. 
@param *fp ponteiro para o arquivo .class sendo lido.
@return struct LocalVariableTable.
*/

LocalVariableTable LeClasse::getLocalVariableTable(FILE *fp) {
    LocalVariableTable toReturn;
    toReturn.start_pc = readU2(fp);
    toReturn.length = readU2(fp);
    toReturn.name_index = readU2(fp);
    toReturn.descriptor_index = readU2(fp);
    toReturn.index = readU2(fp);
    return toReturn;
}

/**
Lê o arquivo .class com o método readU2 para pegar e setar local_variable_table_length, utiliza esse valor para saber o número de line_number_table. 
Utiliza o malloc para alocar memória com o tamanho adequado, para cada local_variable_table utiliza o método getLocalVariableTable 
que retorna um LocalVariableTable e o seta no campo local_variable_table.
@param *fp ponteiro para o arquivo .class sendo lido.
@return struct LocalVariableTable_attribute.
*/

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

/**
Lê o arquivo .class com o método readU2 para pegar e setar number_of_exceptions, utiliza esse valor para saber o número de entradas na tabela. 
Utiliza o malloc para alocar memória com o tamanho adequado, para cada entrada na tabela utiliza o método readU2 para ler o arquivo e seta o campo.
@param *fp ponteiro para o arquivo .class sendo lido.
@return struct Exceptions_attribute.
*/

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

/**
Lê o arquivo .class com o método readU2 para pegar e setar o campo sourceFile_index da struct tipo SourceFile_attribute. 
@param *fp ponteiro para o arquivo .class sendo lido.
@return struct SourceFile_attribute.
*/

SourceFile_attribute LeClasse::getSourceFileAttribute(FILE *fp) {
    SourceFile_attribute toReturn;
    toReturn.sourcefile_index = readU2(fp);
    return toReturn;
}

/**
Cria uma struct do tipo Deprecated_attribute(vazia) e retorna ela, não foi implementado. 
@param *fp ponteiro para o arquivo .class sendo lido.
@return struct Deprecated_attribute.
*/

Deprecated_attribute LeClasse::getDeprecatedAttribute(FILE *fp) {
    Deprecated_attribute toReturn;
    return toReturn;
}

/**
Lê o arquivo .class com o método readU2 para pegar e setar os campos inner_class_info_index, outer_class_info_index, 
inner_name_index e inner_class_access_flags da struct tipo Class. 
@param *fp ponteiro para o arquivo .class sendo lido.
@return struct Class.
*/

Class LeClasse::getClass(FILE *fp) {
    Class toReturn;
    toReturn.inner_class_info_index = readU2(fp);
    toReturn.outer_class_info_index = readU2(fp);
    toReturn.inner_name_index = readU2(fp);
    toReturn.inner_class_access_flags = readU2(fp);
    return toReturn;
}

/**
Lê o arquivo .class com o método readU2 para pegar e setar nnumber_of_classes, utiliza esse valor para saber o número de class's(struct class). 
Utiliza o malloc para alocar memória com o tamanho adequado, para cada class na tabela utiliza o método getClass para pegar a class e seta o campo.
@param *fp ponteiro para o arquivo .class sendo lido.
@return struct InnerClasses_attribute.
*/

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

/**
Cria uma struct do tipo Synthetic_attribute(vazia) e retorna ela, não foi implementado. 
@param *fp ponteiro para o arquivo .class sendo lido.
@return struct Synthetic_attribute.
*/

Synthetic_attribute LeClasse::getSyntheticAttribute(FILE *fp) {
    Synthetic_attribute toReturn;
    return toReturn;
}

/**
Lê o arquivo .class com o método readU2 para pegar e setar o campo constantvalue_index da struct tipo ConstantValue_attribute. 
@param *fp ponteiro para o arquivo .class sendo lido.
@return struct ConstantValue_attribute.
*/

ConstantValue_attribute LeClasse::getConstantValueAttribute(FILE *fp) {
    ConstantValue_attribute toReturn;
    toReturn.constantvalue_index = readU2(fp);
    return toReturn;
}