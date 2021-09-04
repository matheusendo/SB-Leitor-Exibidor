#ifndef TIPOS_H
#define TIPOS_H

#include <iostream>
#include <vector>
// Tipos de representação de dados da classe
typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;

using namespace std;

struct CONSTANT_Class_info {
	u2 name_index;
};

struct CONSTANT_Fieldref_info {
    u2 class_index;
    u2 name_and_type_index;
};

struct CONSTANT_Methodref_info {
    u2 class_index;
    u2 name_and_type_index;
};

struct CONSTANT_InterfaceMethodref_info {
    u2 class_index;
    u2 name_and_type_index;
};

struct CONSTANT_String_info {
    u2 string_index;
};

struct CONSTANT_Integer_info {
    u4 bytes;
};

struct CONSTANT_Float_info {
    u4 bytes;
};

struct CONSTANT_Long_info {
    u4 high_bytes;
    u4 low_bytes;
};

struct CONSTANT_Double_info {
    u4 high_bytes;
    u4 low_bytes;
};

struct CONSTANT_NameAndType_info {
	u2 name_index;
	u2 descriptor_index;
};

struct CONSTANT_Utf8_info {
    u2 length;
    u1 *bytes;
};

struct CONSTANT_MethodHandle_info{
    u1 reference_kind;
    u2 reference_index;
};

struct CONSTANT_MethodType_info{
    u2 descriptor_index;
};

struct CONSTANT_InvokeDynamic_info{
    u2 bootstrap_method_attr_index;
    u2 name_and_type_index;
};

struct ConstantValue_attribute {
    u2 constantvalue_index;
};

struct ExceptionTable {
    u2 start_pc;
    u2 end_pc;
    u2 handler_pc;
    u2 catch_type;
};

struct Deprecated_attribute {
    // vazio
};

struct attribute_info;

struct Code_attribute {
	u2 max_stack;
	u2 max_locals;
	u4 code_length;
	u1 *code;
	u2 exception_table_length;
    ExceptionTable *exception_table;
	u2 attributes_count;
	attribute_info *attributes;
};

struct Exceptions_attribute {
	u2 number_of_exceptions;
	u2 *exception_index_table;
};

struct Class {
    u2 inner_class_info_index;	     
    u2 outer_class_info_index;	     
    u2 inner_name_index;	     
    u2 inner_class_access_flags;	
};

struct InnerClasses_attribute {
	u2 number_of_classes;
	Class *classes;
};

struct Synthetic_attribute {
	// vazio
};

struct SourceFile_attribute {
  	u2 sourcefile_index;
};

struct LineNumberTable {
    u2 start_pc;	     
    u2 line_number;
};

struct LineNumberTable_attribute {
	u2 line_number_table_length;
	LineNumberTable *line_number_table;
};

struct LocalVariableTable {
    u2 start_pc;
    u2 length;
    u2 name_index;
    u2 descriptor_index;
    u2 index;
};

struct LocalVariableTable_attribute {
    u2 local_variable_table_length;
    LocalVariableTable *local_variable_table;
};

struct attribute_info {
    u2 attribute_name_index;
    u4 attribute_length;
    union {
        ConstantValue_attribute constantValue_info;
        Code_attribute code_info;
        Exceptions_attribute exceptions_info;
        InnerClasses_attribute innerClasses_info;
        Synthetic_attribute synthetic_info;
        SourceFile_attribute sourceFile_info;
        LineNumberTable_attribute lineNumberTable_info;
        LocalVariableTable_attribute localVariableTable_info;
        Deprecated_attribute deprecated_info;
    } info;
};

struct field_info {
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    attribute_info *attributes;
};

struct method_info {
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    attribute_info *attributes;
};

struct cp_info {
    u1 tag;
    union {
        CONSTANT_Class_info class_info;
        CONSTANT_Fieldref_info fieldref_info;
        CONSTANT_Methodref_info methodref_info;
        CONSTANT_InterfaceMethodref_info interfaceMethodref_info;
        CONSTANT_String_info string_info;
        CONSTANT_Integer_info integer_info;
        CONSTANT_Float_info float_info;
        CONSTANT_Long_info long_info;
        CONSTANT_Double_info double_info;
        CONSTANT_NameAndType_info nameAndType_info;
        CONSTANT_Utf8_info utf8_info;
        CONSTANT_MethodHandle_info methodHandle_info;
        CONSTANT_MethodType_info methodType_info;
        CONSTANT_InvokeDynamic_info invokeDynamic_info;
    } info;
};

#endif