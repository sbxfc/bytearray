//
//  SFByteArray.cpp
//  ByteArrayDemo
//
//  Created by sbx_fc on 15/6/12.
//  Copyright (c) 2015年 SF. All rights reserved.
//

#include "SFByteArray.h"
#include <stdlib.h>

SFByteArray::SFByteArray(int allowSize)
{
    writePos = 0;
    readPos = 0;
    bytesBuf.reserve(allowSize < 0 ? 1 : allowSize);
    bytesBuf.clear();
    Endian endian= getEndian();
    setEndian(endian, endian);
}

void SFByteArray::writeByte(char value)
{
    writeChars(&value, 1);
}

void SFByteArray::writeBOOL(bool value)
{
    writeChars((char *)&value, 1, 0);
}

void SFByteArray::writeChars(const char *val)
{
    writeChars(val, (int)strlen(val), 0);
}

void SFByteArray::writeString(const std::string &value)
{
    writeNumber((int)value.size());
    writeChars(value.c_str(), value.size(), 0);
}

void SFByteArray::writeChars(const char *value, size_t length, int offset)
{
    if(bytesBuf.size() < (writePos + length))
    {
        bytesBuf.resize(writePos + length);
    }
    
    const char *src = value + offset;
    ::memcpy(&bytesBuf[writePos], src, length);
    writePos += length;
}

bool SFByteArray::readBOOL()
{
    bool value = false;
    readBytes((char *)&value, 1, 0);
    return value;
}

char SFByteArray::readByte()
{
    char value;
    readBytes(&value, 1);
    return value;
}


bool SFByteArray::readBytes(char *value, size_t length, int offset)
{
    char *destBytes = value + offset;
    if(readPos + length > bytesBuf.size())
    {
        *destBytes = 0;
        return false;
    }
    ::memcpy(destBytes, &bytesBuf[readPos], length);
    readPos += length;
    return true;
}

void SFByteArray::readChars(char *val, size_t size)
{
    readBytes((char *)val, size, 0);
}

/**
 * 读取一个字符串
 */
std::string SFByteArray::readString()
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
 * 将字节源 bytes 里的字节顺序反转
 * @param bytes 源字节
 * @param size 字节长度
 */
void SFByteArray::reversalArray(char *bytes, size_t size)
{
    for(size_t i = 0; i < size / 2; i++)
    {
        char tb;
        tb = *(bytes + i);
        *(bytes + i) = *(bytes + size - i - 1);
        *(bytes + size - i - 1) = tb;
    }
}

/**
 * return 1 : 小端
 * return 0 : 大端
 */
Endian SFByteArray::getEndian()
{
    union {
        unsigned int a;
        unsigned char b;
    }c;
    c.a = 1;
    
    if(c.b == 1)
    {
        return LITENDIAN;
    }
    
    return BIGENDIAN;
}


/**
 * 释放内存
 */
SFByteArray::~SFByteArray()
{
    std::vector<char>().swap(bytesBuf);
}