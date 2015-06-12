//
//  main.cpp
//  ByteArrayDemo
//
//  Created by sbx_fc on 15/6/12.
//  Copyright (c) 2015年 SF. All rights reserved.
//

#include <iostream>
#include "SFByteArray.h"
#include "SFByteArray2.h"

int main(int argc, const char * argv[]) {
    
     /**
     * 使用反转函数实现的字节流转换
     */
    SFByteArray bytes;
    bytes.writeString(std::string("sbx"));
    bytes.writeChars("fc");
    bytes.writeNumber(17);
    bytes.writeBOOL(true);
    bytes.writeNumber((float)3.141592654f);
    bytes.writeNumber((double)3.141592654f);
    
    std::string strVal = bytes.readString();
    std::cout << strVal << "\n";
    
    char charsVal[100] = { 0 };
    bytes.readChars(charsVal,2);
    std::cout << charsVal << "\n";
    
    int intVal = 0;
    bytes.readNumber(&intVal);
    std::cout << intVal << "\n";
    
    bool bVal = false;
    bVal = bytes.readBOOL();
    std::cout << bVal << "\n";
    
    float f = 0.0;
    bytes.readNumber(&f);
    std::cout << f << "\n";
    
    double d = bytes.read<double>();
    std::cout << d << "\n";
    
    /**
     * 使用移位运算符实现的字节流转换
     */
    SFByteArray2 byteArray;
    byteArray.writeByte(4);
    
    std::cout <<"可读取的字节长度:"<< byteArray.readableBytes() << "\n";
    
    byteArray.writeShort(32767);
    byteArray.writeLong(-2147483647);
    byteArray.writeString("sbxfc");
    
    std::cout <<"字节长度:"<< byteArray.size() << "\n";
    
    char byteValue = byteArray.readByte();
    std::cout << byteValue << "\n";

    short shortValue = byteArray.readShort();
    std::cout << shortValue << "\n";
    
    std::cout <<"可读取的字节长度:"<< byteArray.readableBytes() << "\n";
    
    long longValue = byteArray.readLong();
    std::cout << longValue << "\n";
    
    std::string strValue = byteArray.readString();
    std::cout << strValue << "\n";
    
    return 0;
}
