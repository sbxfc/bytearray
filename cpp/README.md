

#使用

  ByteArray byteArray;
  byteArray.writeByte(4);

  std::cout <<"可读取的字节长度:"<< byteArray.readableBytes() << "\n";

  byteArray.writeShort(32767);
  byteArray.writeLong(-2147483647);
  byteArray.writeString("sbxfc");

  std::cout <<"字节长度:"<< byteArray.size() << "\n";

  char byteValue = byteArray.readByte();
  int asc2Value = byteValue;
  std::cout << asc2Value << "\n";

  short shortValue = byteArray.readShort();
  std::cout << shortValue << "\n";

  std::cout <<"可读取的字节长度:"<< byteArray.readableBytes() << "\n";

  long longValue = byteArray.readLong();
  std::cout << longValue << "\n";

  std::string strValue = byteArray.readString();
  std::cout << strValue << "\n";
