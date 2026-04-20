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
public class DeserializeDemo {
    public static void main(String[] args) throws Exception {

        ObjectInputStream ois =
            new ObjectInputStream(new FileInputStream("student.dat"));

        Student s = (Student) ois.readObject();

        System.out.println(s.id);
        System.out.println(s.name);
        System.out.println(s.marks);

        ois.close();
    }
}