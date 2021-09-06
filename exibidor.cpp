#include "exibidor.hpp"
#include <cmath>

Exibidor::Exibidor(ArquivoClasse arq_classe, FILE *fp){
    this->printGeneralInfo(arq_classe, fp);
    this->printConstantPool(arq_classe, fp);
    this->printInterfaces(arq_classe, fp);
    this->printFields(arq_classe, fp);
    this->printMethods(arq_classe, fp);
    this->printAttributes(arq_classe, fp);
}

string Exibidor::getAccessFlags(u2 accessFlags){
    string toReturn;
    if (accessFlags & 0x0001) {
        toReturn += " public ";
    }
    if (accessFlags & 0x0002) {
        toReturn += " private ";
    }
    if (accessFlags & 0x0004) {
        toReturn += " protected ";
    }
    if (accessFlags & 0x0008) {
        toReturn += " static ";
    }
    if (accessFlags & 0x0010) {
        toReturn += " final ";
    }
    if (accessFlags & 0x0040) {
        toReturn += " bridge ";
    }
    if (accessFlags & 0x0080) {
        toReturn += " varargs ";
    }
    if (accessFlags & 0x0100) {
        toReturn += " native ";
    }
    if (accessFlags & 0x0400) {
        toReturn += " abstract ";
    }
    if (accessFlags & 0x0800) {
        toReturn += " strict ";
    }
    if (accessFlags & 0x1000) {
        toReturn += " synthetic ";
    }
    
    return toReturn;
}

string Exibidor::getMajorVersionAjustado(u2 majorVersion){
    switch (majorVersion) {
        case 46:
            return "1.2";
        case 47:
            return "1.3";
        case 48:
            return "1.4";
        case 49:
            return "1.5";
        case 50:
            return "1.6";
        case 51:
            return "1.7";
        case 52:
            return "1.8";
        case 53:
            return "1.9";
        case 54:
            return "1.10";
        case 55:
            return "1.11";
        case 56:
            return "1.12";
        case 57:
            return "1.13";
        case 58:
            return "1.14";
        default:
            return "";
    }
}

string Exibidor::getStringConstantPool(cp_info cpInfo, vector<cp_info> constantPool) {
    if (cpInfo.tag == 1){
        string toReturn;
        int contador = cpInfo.info.utf8_info.length;
        for (int i = 0 ; i < contador; i++){
            toReturn.push_back(cpInfo.info.utf8_info.bytes[i]);
        }
        
        return toReturn;
    } 
    else if (cpInfo.tag == 3) {
        return to_string(cpInfo.info.float_info.bytes);
    } 
    else if (cpInfo.tag == 4) {
        return to_string(cpInfo.info.float_info.bytes);
    } 
    else if (cpInfo.tag == 5) {
        long long temp = (long long)cpInfo.info.long_info.high_bytes << 32;
        temp += cpInfo.info.long_info.low_bytes;
        return to_string(temp);
    } 
    else if (cpInfo.tag == 6) {
        int64_t temp = ((int64_t) cpInfo.info.double_info.high_bytes << 32);
        temp += cpInfo.info.double_info.low_bytes;
        int32_t x = ((temp >> 63) == 0) ? 1 : -1;
        int32_t y = (int32_t)((temp >> 52) & 0x7ffL);
        int64_t z = (y == 0) ? (temp & 0xfffffffffffffL) << 1 : (temp & 0xfffffffffffffL) | 0x10000000000000L;
        double num = x * z * pow(2, y-1075);
        
        return to_string(num);
    } 
    else if (cpInfo.tag == 7) {
        cpInfo = constantPool[cpInfo.info.class_info.name_index-1];
        return this->getStringConstantPool(cpInfo, constantPool);
    } 
    else if (cpInfo.tag == 8) {
        cpInfo = constantPool[cpInfo.info.string_info.string_index-1];
        return this->getStringConstantPool(cpInfo, constantPool);
    } 
    else if (cpInfo.tag == 12) {
        cp_info cp1 = constantPool[cpInfo.info.nameAndType_info.name_index-1];
        cp_info cp2 = constantPool[cpInfo.info.nameAndType_info.descriptor_index-1];
        return this->getStringConstantPool(cp1, constantPool) + ": " + this->getStringConstantPool(cp2,constantPool);
    }
    else{
        cout<<"Tag inválida , tag ="<<cpInfo.tag<<endl;
        exit(1);
    }
    

    return 0;
}

void Exibidor::printGeneralInfo(ArquivoClasse arq_classe, FILE *fp) {
    vector<cp_info> cp = arq_classe.getConstantPool();
    
    fprintf(fp, "\n===================== General Information =====================\n");

    fprintf(fp,"\t Magic Number: \t0x%.8X\n", arq_classe.getMagicNumber());
    fprintf(fp,"\t Minor Version: \t%hu\n", arq_classe.getMinorVersion());
    fprintf(fp,"\t Major Version: \t%hu [%s]\n", arq_classe.getMajorVersion(),this->getMajorVersionAjustado(arq_classe.getMajorVersion()).c_str());
    fprintf(fp,"\t Constant Pool Count: \t %hu\n", arq_classe.getConstantPoolSize());
    fprintf(fp,"\t Access Flags: \t0x%.4X [%s]\n", arq_classe.getAccessFlags(),getAccessFlags(arq_classe.getAccessFlags()).c_str());

    int index = arq_classe.getThisClass();
    string str = this->getStringConstantPool(cp[index-1], cp);
     
    fprintf(fp,"\t This Class: \tcp_info #%hu <%s>\n", index, str.c_str());
    index = arq_classe.getSuperClass();
    str = this->getStringConstantPool(cp[index-1], cp);
    fprintf(fp,"\t Super Class: \tcp_info #%hu <%s>\n", index, str.c_str());

    fprintf(fp,"\t Interfaces Count: \t%hu\n", arq_classe.getInterfacesCount());
    fprintf(fp,"\t Fields Count: \t%hu\n", arq_classe.getFieldsCount());
    fprintf(fp,"\t Methods Count: \t%hu\n", arq_classe.getMethodsCount());
    fprintf(fp,"\t Attributes Count: \t%hu\n", arq_classe.getAttributesCount());
    
}

void Exibidor::printConstantPool(ArquivoClasse arq_classe, FILE *fp){
    vector<cp_info> cp;
    cp = arq_classe.getConstantPool();
    fprintf(fp, "\n\n\n\n===================== Constant Pool =====================\n\n");
    
    for(int i = 0; i < cp.size(); i++){
        cp_info cpInfo = cp[i];
        string str;
        
        if (cpInfo.tag == 0) {
            fprintf(fp,"\t [%d] (large numeric continued)\n", i+1);
        }
        else if(cpInfo.tag == 1){
            str = getStringConstantPool(cpInfo, cp);
            fprintf(fp,"\t [%d] CONSTANT_Utf8_info\n", i+1);
            fprintf(fp,"\t\t | Length of Byte Array: %hu\n", cpInfo.info.utf8_info.length);
            fprintf(fp,"\t\t | Length of String: %hu\n", cpInfo.info.utf8_info.length);
            fprintf(fp,"\t\t | String: %s\n", str.c_str());
        }
        else if(cpInfo.tag == 3){
            fprintf(fp,"\t [%d] CONSTANT_Integer_info\n", i+1);
            fprintf(fp,"\t\t | Bytes: 0x%.8X\n", cpInfo.info.integer_info.bytes);
            int d = *(int*)(&cpInfo.info.float_info.bytes);
            fprintf(fp,"\t\t | Integer: %d\n", d);
        }
        else if(cpInfo.tag == 4){
            fprintf(fp,"\t [%d] CONSTANT_Float_info\n", i+1);
            fprintf(fp,"\t\t | Bytes: 0x%.8X\n", cpInfo.info.float_info.bytes);
            float f = *(float*)(&cpInfo.info.float_info.bytes);
            fprintf(fp,"\t\t | Float: %.1f\n", f);
        }
        else if(cpInfo.tag == 5){
            str = getStringConstantPool(cpInfo, cp);
            fprintf(fp,"\t [%d] CONSTANT_Long_info\n", i+1);
            fprintf(fp,"\t\t | High Bytes: 0x%.8X\n", cpInfo.info.long_info.high_bytes);
            fprintf(fp,"\t\t | Low Bytes: 0x%.8X\n", cpInfo.info.long_info.low_bytes);
            fprintf(fp,"\t\t | Long: %ld\n", stol(str));
        }
        else if(cpInfo.tag == 6){
            str = getStringConstantPool(cpInfo, cp);
            fprintf(fp,"\t [%d] CONSTANT_Double_info\n", i+1);
            fprintf(fp,"\t\t | High Bytes: 0x%.8X\n", cpInfo.info.double_info.high_bytes);
            fprintf(fp,"\t\t | Low Bytes: 0x%.8X\n", cpInfo.info.double_info.low_bytes);
            fprintf(fp,"\t\t | Double: %lf\n", stod(str));
        }
        else if(cpInfo.tag == 7){
            str = getStringConstantPool(cpInfo, cp);
            fprintf(fp,"\t [%d] CONSTANT_Class_info\n", i+1);
            fprintf(fp,"\t\t |Class Name: \tcp_info #%hu <%s>\n", cpInfo.info.class_info.name_index, str.c_str());
        }
        else if(cpInfo.tag == 8){
            str = getStringConstantPool(cpInfo, cp);
            fprintf(fp,"\t [%d] CONSTANT_String_info\n", i+1);
            fprintf(fp,"\t\t |String: \tcp_info #%hu <%s>\n", cpInfo.info.string_info.string_index, str.c_str());
        }
        else if(cpInfo.tag == 9){     
            fprintf(fp,"\t [%d] CONSTANT_Fieldref_info\n", i+1);
            cp_info cp1 = cp[cpInfo.info.fieldref_info.class_index-1];
            str = getStringConstantPool(cp1, cp);
            fprintf(fp,"\t\t |Class Name: \tcp_info #%hu <%s>\n", cpInfo.info.fieldref_info.class_index, str.c_str());
            cp1 = cp[cpInfo.info.fieldref_info.name_and_type_index-1];
            str = getStringConstantPool(cp1, cp);
            fprintf(fp,"\t\t |Name and Type: \t cp_info #%hu <%s>\n", cpInfo.info.fieldref_info.name_and_type_index, str.c_str());
        }
        else if(cpInfo.tag == 10){     
            fprintf(fp,"\t [%d] CONSTANT_Methodref_info\n", i+1);
            cp_info cp1 = cp[cpInfo.info.methodref_info.class_index-1];
            str = getStringConstantPool(cp1, cp);
            fprintf(fp,"\t\t |Class Name: \tcp_info #%hu <%s>\n", cpInfo.info.methodref_info.class_index, str.c_str());
            cp1 = cp[cpInfo.info.methodref_info.name_and_type_index-1];
            str = getStringConstantPool(cp1, cp);
            fprintf(fp,"\t\t |Name and Type: \t cp_info #%hu <%s>\n", cpInfo.info.methodref_info.name_and_type_index, str.c_str());
        }
        else if(cpInfo.tag == 11){     
            fprintf(fp,"\t [%d] CONSTANT_InterfaceMethodref_info\n", i+1);
            cp_info cp1 = cp[cpInfo.info.interfaceMethodref_info.class_index-1];
            str = getStringConstantPool(cp1, cp);
            fprintf(fp,"\t\t |Class Name: \tcp_info #%hu <%s>\n", cpInfo.info.interfaceMethodref_info.class_index, str.c_str());
            cp1 = cp[cpInfo.info.interfaceMethodref_info.name_and_type_index-1];
            str = getStringConstantPool(cp1, cp);
            fprintf(fp,"\t\t |Name and Type: \t cp_info #%hu <%s>\n", cpInfo.info.interfaceMethodref_info.name_and_type_index, str.c_str());
        }
        else if(cpInfo.tag == 12){     
            fprintf(fp,"\t [%d] CONSTANT_NameAndType_info\n", i+1);
            cp_info cp1 = cp[cpInfo.info.nameAndType_info.name_index-1];
            str = getStringConstantPool(cp1, cp);
            fprintf(fp,"\t\t |Name: \tcp_info #%hu <%s>\n", cpInfo.info.nameAndType_info.name_index, str.c_str());
            cp1 = cp[cpInfo.info.nameAndType_info.descriptor_index-1];
            str = getStringConstantPool(cp1, cp);
            fprintf(fp,"\t\t |Descriptor: \t cp_info #%hu <%s>\n", cpInfo.info.nameAndType_info.descriptor_index, str.c_str());
        }
        else if(cpInfo.tag == 15){     
            fprintf(fp,"\t [%d] CONSTANT_MethodHandle_info\n", i+1);
            fprintf(fp,"\t\t |Reference Kind :\t %hhu\n", cpInfo.info.methodHandle_info.reference_kind);
            fprintf(fp,"\t\t |Reference Index :\t %hu\n", cpInfo.info.methodHandle_info.reference_index);
        }
        else if(cpInfo.tag == 16){     
            fprintf(fp,"\t [%d] CONSTANT_MethodType_info\n", i+1);
            fprintf(fp,"\t\t |Descriptor Index :\t %hu\n", cpInfo.info.methodType_info.descriptor_index);
        }
        else if(cpInfo.tag == 18){     
            fprintf(fp,"\t [%d] CONSTANT_InvokeDynamic_info\n", i+1);
            fprintf(fp,"\t\t |Bootstrap Method Atr :\t %hu\n", cpInfo.info.invokeDynamic_info.bootstrap_method_attr_index);
            fprintf(fp,"\t\t |Name and Type :\t %hu\n", cpInfo.info.invokeDynamic_info.name_and_type_index);
        }
        
        
        
    }
}

void Exibidor::printInterfaces(ArquivoClasse arq_classe, FILE *fp){
    vector<cp_info> cp;
    vector<u2> interfaces_1;
    cp_info cpInfo;
    cp = arq_classe.getConstantPool();
    interfaces_1 = arq_classe.getInterfaces();
    fprintf(fp, "\n\n\n\n===================== Interfaces =====================\n\n");
    int contador = arq_classe.getInterfacesCount();

    for(int i = 0 ; i < contador; i++){
        fprintf(fp,"\t Interface %d \n", i);
        cpInfo = cp[interfaces_1[i]-1];
        fprintf(fp,"\t\t |Interface : \t cp_info #%hu <%s>\n", interfaces_1[i],getStringConstantPool(cpInfo,cp).c_str());
    }
}

void Exibidor::printFields(ArquivoClasse arq_classe, FILE *fp){
    vector<cp_info> cp;
    vector<field_info> fields_1;
    cp_info cpInfo;
    cp = arq_classe.getConstantPool();
    fields_1 = arq_classe.getFields();
    fprintf(fp, "\n\n\n\n===================== Fields =====================\n\n");
    int contador = arq_classe.getFieldsCount();

    for(int i = 0 ; i < contador; i++){
        int index = fields_1[i].name_index;
        cpInfo = cp[index-1];
        fprintf(fp,"\t[%d] %s\n", i,getStringConstantPool(cpInfo,cp).c_str());
        fprintf(fp,"\t\t |Name : \t cp_info #%d <%s>\n", index,getStringConstantPool(cpInfo,cp).c_str());

        index = fields_1[i].descriptor_index;
        cpInfo = cp[index-1];
        fprintf(fp,"\t\t |Descriptor : \t cp_info #%d <%s>\n", index,getStringConstantPool(cpInfo,cp).c_str());

    }
}

void Exibidor::printMethods(ArquivoClasse arq_classe, FILE *fp){
    vector<cp_info> cp;
    vector<method_info> methods_1;
    cp_info cpInfo;
    cp = arq_classe.getConstantPool();
    methods_1 = arq_classe.getMethods();
    fprintf(fp, "\n\n\n\n===================== Methods =====================\n\n");
    int contador = arq_classe.getMethodsCount();

    for(int i = 0 ; i < contador; i++){
        int index = methods_1[i].name_index;
        cpInfo = cp[index-1];
        fprintf(fp,"\t[%d] %s\n", i,getStringConstantPool(cpInfo,cp).c_str());
        fprintf(fp,"\t\t |Name : \t cp_info #%d <%s>\n", index,getStringConstantPool(cpInfo,cp).c_str());

        index = methods_1[i].descriptor_index;
        cpInfo = cp[index-1];
        fprintf(fp,"\t\t |Descriptor : \t cp_info #%d <%s>\n", index,getStringConstantPool(cpInfo,cp).c_str());
        
        fprintf(fp,"\t\t |Access Flags : \t 0x%.4X [%s]\n",methods_1[i].access_flags, getAccessFlags(methods_1[i].access_flags).c_str());

        fprintf(fp,"\t\t |Attributes :\n");
        int contador = methods_1[i].attributes_count;
        for(int j = 0; j < contador; j++){
            printAttribute(methods_1[i].attributes[j], j, cp,fp);
        }
        
    }
}

void Exibidor::printAttribute(attribute_info attributeInfo, int index, vector<cp_info> cp, FILE *fp) { 
    cp_info cpInfo;   
    string attributeName;

    cpInfo = cp[attributeInfo.attribute_name_index-1];
    attributeName = getStringConstantPool(cpInfo,cp);
    
    fprintf(fp,"\t\t\t |[%d] %s\n", index, attributeName.c_str());
    
    fprintf(fp,"\t\t\t\t |Attribute name index:\t cp_info #%d <%s>\n", attributeInfo.attribute_name_index,attributeName.c_str());
    
    fprintf(fp,"\t\t\t\t |Attribute length:\t %d\n", attributeInfo.attribute_length);
        
}

void Exibidor::printAttributes(ArquivoClasse arq_classe, FILE *fp) { 
    vector<cp_info> cp;  
    vector<attribute_info> attributes_1;

    cp = arq_classe.getConstantPool();
    attributes_1 = arq_classe.getAttributes();

    fprintf(fp, "\n\n\n\n===================== Attributes =====================\n\n");
    int contador = arq_classe.getAttributesCount();
    for(int i = 0; i < contador; i++){
        printAttribute(attributes_1[i],i,cp,fp);
    }
    
        
}

