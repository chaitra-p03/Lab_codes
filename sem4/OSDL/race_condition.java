class Counter {
    int count = 0;

    synchronized public void increment() { //synchronized word before the method prevents race condition
        count++;  
    }
}

class IncrementTask implements Runnable {
    Counter counter;

    public IncrementTask(Counter counter) {
        this.counter = counter;
    }

    @Override
    public void run() {
        for (int i = 0; i < 100000; i++) {
            counter.increment();
        }
    }
}

public class race_condition {
    public static void main(String[] args) throws InterruptedException {
        Counter counter = new Counter();

        Thread t1 = new Thread(new IncrementTask(counter));
        Thread t2 = new Thread(new IncrementTask(counter));

        t1.start();
        t2.start();

        t1.join();
        t2.join();

        System.out.println("Expected: 200000");
        System.out.println("Actual: " + counter.count);
    }
}
