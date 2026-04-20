import java.util.*;

class Book{
    int id;
    String title;
    String author;
    double price;
    boolean avail;

    Book(int id, String title, String author, double price){
        this.id = id; 
        this.title = title;
        this.author = author;
        this.price = price;
        this.avail = true;
    }

    void display(){
        System.out.println("\nID| "+id+" |title| " + title + " |author| "+author+" |price| "+price+" |avail| "+avail);
    }
}

class Member{
    int mid;
    String name; 
    int phone; 
    int bid;

    Member(int mid, String name, int phone){
        this.mid = mid;
        this.name = name;
        this.phone = phone; 
        this.bid = -1;
    }

    void display(){
        System.out.println("\nMID| "+mid+" |name| " + name + " |phone| "+phone+" |bid| "+bid);
    }
}


public class collections_lib {
    static ArrayList<Book> books = new ArrayList<>();
    static ArrayList<Member> members = new ArrayList<>();
    static HashMap<Integer,Member> map = new HashMap<>();

    static Scanner sc = new Scanner(System.in);

    // add new books
    static void addbook(){
        System.out.println("Enter id, title, author, price: ");
        int id = sc.nextInt();
        sc.nextLine();
        String title = sc.nextLine();
        String author = sc.nextLine();
        double price = sc.nextDouble();
        sc.nextLine();
        for (Book b : books) {
        if (b.id == id) {
            System.out.println("Book already exists");
            return;
        }
    }
        books.add(new Book(id, title, author, price));
        return;
    }

    // display avail books
    static void displayavail(){
        for(Book b : books){
            if(b.avail){
                b.display();
            }
        }
    }

    // add member
    static void addmember(){
        System.out.println("Enter mid, name, phone: ");
        int mid = sc.nextInt();
        sc.nextLine();
        String name = sc.nextLine();
        int phone = sc.nextInt();
        sc.nextLine();
        for (Member m : members) {
        if (m.mid == mid) {
            System.out.println(" Memeber already exists");
            return;
        }
    }
            members.add(new Member(mid, name, phone));

    }

    // display member
    static void displaymember(){
        for(Member m : members){
            m.display();
        }
    }

    // remove member
    static void removemember(){
    System.out.println("Enter id to remove: ");
    int id = sc.nextInt();

    Iterator<Member> it = members.iterator();

    while(it.hasNext()){
        Member m = it.next();

        if(m.mid == id){

            if(m.bid != -1){
                System.out.println("Cannot remove member with issued book");
                return;
            }

            it.remove();
            System.out.println("Member removed");
            return;
        }
    }

    System.out.println("Member does not exist");
}

    static Book getbook(int bid){
        for(Book b : books){
            if(b.id==bid){
                return b;
            }
        }
        return null;
    }

    // issue book
    static void issue(){
        System.out.println("Enter mid and bid: ");
        int mid = sc.nextInt();
        int bid = sc.nextInt();

        // check for bid
        Book b = getbook(bid);
        if(b == null || b.avail==false){
            System.out.println("Not available");
            return;
        }

        // check for mid
        for(Member m : members){
            if(m.mid==mid){
                if (m.bid != -1) {
                System.out.println("Member already has a book");
                return;
                }
                b.avail = false;
                m.bid = bid;
                map.put(bid,m);
                System.out.println("Booking successful");
                return;
            }
        }
        System.out.println("Customer not found");

    }

    static void returnbook(){
        System.out.println("Enter bid to return: ");
        int bid = sc.nextInt();
        if(!map.containsKey(bid)){
            System.out.println("Not possible");
            return;
        }
        Book b = getbook(bid);
        b.avail=true;
        Member m = map.get(bid);
        m.bid = -1;
        map.remove(bid);
        System.out.println("Returned");

    }

    static void sort(){
        Collections.sort(books, (a,b) -> Double.compare(b.price, a.price));
        displayavail();
    }

    public static void main(String[] args) {
        int idx = -1; 
        while(true){
            System.out.println("\nEnter 1. Add book\n 2. Add memeber\n 3. display avail\n 4.display member\n5. Remove member\n6.issuebook\n7.Return book\n8.Sort\n9Exit");
            idx = sc.nextInt();
            switch (idx) {
                case 1: addbook();
                break;
                case 2: addmember();
                break;
                case 3: displayavail(); break;
                case 4: displaymember(); break;
                case 5: removemember(); break;
                case 6: issue(); break;
                case 7: returnbook(); break;
                case 8: sort(); break;
                case 9: System.out.println("Exiting"); return;
                default:
                    System.out.println("Enter valid!"); break;
            }
        }
    }


}
