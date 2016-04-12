/**
 * Created by sbxfc on 15/9/23.
 */
function init(){
    var bytes = new ByteArray();
    bytes.writeUTF('中文123');
    bytes.writeByte(127);
    bytes.writeInt(666);
    bytes.writeLong(201412270547);
    bytes.writeDouble(20141227.0547);

    var arraybuffer = bytes.buffer();
    bytes = new ByteArray(arraybuffer);
    document.write(bytes.readUTF());
    document.write("<br>");
    document.write(bytes.readByte().toString());
    document.write("<br>");
    document.write(bytes.readInt().toString());
    document.write("<br>");
    document.write(bytes.readLong().toString());
    document.write("<br>");
    document.write(bytes.readDouble().toString());
}