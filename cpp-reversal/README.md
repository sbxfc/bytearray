#使用

    ByteArray bytes;
    bytes.writeString(std::string("sbxfc"));
    bytes.writeChars("fc");
    bytes.writeNumber(17);
    bytes.writeBOOL(true);
    bytes.writeNumber((long)1234567890123);
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

    long longValue = 0.0;
    bytes.readNumber(&longValue);
    std::cout << longValue << "\n";

    float f = 0.0;
    bytes.readNumber(&f);
    std::cout << f << "\n";

    double d = bytes.read<double>();
    std::cout << d << "\n";
