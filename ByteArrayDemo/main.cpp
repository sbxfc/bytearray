//
//  main.cpp
//  ByteArrayDemo
//
//  Created by sbx_fc on 15/6/12.
//  Copyright (c) 2015年 SF. All rights reserved.
//

#include <iostream>
#include "SFByteArray.h"

int main(int argc, const char * argv[]) {
    // insert code here...

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
    
    return 0;
}
