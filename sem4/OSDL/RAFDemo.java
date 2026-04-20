import java.io.*;

public class RAFDemo {
    public static void main(String[] args) throws Exception {

        RandomAccessFile raf = new RandomAccessFile("data.txt", "rw");

        // WRITE
        raf.writeInt(101);          // 4 bytes
        raf.writeUTF("Java");       // variable size
        raf.writeDouble(95.5);      // 8 bytes

        // MOVE POINTER TO START
        raf.seek(0);

        // READ
        int id = raf.readInt();
        String name = raf.readUTF();
        double marks = raf.readDouble();

        System.out.println(id + " " + name + " " + marks);

        raf.close();
    }
}