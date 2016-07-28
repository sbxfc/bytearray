/*
 *  DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *  Version 2, December 2004
 *
 *  Copyright (C) 2013-2016 sbxfc http://rungame.me
 *
 *  Everyone is permitted to copy and distribute verbatim or modified
 *  copies of this license document, and changing it is allowed as long
 *  as the name is changed.
 *
 *  DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 *  0. You just DO WHAT THE FUCK YOU WANT TO.
 */

#ifndef __SF__ByteArray__
#define __SF__ByteArray__

#include <stdio.h>
#include <vector>
#include <string>

enum Endian
{
    BIGENDIAN = 0,
    LITENDIAN = 1
};

class ByteArray
{
    
public:
    ByteArray(int allocSize = 1);
    ~ByteArray();
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
     * 写入多个字节数据
     */
    void writeChars(const char *chars);
    
    /**
     * 写入多个字节数据
     * @param chars 字节数据
     * @param length 字节数据长度
     * @param offset 从偏移量(writePosition+offset)开始写入
     */
    void writeChars(const char *chars, size_t length, int offset = 0);
    
    /**
     * 写入一个数字
     * @param value 数字(int long double float)
     */
    template <typename Number>
    int writeNumber(Number value)
    {
        char bytes[sizeof(value)];
        
        /*进行网络通信传输时,第三个参数应该设为BIGENDIAN*/
        int size = numberToBytes(value, bytes, BIGENDIAN);
        writeChars(bytes, size);
        return size;
    }
    
    /**
     * 写入一个字符串
     */
    void writeString(const std::string &value);
    
public:
    
    /**
     * 读取一个字节
     */
    char readByte();
    
    /**
     * 读取一个布尔值
     */
    bool readBOOL();
    
    /**
     * 读取多个字节
     */
    void readChars(char *val, size_t size);
    
    /**
     * 读取多个字节
     */
    bool readBytes(char *value, size_t size, int offset = 0);
    std::string readString();
    
    /**
     * 读取一个数字
     */
    template <typename Number>
    int readNumber(Number *value)
    {
        const int length = sizeof(*value);
        char bytes[length];
        readChars(bytes, length);
        bytesToNumber(value, bytes, BIGENDIAN);
        return length;
    }
    
    /**
     *
     */
    template <typename Number>
    Number read()
    {
        Number value;
        const int length = sizeof(value);
        char bytes[length];
        readBytes(bytes, length);
        bytesToNumber(&value, bytes, BIGENDIAN);
        return value;
    }
    
private:
    /**
     *
     * @param value 数值
     */
    template <typename T>
    int numberToBytes(T value, char *bytes, Endian endian)
    {
        int size = sizeof(value);
        *(T *)bytes = value;
        if(endian == getDeviceEndian()){
            return size;
        }
        else{
            reversalArray(bytes, size);
            return size;
        }
    }
    
    template <typename T>
    int bytesToNumber(T value, char *bytes, Endian endian)
    {
        int length = sizeof(*value);
        if(endian == getDeviceEndian()){
            
        }
        else{
            reversalArray(bytes, length);
        }
        *value = *(T)bytes;
        return length;
    }
    
    static void reversalArray(char *bytes, size_t size);
public:
    
    const char* data() const
    {
        return buffer.data();
    }
    
    size_t size()
    {
        return buffer.size();
    }
    
    size_t readableBytes() const
    {
        return writePosition - readPosition;
    }
    
    size_t writableBytes() const
    {
        return buffer.size() - writePosition;
    }
    
private:
    static Endian getDeviceEndian();
    
private:
    ByteArray(const ByteArray&);
    ByteArray& operator=(const ByteArray&);
private:
    
    /**
     * 当前写入的字节位置
     */
    size_t writePosition;
    
    /**
     * 当前读到的字节位置
     */
    size_t readPosition;
    std::vector<char> buffer;
};


#endif /* defined(__demo__ByteArray__) */
