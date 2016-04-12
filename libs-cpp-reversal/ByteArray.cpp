//
//  ByteArray.cpp
//  ByteArrayDemo
//
//  Created by sbxfc on 15/6/12.
//  Copyright (c) 2015年 SF. All rights reserved.
//

#include "ByteArray.h"
#include <stdlib.h>

ByteArray::ByteArray(int allowSize)
{
    //清空容器并制定容量大小
    buffer.reserve(allowSize < 0 ? 1 : allowSize);
    buffer.clear();
    
    //初始化容器的读写位置
    writePosition = 0;
    readPosition = 0;
}

/**
 * 写入一个字节
 */
void ByteArray::writeByte(char value)
{
    writeChars(&value, 1);
}

/**
 * 写入一个布尔值
 */
void ByteArray::writeBOOL(bool value)
{
    writeChars((char *)&value, 1, 0);
}

/**
 * 写入多个字节
 */
void ByteArray::writeChars(const char *val)
{
    writeChars(val, (int)strlen(val), 0);
}

/**
 * 写入一个字符串
 */
void ByteArray::writeString(const std::string &value)
{
    writeNumber((int)value.size());
    writeChars(value.c_str(), value.size(), 0);
}

/**
 * 写入多个字节
 */
void ByteArray::writeChars(const char *value, size_t length, int offset)
{
    if(buffer.size() < (writePosition + length)){
        buffer.resize(writePosition + length);
    }
    
    const char *src = value + offset;
    memcpy(&buffer[writePosition], src, length);
    writePosition += length;
}

bool ByteArray::readBOOL()
{
    bool value = false;
    readBytes((char *)&value, 1, 0);
    return value;
}

char ByteArray::readByte()
{
    char value;
    readBytes(&value, 1);
    return value;
}


bool ByteArray::readBytes(char *value, size_t length, int offset)
{
    char *destBytes = value + offset;
    if(readPosition + length > buffer.size()){
        *destBytes = 0;
        return false;
    }
    memcpy(destBytes, &buffer[readPosition], length);
    readPosition += length;
    return true;
}

void ByteArray::readChars(char *val, size_t size)
{
    readBytes((char *)val, size, 0);
}

/**
 * 读取一个字符串
 */
std::string ByteArray::readString()
{
    int length;
    readNumber(&length);
    char *chars = (char *)malloc(length + 1);
    memset(chars, 0, length + 1);
    readBytes((char *)chars, length, 0);
    std::string str(chars);
    free(chars);
    return str;
}

 /**
 * 将bytes里的字节颠倒
 */
void ByteArray::reversalArray(char *bytes, size_t size)
{
    for(size_t i = 0; i < size / 2; i++){
        char temp;
        temp = *(bytes + i);
        *(bytes + i) = *(bytes + size - i - 1);
        *(bytes + size - i - 1) = temp;
    }
}

/**
 * 获取当前设置的大、小端类型
 * @return 1 //小端
 * @return 0 //大端
 */
Endian ByteArray::getDeviceEndian()
{
    union {
        unsigned int a;
        unsigned char b;
    }c;
    c.a = 1;
    
    if(c.b == 1){
        return LITENDIAN;
    }
    
    return BIGENDIAN;
}


/**
 * 释放内存
 */
ByteArray::~ByteArray()
{
    std::vector<char>().swap(buffer);
}