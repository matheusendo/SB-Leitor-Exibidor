#ifndef __ARQUIVOCLASSE_H__
#define __ARQUIVOCLASSE_H__

#include <cstdint>
#include <vector>
#include <fstream>
#include "tipos.hpp"

using namespace std;

#define typeof __typeof__

/** 
 * Definição de um arquivo .class. Formato:
 * 
 *
 * ClassFile { \n
 * <pre>
 *      u4 magic;   // Assinatura do arquivo .class deve ser igual a 0xCAFEBABE.
 *      u2 minor_version;   // Indica a versão mínima suportada.
 *      u2 major_version;   // Indica versão mais recente suportada
 *      u2 constant_pool_count;   // Número de entradas na tabela ConstantPool + 1.
 *      cp_info constant_pool[constant_pool_count-1];   // Tabela de estruturas representando strings, nomes de classes ou de interfaces, nomes de campos, e outras constantes.
 *      u2 access_flags;   // Máscara de flags que especifica permissão de acesso e propriedades da classe ou interface.
 *      u2 this_class;   // Index de entrada na ConstantPool da própria classe ou interface do arquivo .class.
 *      u2 super_class;   // Zero ou index de entrada na ConstantPool da super classe direta da classe do arquivo .class, se for 0 a classe estende Object
 *      u2 interfaces_count;   // Número de superinterfaces diretas da classe ou interface do arquivo .class.
 *      u2 interfaces[interfaces_count];   // Array de índices válidos na ConstantPool da super interface direta da classe ou interface do arquivo .class
 *      u2 fields_count;   // Número de estruturas de field_info na tabela fields.
 *      field_info fields[fields_count];   // Tabela contendo os campos declaradas pela classe ou interface do arquivo .class.
 *      u2 methods_count;   // Número de estruturas de methods_info na tabela de methods.
 *      method_info methods[methods_count];  // Tabela contendos os métodos declarados pela classe ou interface do arquivo .class.
 *      u2 attributes_count;   // Número de atributos na tabela de atributos da classe ou interface do arquivo .class.
 *      attribute_info attributes[attributes_count]; // Tabela de estruturas do tipo attribute_info.
 * </pre>
 * }
 *
 */

class ArquivoClasse {
    private:
    u4 magicNumber;
    u2 minorVersion;
    u2 majorVersion;
    u2 constantPoolSize;
    vector<cp_info> constantPool;
    u2 accessFlags;
    u2 thisClass;
    u2 superClass;
    u2 interfacesCount;
    vector<u2> interfaces;
    u2 fieldsCount;
    vector<field_info> fields;
    u2 methodsCount;
    vector<method_info> methods;
    u2 attributesCount;
    vector<attribute_info> attributes;

    void setMagicNumber(FILE * fp);
    void setMajorVersion(FILE * fp);
    void setMinorVersion(FILE * fp);
    void setConstantPoolSize(FILE * fp);
    void setConstantPool(FILE * fp);
    void setAccessFlags(FILE * fp);
    void setThisClass(FILE * fp);
    void setSuperClass(FILE * fp);
    void setInterfacesCount(FILE * fp);
    void setInterfaces(FILE * fp);
    void setFieldsCount(FILE * fp);
    void setFields(FILE * fp);
    void setMethodsCount(FILE * fp);
    void setMethods(FILE * fp);
    void setAttributesCount(FILE * fp);
    void setAttributes(FILE * fp);
    
    public:
    ArquivoClasse(FILE * fp);
    ArquivoClasse();
    u4 getMagicNumber();
    u2 getMajorVersion();
    u2 getMinorVersion();
    u2 getConstantPoolSize();
    vector<cp_info> getConstantPool();
    u2 getAccessFlags();
    u2 getThisClass();
    u2 getSuperClass();
    u2 getInterfacesCount();
    vector<u2> getInterfaces();
    u2 getFieldsCount();
    vector<field_info> getFields();
    u2 getMethodsCount();
    vector<method_info> getMethods();
    u2 getAttributesCount();
    vector<attribute_info> getAttributes();
};

#endif
