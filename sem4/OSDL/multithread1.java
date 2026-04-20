class Loading implements Runnable {
    @Override
    public void run() {
        System.out.println("Loading...");
        try {
            Thread.sleep(2000); // 2 seconds
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}

class Processing implements Runnable {
    @Override
    public void run() {
        System.out.println("Processing...");
        try {
            Thread.sleep(2000); // 2 seconds
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}

class Complete implements Runnable {
    @Override
    public void run() {
        System.out.println("Complete!");
        try {
            Thread.sleep(1000); // 1 second
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}

public class multithread1 {
    public static void main(String[] args) {
        Thread mythread1 = new Thread(new Loading());
        Thread mythread2 = new Thread(new Processing());
        Thread mythread3 = new Thread(new Complete());

        try {
            mythread1.start();
            mythread1.join();

            mythread2.start();
            mythread2.join();  // Thread 3 waits for Thread 2

            mythread3.start(); // Runs after Thread 2 finishes
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}

