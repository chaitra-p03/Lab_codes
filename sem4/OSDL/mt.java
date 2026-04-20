public class mt{
  public static void main(String[] args){
    Taskworker th1 = new Taskworker("alice",101,"running");
    Taskworker th2 = new Taskworker("bob",102,"walking");
    
    Thread t1 = new Thread(th1);
    Thread t2 = new Thread(th2);
    t1.start();
    t2.start();
    
    try {
        t1.join();
        t2.join();
    } catch (InterruptedException e) {
        e.printStackTrace();
    }
    System.out.println("finished");
  }
}


class Worker{
  String name; 
  int id; 
  
  Worker(String name, int id){
    this.name = name;
    this.id = id;
  }
  
  public void showdetails(){
    System.out.println("Name "+ name+" id "+id);
  }
}

class Taskworker extends Worker implements Runnable {
  String task;
  Taskworker(String name, int id, String task){
    super(name,id);
    this.task=task;
  }
  
  @Override
  public void run(){
    showdetails();
    for(int i=0; i<3; i++){
      System.out.println("Performing "+task+" "+i);
      try{
        Thread.sleep(1000);
      } catch (InterruptedException e){
        e.printStackTrace();
      }
    }
  }
}


