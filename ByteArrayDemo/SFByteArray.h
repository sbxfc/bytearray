//
//  SFByteArray.h
//  ByteArrayDemo
//
//  Created by sbx_fc on 15/6/12.
//  Copyright (c) 2015年 SF. All rights reserved.
//

#ifndef __ByteArrayDemo__SFByteArray__
#define __ByteArrayDemo__SFByteArray__

#include <stdio.h>
#include <vector>
#include <string>

enum Endian
{
    BIGENDIAN = 0,
    LITENDIAN = 1
};

class SFByteArray
{
    
public:
    SFByteArray(int allocSize = 1);
    ~SFByteArray();
    
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
     */
    void writeChars(const char *value, size_t length, int offset = 0);
    
    /**
     * 写入一个数字
     */
    template <typename Number>
    int writeNumber(Number values)
    {
        char bytes[sizeof(values)];
        
        /*进行网络通信传输时,第三个参数应该设为BIGENDIAN*/
        int size = numberToBytes(values, bytes, writeEndian);
        writeChars(bytes, size);
        return size;
    }
    
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
    
    /**
     * 读取一个数字
     */
    template <typename Number>
    int readNumber(Number *value)
    {
        const int length = sizeof(*value);
        char bytes[length];
        readBytes(bytes, length);
        bytesToNumber(value, bytes, readEndian);
        return length;
    }
    
    template <typename Number>
    Number read()
    {
        Number value;
        const int length = sizeof(value);
        char bytes[length];
        readBytes(bytes, length);
        bytesToNumber(&value, bytes, readEndian);
        return value;
    }
    
private:
    template <typename T>
    int numberToBytes(T values, char *bytes, Endian endian)
    {
        int size = sizeof(values);
        *(T *)bytes = values;
        if(endian == getEndian())
        {
            return size;
        }
        else
        {
            reversalArray(bytes, size);
            return size;
        }
    }
    
    template <typename T>
    int bytesToNumber(T value, char *bytes, Endian endian)
    {
        int length = sizeof(*value);
        if(endian == getEndian())
        {
            
        }else{
            reversalArray(bytes, length);
        }
        *value = *(T)bytes;
        return length;
    }
    
    static void reversalArray(char *bytes, size_t size);
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
    
    void setEndian(Endian write_endian, Endian read_endian)
    {
        writeEndian = write_endian;
        readEndian = read_endian;
    }
private:
    static Endian getEndian();
    
private:
    SFByteArray(const SFByteArray&);
    SFByteArray& operator=(const SFByteArray&);
private:
    size_t writePos;
    size_t readPos;
    std::vector<char> bytesBuf;
    Endian      writeEndian;
    Endian      readEndian;
};


#endif /* defined(__ByteArrayDemo__SFByteArray__) */
