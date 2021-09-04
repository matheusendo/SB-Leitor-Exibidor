#ifndef __ARQUIVOCLASSE_H__
#define __ARQUIVOCLASSE_H__

#include <cstdint>
#include <vector>
#include <fstream>
#include "tipos.h"

using namespace std;

#define typeof __typeof__

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
