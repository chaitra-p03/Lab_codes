class Storage<T> {
    T[] arr;
    int idx = 0;
    int capacity;

    Storage(int capacity) {
        this.capacity = capacity;
        arr = (T[]) new Object[capacity];
    }

    void add(T item) {
        if (idx >= capacity) {
            System.out.println("Capacity reached");
            return;
        }
        arr[idx++] = item;
    }

    T get(int index) {
        if (index >= idx) {
            System.out.println("Index out of bounds");
            return null;
        }
        return arr[index];
    }

    void displayAll() {
        for (int i = 0; i < idx; i++) {
            System.out.println(" | " + arr[i]);
        }
    }
}

class BillSummary<T extends Number> {
    T[] arr;
    int size;

    @SuppressWarnings("unchecked")
    BillSummary(int capacity) {
        this.size = capacity;
        arr = (T[]) new Number[capacity]; 
    }

    void add(T item, int index) {
        arr[index] = item;
    }

    double getTotal() {
        double total = 0;
        for (T t : arr) {
            total += t.doubleValue();
        }
        return total;
    }

    double getAverage() {
        return getTotal() / arr.length;
    }

    double getMax() {
        double max = arr[0].doubleValue();
        for (T t : arr) {
            if (t.doubleValue() > max) {
                max = t.doubleValue();
            }
        }
        return max;
    }
}

class Pair<T, U> {
    T first;
    U second;

    Pair(T first, U second) {
        this.first = first;
        this.second = second;
    }

    void display() {
        System.out.println("First: " + first + " | Second: " + second);
    }
}

public class generics1 {

    public static <T extends Comparable<T>> T findMax(T[] items) {
        T max = items[0];
        for (T t : items) {
            if (t.compareTo(max) > 0) {
                max = t;
            }
        }
        return max;
    }

    public static void main(String[] args) {

        
        Storage<String> roomStorage = new Storage<>(3);
        roomStorage.add("Deluxe");
        roomStorage.add("Suite");
        roomStorage.add("Standard");
        roomStorage.displayAll();
        System.out.println("Get index 1: " + roomStorage.get(1));

        
        Storage<Pair<Integer, String>> pairStorage = new Storage<>(2);
        pairStorage.add(new Pair<>(101, "Deluxe"));
        pairStorage.add(new Pair<>(102, "Suite"));
        for (int i = 0; i < pairStorage.idx; i++) {
            pairStorage.get(i).display();
        }

        
        BillSummary<Double> bills = new BillSummary<>(3);
        bills.add(2000.0, 0);
        bills.add(3500.0, 1);
        bills.add(5000.0, 2);
        System.out.println("Total  : " + bills.getTotal());
        System.out.println("Average: " + bills.getAverage());
        System.out.println("Max    : " + bills.getMax());

    
        Double[] prices = {1200.0, 4500.0, 3000.0};
        String[] types  = {"Standard", "Deluxe", "Suite"};
        System.out.println("Most expensive : " + findMax(prices));
        System.out.println("Last alphabetically: " + findMax(types));
    }
}