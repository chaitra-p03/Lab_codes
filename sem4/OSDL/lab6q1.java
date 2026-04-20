import java.io.*;
import java.util.Scanner;

public class lab6q1 {

    static final int NAME_SIZE = 20; 
    static final int RECORD_SIZE = 4 + (2 * NAME_SIZE) + 8 + 1;

    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);
        RandomAccessFile raf = new RandomAccessFile("rooms.dat", "rw");

        while (true) {
            System.out.println("\n1. Add Room");
            System.out.println("2. View Room");
            System.out.println("3. Update Booking");
            System.out.println("4. Exit");
            System.out.print("Enter choice: ");
            int ch = sc.nextInt();

            switch (ch) {
                case 1:
                    addRoom(raf, sc);
                    break;
                case 2:
                    viewRoom(raf, sc);
                    break;
                case 3:
                    updateRoom(raf, sc);
                    break;
                case 4:
                    raf.close();
                    return;
            }
        }
    }

    // ADD ROOM
    static void addRoom(RandomAccessFile raf, Scanner sc) throws Exception {
        System.out.print("Room No: ");
        int roomNo = sc.nextInt();
        sc.nextLine();
        System.out.print("Room Type: ");
        String type = sc.nextLine();
        System.out.print("Price: ");
        double price = sc.nextDouble();
        System.out.print("Booked (true/false): ");
        boolean status = sc.nextBoolean();

        raf.seek(raf.length());

        raf.writeInt(roomNo);
        writeFixedString(raf, type);
        raf.writeDouble(price);
        raf.writeBoolean(status);

        System.out.println("Room added.");
    }

    // VIEW ROOM
    static void viewRoom(RandomAccessFile raf, Scanner sc) throws Exception {
        System.out.print("Enter room number: ");
        int roomNo = sc.nextInt();

        int index = findRoom(raf, roomNo);

        if (index == -1) {
            System.out.println("Room not found.");
            return;
        }

        raf.seek(index * RECORD_SIZE);

        System.out.println("Room No: " + raf.readInt());
        System.out.println("Type: " + readFixedString(raf));
        System.out.println("Price: " + raf.readDouble());
        System.out.println("Booked: " + raf.readBoolean());
    }

    // UPDATE BOOKING
    static void updateRoom(RandomAccessFile raf, Scanner sc) throws Exception {
        System.out.print("Enter room number: ");
        int roomNo = sc.nextInt();

        int index = findRoom(raf, roomNo);

        if (index == -1) {
            System.out.println("Room not found.");
            return;
        }

        raf.seek(index * RECORD_SIZE);

        raf.readInt();
        readFixedString(raf);
        raf.readDouble();

        System.out.print("Set booking status (true/false): ");
        boolean newStatus = sc.nextBoolean();

        raf.writeBoolean(newStatus);

        System.out.println("Updated successfully.");
    }

    // FIND ROOM INDEX
    static int findRoom(RandomAccessFile raf, int roomNo) throws Exception {
        int total = (int) (raf.length() / RECORD_SIZE);

        for (int i = 0; i < total; i++) {
            raf.seek(i * RECORD_SIZE);
            int r = raf.readInt();
            if (r == roomNo)
                return i;
        }
        return -1;
    }

    // WRITE FIXED STRING
    static void writeFixedString(RandomAccessFile raf, String s) throws Exception {
        StringBuilder sb = new StringBuilder(s);
        sb.setLength(NAME_SIZE);
        raf.writeChars(sb.toString());
    }

    // READ FIXED STRING
    static String readFixedString(RandomAccessFile raf) throws Exception {
        char[] chars = new char[NAME_SIZE];
        for (int i = 0; i < NAME_SIZE; i++)
            chars[i] = raf.readChar();
        return new String(chars).trim();
    }
}