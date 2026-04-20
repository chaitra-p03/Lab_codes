class OddNumbers implements Runnable {
    @Override
    public void run() {
        for (int i = 1; i <= 9; i += 2) {
            System.out.println(Thread.currentThread().getName() + ": " + i);
            Thread.yield(); // Hint scheduler to switch thread
        }
    }
}

class EvenNumbers implements Runnable {
    @Override
    public void run() {
        for (int i = 2; i <= 10; i += 2) {
            System.out.println(Thread.currentThread().getName() + ": " + i);
            Thread.yield(); // Hint scheduler to switch thread
        }
    }
}

public class multithread2 {
    public static void main(String[] args) {
        Thread t1 = new Thread(new OddNumbers(), "Odd-Thread");
        Thread t2 = new Thread(new EvenNumbers(), "Even-Thread");

        t1.start();
        t2.start();
    }
}
