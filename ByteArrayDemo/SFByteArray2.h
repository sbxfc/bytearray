//
//  SFByteArray2.h
//  ByteArrayDemo
//
//  Created by sbx_fc on 15/6/12.
//  Copyright (c) 2015年 SF. All rights reserved.
//

#ifndef __ByteArrayDemo__SFByteArray2__
#define __ByteArrayDemo__SFByteArray2__

#include <stdio.h>

#include <stdio.h>
#include <vector>

typedef unsigned char  BYTE;

class SFByteArray2
{
    
public:
    SFByteArray2(int allocSize = 1);
    ~SFByteArray2();
    
public:
    
    /**
     * 写入一个字节
     */
    void writeByte(char value);
    
    /**
     * 写入一个布尔值
     */
    void writeBOOL(bool value);
    
    /**
     * 写入多个字节
     */
    void writeChars(const char *value);
    
    /**
     * 写入多个字节
     * @param offset 读取字节的偏移量
     */
    void writeChars(const char *value, size_t length, int offset = 0);
    
    /**
     * 写入一个短整型
     */
    void writeShort(short value);
    
    /**
     * 写入一个整型
     */
    void writeInt(int value);
    
    /**
     * 写入一个长整型
     */
    void writeLong(long value);
    
    /**
     * 写入一个长整型
     */
    void writeDouble(double value);
    
    /**
     * 写入一个字符串
     */
    void writeString(const std::string &value);
    
public:
    
    /**
     * 读入一个字节
     */
    char readByte();
    
    /**
     * 读入一个布尔值
     */
    bool readBOOL();
    
    /**
     * 读入一个短整型数值
     */
    short readShort();
    
    /**
     * 读入
     */
    int readInt();
    
    /**
     * 读入
     */
    long readLong();
    
    /**
     * 读入多个字节
     */
    bool readBytes(char *value, size_t size, int offset = 0);
    
    /**
     * 读入一个字符串
     */
    std::string readString();
    
    /**
     * 读入多个字节
     */
    void readChars(char *val, size_t size);
public:
    
    const char* data() const
    {
        return bytesBuf.data();
    }
    
    size_t size()
    {
        return bytesBuf.size();
    }
    
    size_t readableBytes() const
    {
        return writePos - readPos;
    }
    
    size_t writableBytes() const
    {
        return bytesBuf.size() - writePos;
    }
private:
    SFByteArray2(const SFByteArray2&);
    SFByteArray2& operator=(const SFByteArray2&);
private:
    size_t writePos;
    size_t readPos;
    std::vector<char> bytesBuf;
};

#endif /* defined(__ByteArrayDemo__SFByteArray2__) */
