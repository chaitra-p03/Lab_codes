import java.io.*;

class Student implements Serializable {
    int id;
    String name;
    double marks;

    Student(int id, String name, double marks) {
        this.id = id;
        this.name = name;
        this.marks = marks;
    }
}
public class SerializeDemo {
    public static void main(String[] args) throws Exception {

        Student s1 = new Student(101, "Ravi", 85.5);

        FileOutputStream fis = new FileOutputStream("student.dat");
        ObjectOutputStream oos = new ObjectOutputStream(fis);

        oos.writeObject(s1);
        oos.close();

        System.out.println("Serialized");
    }
}