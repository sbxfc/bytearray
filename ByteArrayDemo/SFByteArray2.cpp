//
//  SFByteArray2.cpp
//  ByteArrayDemo
//
//  Created by sbx_fc on 15/6/12.
//  Copyright (c) 2015年 SF. All rights reserved.
//

#include "SFByteArray2.h"

#include <string>
#include <stdlib.h>

SFByteArray2::SFByteArray2(int allowSize)
{
    writePos = 0;
    readPos = 0;
    bytesBuf.reserve(allowSize < 0 ? 1 : allowSize);
    bytesBuf.clear();
}

/**
 * 写入一个字节
 */
void SFByteArray2::writeByte(char value)
{
    writeChars(&value, 1);
}

/**
 * 写入一个布尔值
 */
void SFByteArray2::writeBOOL(bool value)
{
    writeChars((char *)&value, 1, 0);
}

/**
 * 写入一个短整型数值
 */
void SFByteArray2::writeShort(short value)
{
    if(bytesBuf.size() < (writePos + 2))
    {
        bytesBuf.resize(writePos + 2);
    }
    
    bytesBuf[writePos++] = (value >> 8) & 0xff;
    bytesBuf[writePos++] = value & 0xff;
}

/**
 * 写入整型数值
 */
void SFByteArray2::writeInt(int value)
{
    if(bytesBuf.size() < (writePos + 4))
    {
        bytesBuf.resize(writePos + 4);
    }
    
    bytesBuf[writePos++] = (value >> 24) & 0xff;
    bytesBuf[writePos++] = (value >> 16) & 0xff;
    bytesBuf[writePos++] = (value >> 8) & 0xff;
    bytesBuf[writePos++] = value & 0xff;
}

/**
 * 写入长整型数值
 */
void SFByteArray2::writeLong(long value)
{
    if(bytesBuf.size() < (writePos + 8))
    {
        bytesBuf.resize(writePos + 8);
    }
    
    bytesBuf[writePos++] = (value >> 56) & 0xff;
    bytesBuf[writePos++] = (value >> 48) & 0xff;
    bytesBuf[writePos++] = (value >> 40) & 0xff;
    bytesBuf[writePos++] = (value >> 32) & 0xff;
    bytesBuf[writePos++] = (value >> 24) & 0xff;
    bytesBuf[writePos++] = (value >> 16) & 0xff;
    bytesBuf[writePos++] = (value >> 8) & 0xff;
    bytesBuf[writePos++] = value & 0xff;
}

/**
 * 写入多个字节
 */
void SFByteArray2::writeChars(const char *val)
{
    writeChars(val, (int)strlen(val), 0);
}

/**
 * 写入一个字符串
 */
void SFByteArray2::writeString(const std::string &value)
{
    writeInt((int)value.size());
    writeChars(value.c_str(), value.size(), 0);
}

/**
 * 写入多个字节
 */
void SFByteArray2::writeChars(const char *value, size_t length, int offset)
{
    if(bytesBuf.size() < (writePos + length))
    {
        bytesBuf.resize(writePos + length);
    }
    
    const char *src = value + offset;
    ::memcpy(&bytesBuf[writePos], src, length);
    writePos += length;
}

/**
 * 读取一个字节
 */
char SFByteArray2::readByte()
{
    char value;
    readBytes(&value, 1);
    return value;
}

/**
 * 读取一个布尔值
 */
bool SFByteArray2::readBOOL()
{
    bool value = false;
    readBytes((char *)&value, 1, 0);
    return value;
}

/**
 * 读取一个短整形
 */
short SFByteArray2::readShort()
{
    char bytes[2];
    readBytes(bytes, 2);
    
    short value = 0;
    value  = (bytes[0] & 0xff) << 8;
    value |= (bytes[1] & 0xff);
    
    return value;
}

/**
 * 读取一个整形
 */
int SFByteArray2::readInt()
{
    char bytes[4];
    readBytes(bytes, 4);
    
    int value = 0;
    value  = ((bytes[0] & 0xff) << 24);
    value |= ((bytes[1] & 0xff) << 16);
    value |= ((bytes[2] & 0xff) << 8);
    value |=  (bytes[3] & 0xff);
    
    return value;
}

/**
 * 读取一个长整形
 */
long SFByteArray2::readLong()
{
    char bytes[8];
    readBytes(bytes, 8);
    
    long value = 0;
    value = ((long)bytes[0] & 0xff)<< 56;
    value|= ((long)bytes[1] & 0xff)<< 48;
    value|= ((long)bytes[2] & 0xff)<< 40;
    value|= ((long)bytes[3] & 0xff)<< 32;
    value|= (bytes[4] & 0xff) << 24;
    value|= (bytes[5] & 0xff) << 16;
    value|= (bytes[6] & 0xff) << 8;
    value|= (bytes[7] & 0xff);
    return value;
}

/**
 * 读取多个字节
 */
bool SFByteArray2::readBytes(char *value, size_t length, int offset)
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

/**
 * 读取多个字节
 */
void SFByteArray2::readChars(char *val, size_t size)
{
    readBytes((char *)val, size, 0);
}

/**
 * 读取一个字符串
 */
std::string SFByteArray2::readString()
{
    int length = readInt();
    char *chars = (char *)malloc(length + 1);
    memset(chars, 0, length + 1);
    readBytes((char *)chars, length, 0);
    std::string str(chars);
    free(chars);
    return str;
}

/**
 * 释放内存
 */
SFByteArray2::~SFByteArray2()
{
    std::vector<char>().swap(bytesBuf);
}
