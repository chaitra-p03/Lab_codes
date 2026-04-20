import java.util.*;

class Vehicle{
    int no; 
    String type; 
    double fee; 
    boolean parked;

    Vehicle(int no, String type, double fee){
        this.no = no;
        this.type = type; 
        this.fee = fee;
        parked = false;
    }

    void display(){
        System.out.println("No " + no+ "|type|" + type + "|parked|"+parked + "|FEE|" + fee);
    }
}

class Owner{
    int id; 
    String name; 
    String phone; 
    int parkedno;

    Owner(int id, String name, String phone){
        this.id = id;
        this.name = name; 
        this.phone = phone;
        parkedno = -1;
    }

    void display(){
        System.out.println("ID " + id+ "|name|" + name + "|parked no|"+parkedno);
    }
}


public class collections_parking {
    static ArrayList<Vehicle> vehicles = new ArrayList<>();
    static ArrayList<Owner> owners = new ArrayList<>();
    static HashMap<Integer, Owner> map = new HashMap<>();

    static Scanner sc = new Scanner(System.in);

    // add vehicle
    static void addvehicle(){
        System.out.println("Enter no, type, fee: ");
        int no = sc.nextInt();
        sc.nextLine();
        String type = sc.nextLine();
        double fee = sc.nextDouble();
        sc.nextLine();

        for(Vehicle v : vehicles){
            if(v.no==no){
                System.out.println("Already exists");
                return;
            }
        }

        vehicles.add(new Vehicle(no, type, fee));
    }

    // add owner
    static void addowner(){
        System.out.println("Enter id, name, phone: ");
        int id = sc.nextInt();
        sc.nextLine();
        String name = sc.nextLine();
        String phone = sc.nextLine();

        for(Owner o : owners){
            if(o.id==id){
                System.out.println("Already exists");
                return;
            }
        }

        owners.add(new Owner(id, name, phone));
    }

    static Owner getowner(int id){
        for(Owner o : owners){
            if(o.id == id) return o;
        }
        return null;
    }
    static Vehicle getvehicle(int no){
    for(Vehicle v : vehicles){
        if(v.no == no) return v;
    }
    return null;
}
    // park 
    static void park(){
        System.out.println("Enter id of owner, no of car to park: ");
        int id = sc.nextInt();
        int no = sc.nextInt();

        Owner o = getowner(id);
        if(o == null){
            System.out.println("Owner not found");
            return;
        }
        if(o.parkedno != -1){
            System.out.println("Owner already has a vehicle parked");
            return;
        }
        Vehicle v = getvehicle(no);
        if(v == null){
            System.out.println("Vehicle not found");
            return;
        }
        if(v.parked){
            System.out.println("Vehicle already parked");
            return;
        }
        map.put(no,o);
        o.parkedno = no;
        v.parked = true;
        System.out.println("Parked");
    }
    // remove 
    static void unpark(){
        System.out.println("Enter vno to unpark: ");
        int n = sc.nextInt();
        sc.nextLine();
        Vehicle v = getvehicle(n);
        if(v==null){
            System.out.println("Vehicle not found");
            return;
        }
        if(!map.containsKey(n)){
            System.out.println("Already unparked");
            return;
        }
        Owner o = map.get(n);
        map.remove(n);
        v.parked=false;
        o.parkedno=-1;
        System.out.println("UNPARKED");

    }

    static void orderby(){
        Collections.sort(vehicles, (a,b) -> Double.compare(b.fee, a.fee));
        for(Vehicle v : vehicles){
            v.display();
        }
    }

    public static void main (String[] args){
        System.out.println("Enter: ");
        int idx = -1; 
        while(true){
            System.out.println("1.Add vehicle\n2.Add owner\n3.Park\n4.Unpark\n5.Orderby\n6.Exit");
            idx = sc.nextInt();
            sc.nextLine();
            switch(idx){
                case 1: addvehicle(); break;
                case 2: addowner(); break;
                case 3: park(); break;
                case 4: unpark(); break;
                case 5: orderby(); break;
                case 6: System.out.println("Exiting"); return;

            }
        }
    }
}
