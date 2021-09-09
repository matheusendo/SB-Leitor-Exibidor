#include "exibidor.hpp"
#include <cmath>
#include<sstream>  

Exibidor::Exibidor(ArquivoClasse arq_classe, FILE *fp){
    this->setInstructions();
    this->printGeneralInfo(arq_classe, fp);
    this->printConstantPool(arq_classe, fp);
    this->printInterfaces(arq_classe, fp);
    this->printFields(arq_classe, fp);
    this->printMethods(arq_classe, fp);
    this->printAttributes(arq_classe, fp);
    
}

void Exibidor::setInstructions(){
    instructions = { "nop", "aconst_null", "iconst_m1", "iconst_0", "iconst_1", "iconst_2", 
    "iconst_3", "iconst_4", "iconst_5", "lconst_0", "lconst_1", "fconst_0", "fconst_1", 
    "fconst_2", "dconst_0", "dconst_1", "bipush", "sipush", "ldc", "ldc_w", "ldc2_w", 
    "iload", "lload", "fload", "dload", "aload", "iload_0", "iload_1", "iload_2", "iload_3", 
    "lload_0", "lload_1", "lload_2", "lload_3", "fload_0", "fload_1", "fload_2", "fload_3", 
    "dload_0", "dload_1", "dload_2", "dload_3", "aload_0", "aload_1", "aload_2", "aload_3", 
    "iaload", "laload", "faload", "daload", "aaload", "baload", "caload", "saload", "istore", 
    "lstore", "fstore", "dstore", "astore", "istore_0", "istore_1", "istore_2", "istore_3", 
    "lstore_0", "lstore_1", "lstore_2", "lstore_3", "fstore_0", "fstore_1", "fstore_2", 
    "fstore_3", "dstore_0", "dstore_1", "dstore_2", "dstore_3", "astore_0", "astore_1", 
    "astore_2", "astore_3", "iastore", "lastore", "fastore", "dastore", "aastore", "bastore", 
    "castore", "sastore", "pop", "pop2", "dup", "dup_x1", "dup_x2", "dup2", "dup2_x1", 
    "dup2_x2", "swap", "iadd", "ladd", "fadd", "dadd", "isub", "lsub", "fsub", "dsub", 
    "imul", "lmul", "fmul", "dmul", "idiv", "ldiv", "fdiv", "ddiv", "irem", "lrem", "frem", 
    "drem", "ineg", "lneg", "fneg", "dneg", "ishl", "lshl", "ishr", "lshr", "iushr", "lushr", 
    "iand", "land", "ior", "lor", "ixor", "lxor", "iinc", "i2l", "i2f", "i2d", "l2i", "l2f", 
    "l2d", "f2i", "f2l", "f2d", "d2i", "d2l", "d2f", "i2b", "i2c", "i2s", "lcmp", "fcmpl", 
    "fcmpg", "dcmpl", "dcmpg", "ifeq", "ifne", "iflt", "ifge", "ifgt", "ifle", "if_icmpeq", 
    "if_icmpne", "if_icmplt", "if_icmpge", "if_icmpgt", "if_icmple", "if_acmpeq", "if_acmpne", 
    "goto", "jsr", "ret", "tableswitch", "lookupswitch", "ireturn", "lreturn", "freturn", 
    "dreturn", "areturn", "return", "getstatic", "putstatic", "getfield", "putfield", 
    "invokevirtual", "invokespecial", "invokestatic", "invokeinterface", "UNUSED", "new", 
    "newarray", "anewarray", "arraylength", "athrow", "checkcast", "instanceof", "monitorenter", 
    "monitorexit", "wide", "multianewarray", "ifnull", "ifnonnull", "goto_w", "jsr_w" };
}

string Exibidor::getInstruction(u1 index){
    return instructions[index];
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
        stringstream ss; 
        int num = (int) cpInfo.info.integer_info.bytes; 
        ss<<num;
        string s;
        ss >> s;
        return s;
    } 
    else if (cpInfo.tag == 4) {
        stringstream ss; 
        float f = *(float*)(&cpInfo.info.float_info.bytes);
        ss<<f;
        string s;
        ss >> s;
        return s;
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
    else if(cpInfo.tag == 10){
        cp_info cp1 = constantPool[cpInfo.info.methodref_info.class_index-1];
        return this->getStringConstantPool(cp1, constantPool);
    }
    else if (cpInfo.tag == 12) {
        cp_info cp1 = constantPool[cpInfo.info.nameAndType_info.name_index-1];
        cp_info cp2 = constantPool[cpInfo.info.nameAndType_info.descriptor_index-1];
        return this->getStringConstantPool(cp1, constantPool) + ": " + this->getStringConstantPool(cp2,constantPool);
    }
    else{
        cout<<"Tag inválida"<<endl;
        exit(1);
    }
    

    return 0;
}

void Exibidor::printGeneralInfo(ArquivoClasse arq_classe, FILE *fp) {
    vector<cp_info> cp = arq_classe.getConstantPool();
    
    fprintf(fp, "\n===================== General Information =====================\n");

    fprintf(fp,"\t Magic Number: \t0x%.8X\n", arq_classe.getMagicNumber());
    fprintf(fp,"\t Minor Version: \t%hu\n", arq_classe.getMinorVersion());
    fprintf(fp,"\t Major Version: \t%hu [1.%d]\n", arq_classe.getMajorVersion(),arq_classe.getMajorVersion()-44);
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
            str = getStringConstantPool(cpInfo, cp);
            fprintf(fp,"\t\t |Class Name: \tcp_info #%hu <%s>\n", cpInfo.info.methodref_info.class_index, str.c_str());
            cp_info cp1 = cp[cpInfo.info.methodref_info.name_and_type_index-1];
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
            string attributeName = getStringConstantPool(cp[methods_1[i].attributes[j].attribute_name_index-1],cp);
            
            printAttribute(attributeName, j, methods_1[i].attributes[j], fp, arq_classe);
        }
        
    }
}

void Exibidor::printAttribute(string attributeName, int index, attribute_info attributeInfo, FILE *fp, ArquivoClasse arq_classe) { 
    vector<cp_info> cp;
    cp_info cpInfo;
    Code_attribute codeAttribute;
    int contador;
    string instruction;
    string str;
    vector<string> tipos = {"boolean", "char", "float", "double", "byte", "short", "int", "long"};

    cp = arq_classe.getConstantPool();
    codeAttribute = attributeInfo.info.code_info;
    

    fprintf(fp,"\n\t\t\t |[%d] %s\n", index, attributeName.c_str());
    fprintf(fp,"\t\t\t |Generic Info:\n");
    fprintf(fp,"\t\t\t\t |Attribute name index:\t cp_info #%d <%s>\n", attributeInfo.attribute_name_index,attributeName.c_str());
    fprintf(fp,"\t\t\t\t |Attribute length:\t %d\n", attributeInfo.attribute_length);
    fprintf(fp,"\t\t\t |Specific Info:\n");
    if(attributeName == "Code"){//Caso o atributo seja code, printa os bytecodes
        index++;
        contador = attributeInfo.info.code_info.code_length;//pega o tamanho de code
        fprintf(fp,"\t\t\t\t |Byte Code:\n");
        

        for(int i = 0; i < contador ; i++){//itera sobre code até acabar
            
            u1 opcode = codeAttribute.code[i];
            instruction = this->getInstruction(opcode);
            fprintf(fp,"\t\t\t\t\t");
            if(opcode <= 0x0f || (opcode >= 0x1a && opcode <= 0x35) || (opcode >= 0x3b && opcode <= 0x83) || (opcode >= 0x85 && opcode <= 0x98) || (opcode >= 0xac && opcode <= 0xb1) || opcode == 0xbe || opcode == 0xbf || opcode == 0xc2 || opcode == 0xc3){
                fprintf(fp,"%d\t%d %s \n",index ++, i, instruction.c_str());
            }
            else if(opcode == 0x10 || (opcode >= 0x15 && opcode <= 0x19) || (opcode >= 0x36 && opcode <= 0x3a) || opcode == 0xa9){
                fprintf(fp,"%d\t%d %s %d\n", index++, i, instruction.c_str(),codeAttribute.code[i+1]);
                i ++;
            }
            else if(opcode == 0x13 || opcode == 0x14 || (opcode >= 0xb2 && opcode <= 0xb8) || opcode == 0xbb || opcode == 0xbd || opcode == 0xc0 || opcode == 0xc1){
                u1 num = codeAttribute.code[i+1];
                u1 num2 = codeAttribute.code[i+2];
                int16_t result = (num << 8) | num2;

                cpInfo = cp[result-1];
                if(cpInfo.tag == 9){
                    cp_info cp1 = cp[cpInfo.info.fieldref_info.class_index-1];
                    str = getStringConstantPool(cp1, cp);
                    fprintf(fp,"%d\t%d %s #%d <%s", index++, i, instruction.c_str(), result, str.c_str());
                    cp1 = cp[cpInfo.info.fieldref_info.name_and_type_index-1];
                    str = getStringConstantPool(cp1, cp);
                    fprintf(fp,".%s>\n",str.c_str());
                }
                else if(cpInfo.tag == 10){
                    cp_info cp1 = cp[cpInfo.info.methodref_info.name_and_type_index-1];
                    str = getStringConstantPool(cp1,cp);
                    fprintf(fp,"%d\t%d %s #%d <%s", index++, i, instruction.c_str(), result, str.c_str());
                    cp1 = cp[cpInfo.info.methodref_info.name_and_type_index-1];
                    str = getStringConstantPool(cp1,cp);
                    fprintf(fp,".%s>\n",str.c_str());
                }
                else{
                    fprintf(fp,"%d\t%d %s #%d <%s>\n", index++, i, instruction.c_str(), result, getStringConstantPool(cpInfo, cp).c_str());
                }
                
                i += 2;
            }
            else if(opcode == 0xc8 || opcode == 0xc9){
                u1 num = codeAttribute.code[i+1];
                u1 num2 = codeAttribute.code[i+2];
                u1 num3 = codeAttribute.code[i+3];
                u1 num4 = codeAttribute.code[i+4];
                int32_t result = (num << 24) | (num2 << 16) | (num3 << 8) | num4;
                fprintf(fp,"%d\t%d %s %d (%+d)\n",index++, i, instruction.c_str(), i+result, result);
                i += 4;
            }
            else if (opcode == 0xb9) {
                u1 num = codeAttribute.code[i+1];
                u1 num2 = codeAttribute.code[i+2];
                int16_t result = (num << 8) | num2;
                cpInfo = cp[result-1];
                str = getStringConstantPool(cpInfo,cp);
                fprintf(fp,"%d\t%d %s #%d <%s> count %d\n",index++, i, instruction.c_str(), result, str.c_str(), codeAttribute.code[i+3]);
                i += 4;
            } 
            else if (opcode == 0xc5) {
                u1 num = codeAttribute.code[i+1];
                u1 num2 = codeAttribute.code[i+2];
                int16_t result = (num << 8) | num2;
                cpInfo = cp[result-1];
                str = getStringConstantPool(cpInfo,cp);
                fprintf(fp,"%d\t%d %s #%d <%s> dim %d\n",index++, i, instruction.c_str(), result, str.c_str(), codeAttribute.code[i+3]);
                i += 3;
            }
            else if ((opcode >= 0x99 && opcode <= 0xa8) || opcode == 0xc6 || opcode == 0xc7) {
                u1 num = codeAttribute.code[i+1];
                u1 num2 = codeAttribute.code[i+2];
                int16_t result = (num << 8) | num2;
                fprintf(fp,"%d\t%d %s %d (%+d)\n",index++, i, instruction.c_str(), i+result, result);
                i += 2;
            }
            else if (opcode == 0xbc) { 
                u1 num = codeAttribute.code[i+1];
                fprintf(fp,"%d\t%d %s %d (%s)\n",index++, i, instruction.c_str(), num, tipos[num-4].c_str());
                i += 1;
            }
            else if (opcode == 0x12) { 
                u1 num = codeAttribute.code[i+1];
                cpInfo = cp[num-1];
                
                if(cpInfo.tag == 3){
                    str = getStringConstantPool(cpInfo,cp);
                    fprintf(fp,"%d\t%d %s #%d <%d>\n", index++, i, instruction.c_str(), num, stoi(str.c_str()));
                }
                else if(cpInfo.tag == 4){
                    str = getStringConstantPool(cpInfo,cp);
                    fprintf(fp,"%d\t%d %s #%d <%f>\n", index++, i, instruction.c_str(), num, stof(str.c_str()));
                }
                else if(cpInfo.tag == 7 || cpInfo.tag == 8){
                    str = getStringConstantPool(cpInfo,cp);
                    fprintf(fp,"%d\t%d %s #%d <%s>\n", index++, i, instruction.c_str(), num, str.c_str());
                }
                else {
                    cout<<"Parâmetro da instrucao ldc não implementado."<<endl;
                    exit(1);
                }

                
                i += 1;
            }
            else if (opcode == 0x11) { 
                u1 num = codeAttribute.code[i+1];
                u1 num2 = codeAttribute.code[i+2];
                int16_t result = (num << 8) | num2;
                fprintf(fp,"%d\t%d %s %d\n", index++, i, instruction.c_str(), result);
                i += 2;
            }
            else if (opcode == 0x84) { 
                u1 num = codeAttribute.code[i+1];
                u1 num2 = codeAttribute.code[i+2];
                fprintf(fp,"%d\t%d %s %d by %d\n", index++, i, instruction.c_str(), num, num2);
                i += 2;
            }
            else if (opcode == 0xaa){//https://stackoverflow.com/questions/35222839/java-bytecode-lookupswitch-and-tableswitch-total-instruction-length
                int padding = (i+1) % 4;
                u1 num = codeAttribute.code[padding+ i+1];
                u1 num2 = codeAttribute.code[padding+i+2];
                u1 num3 = codeAttribute.code[padding+i+3];
                u1 num4 = codeAttribute.code[padding+i+4];
                int32_t defa = (num << 24) | (num2 << 16) | (num3 << 8) | num4;
                num = codeAttribute.code[padding+i+5];
                num2 = codeAttribute.code[padding+i+6];
                num3 = codeAttribute.code[padding+i+7];
                num4 = codeAttribute.code[padding+i+8];
                int32_t low = (num << 24) | (num2 << 16) | (num3 << 8) | num4;
                num = codeAttribute.code[padding+i+9];
                num2 = codeAttribute.code[padding+i+10];
                num3 = codeAttribute.code[padding+i+11];
                num4 = codeAttribute.code[padding+i+12];
                int32_t high = (num << 24) | (num2 << 16) | (num3 << 8) | num4;

                fprintf(fp,"%d\t%d %s %d to %d\n" ,index++, i, instruction.c_str(), low, high);

                int32_t jumpOffset = high - low + 1;
                int32_t numBytes = 1 + padding + 12; 
                for (int j = low; j <= high; j++) {
                    fprintf(fp,"\t\t\t\t\t");
                    num = codeAttribute.code[numBytes+i];
                    num2 = codeAttribute.code[numBytes+i+1];
                    num3 = codeAttribute.code[numBytes+i+2];
                    num4 = codeAttribute.code[numBytes+i+3];
                    jumpOffset = (num << 24) | (num2 << 16) | (num3 << 8) | num4;
                    fprintf(fp,"\t%d:\t %d (%+d)\n", j, jumpOffset + i , jumpOffset);
                    numBytes += 4;
                    low++;
                }
                fprintf(fp,"\t\t\t\t\t\tDefault:\t %d (%+d)\n", defa + i, defa);
                i += numBytes - 1;
                
            }
            else if (opcode == 0xab){//https://stackoverflow.com/questions/35222839/java-bytecode-lookupswitch-and-tableswitch-total-instruction-length
                int padding = (i+1) % 4;
                u1 num = codeAttribute.code[padding+ i+1];
                u1 num2 = codeAttribute.code[padding+i+2];
                u1 num3 = codeAttribute.code[padding+i+3];
                u1 num4 = codeAttribute.code[padding+i+4];
                int32_t defa = (num << 24) | (num2 << 16) | (num3 << 8) | num4;
                num = codeAttribute.code[padding+i+5];
                num2 = codeAttribute.code[padding+i+6];
                num3 = codeAttribute.code[padding+i+7];
                num4 = codeAttribute.code[padding+i+8];
                int32_t n = (num << 24) | (num2 << 16) | (num3 << 8) | num4;

                fprintf(fp,"%d\t%d %s %d\n" ,index++, i, instruction.c_str(), n);
                int32_t jumpOffset;
                int32_t match;
                int32_t numBytes = 1 + padding + 8; //12 no tabelswitch pq tem high e low
                for (int j = 0; j <= n; j++) {
                    fprintf(fp,"\t\t\t\t\t");
                    num = codeAttribute.code[numBytes+i];
                    num2 = codeAttribute.code[numBytes+i+1];
                    num3 = codeAttribute.code[numBytes+i+2];
                    num4 = codeAttribute.code[numBytes+i+3];
                    match = (num << 24) | (num2 << 16) | (num3 << 8) | num4;
                    num = codeAttribute.code[numBytes+i+4];
                    num2 = codeAttribute.code[numBytes+i+5];
                    num3 = codeAttribute.code[numBytes+i+6];
                    num4 = codeAttribute.code[numBytes+i+7];
                    jumpOffset = (num << 24) | (num2 << 16) | (num3 << 8) | num4;
                    fprintf(fp,"\t%d:\t %d (%+d)\n", match, jumpOffset + i , jumpOffset);
                    numBytes += 8;
                }
                fprintf(fp,"\t\t\t\t\t\tDefault:\t %d (%+d)\n", defa + i, defa);
                i += numBytes - 1;
                
            }
            else{
                fprintf(fp,"\n");
            }
        }
        fprintf(fp,"\t\t\t\t |Exception Table\n");
        contador = codeAttribute.exception_table_length;
        for(int i = 0; i < contador ; i++){
            fprintf(fp,"\t\t\t\t\t |%d \t", i);
            fprintf(fp,"%d \t", codeAttribute.exception_table[i].start_pc);
            fprintf(fp,"%d \t", codeAttribute.exception_table[i].end_pc);
            fprintf(fp,"%d \t", codeAttribute.exception_table[i].handler_pc);
            fprintf(fp,"%d \t", codeAttribute.exception_table[i].catch_type);
        }
        fprintf(fp,"\t\t\t\t |Misc\n");
        fprintf(fp,"\t\t\t\t\t |Maximum Stack Size: %d\n",codeAttribute.max_stack);
        fprintf(fp,"\t\t\t\t\t |Maximum Local Variables: %d\n",codeAttribute.max_locals);
        fprintf(fp,"\t\t\t\t\t |Code Length: %d\n",codeAttribute.code_length);
        contador = codeAttribute.attributes_count;
        for(int i = 0; i < contador; i++) {
            cp_info cp1 = cp[codeAttribute.attributes[i].attribute_name_index-1];
            attributeName = getStringConstantPool(cp1,cp);
            fprintf(fp,"\t\t\t|Attributes: \n");
            printAttribute(attributeName,i,codeAttribute.attributes[i],fp,arq_classe);
        }

    }
    else if (attributeName == "LineNumberTable"){
        contador = attributeInfo.info.lineNumberTable_info.line_number_table_length;

        
        for(int i = 0; i < contador; i++) {
            fprintf(fp,"\t\t\t\t |Nr: %d\t",i);
            fprintf(fp,"|Start PC: %d\t",attributeInfo.info.lineNumberTable_info.line_number_table[i].start_pc);
            fprintf(fp,"|Line Number: %d\n",attributeInfo.info.lineNumberTable_info.line_number_table[i].line_number);
        }
    }
    else if (attributeName == "SourceFile") {
        cpInfo = cp[attributeInfo.info.sourceFile_info.sourcefile_index-1];
        fprintf(fp,"\t\t\t\t |Source File Name Index: cp_info#%d <%s>\t",attributeInfo.info.sourceFile_info.sourcefile_index,getStringConstantPool(cpInfo,cp).c_str());
        
    }
    else{
        cout<<"Informacoes do atributo nao implementadadas para exibicao"<<endl;
    }
        
}

void Exibidor::printAttributes(ArquivoClasse arq_classe, FILE *fp) { 
    vector<cp_info> cp;  
    vector<attribute_info> attributes_1;
    cp_info cpInfo;
    attribute_info attributeInfo;
    string attributeName;
    cp = arq_classe.getConstantPool();
    attributes_1 = arq_classe.getAttributes();

    fprintf(fp, "\n\n\n\n===================== Attributes =====================\n\n");
    int contador = arq_classe.getAttributesCount();
    for(int i = 0; i < contador; i++){
        attributeInfo = attributes_1[i];
        cpInfo = cp[attributeInfo.attribute_name_index-1];
        attributeName = getStringConstantPool(cpInfo,cp);
        
        printAttribute(attributeName,i,attributes_1[i], fp, arq_classe);
    }
    
        
}

