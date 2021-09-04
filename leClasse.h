#ifndef LECLASSE_H
#define LECLASSE_H
#include <stdio.h> 

#include "tipos.h"

class LeClasse {

public:
    LeClasse();
    u1 readU1(FILE *file);
    u2 readU2(FILE *file);
    u4 readU4(FILE *file);
    CONSTANT_Utf8_info getUtf8Info(FILE *file);
    CONSTANT_Integer_info getIntegerInfo(FILE *file);
    CONSTANT_Float_info getFloatInfo(FILE *file);
    CONSTANT_Long_info getLongInfo(FILE *file);
    CONSTANT_Double_info getDoubleInfo(FILE *file);
    CONSTANT_Class_info getClassInfo(FILE *file);
    CONSTANT_String_info getStringInfo(FILE *file);
    CONSTANT_Fieldref_info getFieldRefInfo(FILE *file);
    CONSTANT_Methodref_info getMethodRefInfo(FILE *file);
    CONSTANT_InterfaceMethodref_info getInterfaceMethodRefInfo(FILE *file);
    CONSTANT_NameAndType_info getNameAndTypeInfo(FILE *file);
    CONSTANT_MethodHandle_info getMethodHandleInfo(FILE *file);
    CONSTANT_MethodType_info getMethodTypeInfo(FILE *file);
    CONSTANT_InvokeDynamic_info getInvokeDynamic_info(FILE *file);
    string getUtf8(cp_info);
    ExceptionTable getExceptionTable(FILE *file);
    attribute_info getAttributeInfo(FILE *file, vector<cp_info>);
    Code_attribute getCodeAttribute(FILE *file, vector<cp_info>);
    LineNumberTable getLineNumberTable(FILE *fp);
    LineNumberTable_attribute getLineNumberTableAttribute(FILE * file);
    LocalVariableTable getLocalVariableTable(FILE *fp);
    LocalVariableTable_attribute getLocalVariableAttribute(FILE *file);
    Exceptions_attribute getExceptionsAttribute(FILE *file);
    SourceFile_attribute getSourceFileAttribute(FILE *file);
    Deprecated_attribute getDeprecatedAttribute(FILE *file);
    Class getClass(FILE *fp);
    InnerClasses_attribute getInnerClassesAttribute(FILE *file);
    Synthetic_attribute getSyntheticAttribute(FILE *file);
    ConstantValue_attribute getConstantValueAttribute(FILE *file);


 

};

#endif
