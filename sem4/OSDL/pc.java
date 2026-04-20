class Buffer{
    private int data;
    private boolean available = false;

    public synchronized void produce(int value){
        while(available){
            try{
                wait();
            } catch (InterruptedException e){
                e.printStackTrace();
            }
        }
        data = value;
        System.out.println("Produced: "+ data);
        available = true;
        notify();
    }

    public synchronized int consume(){
        while(!available){
            try{
                wait();
            } catch (InterruptedException e){
                e.printStackTrace();
            }
        }
        System.out.println("Consumed: "+ data);
        available=false;
        notify();
        return data;
    }
}

class Producer extends Thread{
    Buffer buffer;
    Producer(Buffer b){
        buffer = b; 
    }

    public void run(){
        for(int i=1; i<=5; i++){
            buffer.produce(i);
        try{
            Thread.sleep(500);
        } catch (InterruptedException e){
            e.printStackTrace();
        }
        }
    }
}

class Consumer extends Thread {
    Buffer buffer;
    
    Consumer(Buffer b) {
        buffer = b;
    }
    
    public void run() {
        for(int i = 1; i <= 5; i++) {
            buffer.consume();
            try {
                Thread.sleep(500); // Consumer is slower
            } catch(InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}

public class pc {
    public static void main(String[] args) {
        Buffer buffer = new Buffer();
        Producer p = new Producer(buffer);
        Consumer c = new Consumer(buffer);
        
        p.start();
        c.start();
    }
}
