import java.util.*;

class Room {
    int rno;
    String type;
    double price;
    boolean available;

    Room(int rno, String type, double price) {
        this.rno = rno;
        this.type = type;
        this.price = price;
        this.available = true;
    }

    void display() {
        System.out.println("Room: " + rno + " | " + type + " | " + price + " | Available: " + available);
    }
}

class Customer {
    int id;
    String name;
    String phone;
    int roomNo;

    Customer(int id, String name, String phone) {
        this.id = id;
        this.name = name;
        this.phone = phone;
        this.roomNo = -1;
    }

    void display() {
        System.out.println("ID: " + id + " | " + name + " | " + phone + " | Room: " + roomNo);
    }
}

public class collections_hotel {

    static ArrayList<Room> rooms = new ArrayList<>();
    static ArrayList<Customer> customers = new ArrayList<>();
    static HashMap<Integer, Customer> map = new HashMap<>();

    static Scanner sc = new Scanner(System.in);

    // Add Room
    static void addRoom() {
        System.out.print("Enter room no, type, price: ");
        int rno = sc.nextInt();
        String type = sc.next();
        double price = sc.nextDouble();

        rooms.add(new Room(rno, type, price));
    }

    // Display Available Rooms
    static void displayRooms() {
        for (Room r : rooms) {
            if (r.available) {
                r.display();
            }
        }
    }

    // Find Room
    static Room findRoom(int rno) {
        for (Room r : rooms) {
            if (r.rno == rno) return r;
        }
        return null;
    }

    // Add Customer
    static void addCustomer() {
        System.out.print("Enter id, name, phone: ");
        int id = sc.nextInt();
        String name = sc.next();
        String phone = sc.next();

        customers.add(new Customer(id, name, phone));
    }

    // Book Room
    static void bookRoom() {
        System.out.print("Enter customer id and room no: ");
        int id = sc.nextInt();
        int rno = sc.nextInt();

        Room r = findRoom(rno);

        if (r == null || !r.available) {
            System.out.println("Room not available");
            return;
        }

        for (Customer c : customers) {
            if (c.id == id) {
                c.roomNo = rno;
                r.available = false;
                map.put(rno, c);
                System.out.println("Booking successful");
                return;
            }
        }

        System.out.println("Customer not found");
    }

    // Checkout
    static void checkout() {
        System.out.print("Enter room no: ");
        int rno = sc.nextInt();

        if (!map.containsKey(rno)) {
            System.out.println("Room not booked");
            return;
        }

        Customer c = map.get(rno);
        c.roomNo = -1;

        Room r = findRoom(rno);
        if (r != null) r.available = true;

        map.remove(rno);

        System.out.println("Checkout done");
    }

    // Display Customers
    static void displayCustomers() {
        for (Customer c : customers) {
            c.display();
        }
    }

    // Sort Rooms by Price
    static void sortRooms() {
        Collections.sort(rooms, (a, b) -> Double.compare(a.price, b.price));
        System.out.println("Rooms sorted by price");
    }

    // Main Menu
    public static void main(String[] args) {

        while (true) {
            System.out.println("\n1.Add Room\n2.Display Rooms\n3.Add Customer\n4.Book Room\n5.Checkout\n6.Display Customers\n7.Sort Rooms\n8.Exit");
            int ch = sc.nextInt();

            switch (ch) {
                case 1: addRoom(); break;
                case 2: displayRooms(); break;
                case 3: addCustomer(); break;
                case 4: bookRoom(); break;
                case 5: checkout(); break;
                case 6: displayCustomers(); break;
                case 7: sortRooms(); break;
                case 8: return;
                default: System.out.println("Invalid choice");
            }
        }
    }
}