import java.io.*;
import java.util.*;


class Room implements Serializable {
    int number;
    String type;
    double price;
    boolean booked;
    String guest;

    Room(int number, String type, double price) {
        this.number = number;
        this.type = type;
        this.price = price;
        this.booked = false;
        this.guest = "-";
    }

    void display() {
        System.out.println(number + " | " + type + " | " + price +
                " | " + (booked ? "Booked" : "Available") +
                " | " + guest);
    }
}


public class lab6q2 {

    static final String FILE = "rooms.dat";

   
    static void save(ArrayList<Room> rooms) {
        try (ObjectOutputStream oos =
                     new ObjectOutputStream(new FileOutputStream(FILE))) {
            oos.writeObject(rooms);
        } catch (IOException e) {
            System.out.println("Error saving file");
        }
    }

    
    static ArrayList<Room> load() {
        try (ObjectInputStream ois =
                     new ObjectInputStream(new FileInputStream(FILE))) {
            return (ArrayList<Room>) ois.readObject();
        } catch (Exception e) {
            return new ArrayList<>();
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        ArrayList<Room> rooms = load();

        while (true) {
            System.out.println("\n1.Add Room\n2.Display All\n3.Search\n4.Book\n5.Exit");
            int ch = sc.nextInt();

            switch (ch) {

                
                case 1:
                    System.out.print("Enter no, type, price: ");
                    int no = sc.nextInt();
                    String type = sc.next();
                    double price = sc.nextDouble();

                    rooms.add(new Room(no, type, price));
                    save(rooms);
                    break;

               
                case 2:
                    for (Room r : rooms) r.display();
                    break;

              
                case 3:
                    System.out.print("Enter room no: ");
                    int s = sc.nextInt();
                    boolean found = false;

                    for (Room r : rooms) {
                        if (r.number == s) {
                            r.display();
                            found = true;
                        }
                    }

                    if (!found) System.out.println("Not found");
                    break;

              
                case 4:
                    System.out.print("Enter room no: ");
                    int b = sc.nextInt();
                    sc.nextLine();

                    for (Room r : rooms) {
                        if (r.number == b) {

                            if (r.booked) {
                                System.out.println("Already booked");
                                break;
                            }

                            System.out.print("Enter guest name: ");
                            r.guest = sc.nextLine();
                            r.booked = true;

                            save(rooms); 
                            System.out.println("Booked");
                            break;
                        }
                    }
                    break;

                case 5:
                    return;

                default:
                    System.out.println("Invalid");
            }
        }
    }
}