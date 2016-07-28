
基于HTML5的网络字节流解析,支持UTF-8格式的读写.

#使用

    var bytes = new ByteArray();
    bytes.writeUTF('中文123');
    bytes.writeByte(127);
    bytes.writeInt(666);
    bytes.writeLong(201412270547);
    bytes.writeDouble(20141227.0547);

    var arraybuffer = bytes.buffer();
    bytes = new ByteArray(arraybuffer);
    var str = bytes.readUTF();
    var byteValue = bytes.readByte();
    var intValue = bytes.readInt();
    var longValue = bytes.readLong();
    var floatValue = bytes.readDouble();

#参见

- https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Reference/Global_Objects/ArrayBuffer

- https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Reference/Global_Objects/DataView
