import javafx.application.Application;
import javafx.scene.*;
import javafx.stage.*;
import javafx.scene.layout.*;
import javafx.scene.control.*;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.*;

public class Student_Course_reg_gui extends Application {

    class Student {
        int id;
        String name;
        String course;

        Student(int id, String name, String course) {
            this.id = id;
            this.name = name;
            this.course = course;
        }
    }

    @Override
    public void start(Stage stage) {

        TextField id = new TextField();
        TextField name = new TextField();

        ComboBox<String> cmb = new ComboBox<>();
        cmb.getItems().addAll("DBMS", "OS", "CN", "AI");

        Label lbl = new Label();

        Button reg = new Button("Register");
        Button drop = new Button("Drop");

        ObservableList<Student> students = FXCollections.observableArrayList();
        TableView<Student> table = new TableView<>(students);

        // Columns
        TableColumn<Student, String> colId = new TableColumn<>("ID");
        colId.setCellValueFactory(d ->
                new SimpleStringProperty(String.valueOf(d.getValue().id)));

        TableColumn<Student, String> colName = new TableColumn<>("Name");
        colName.setCellValueFactory(d ->
                new SimpleStringProperty(d.getValue().name));

        TableColumn<Student, String> colCourse = new TableColumn<>("Course");
        colCourse.setCellValueFactory(d ->
                new SimpleStringProperty(d.getValue().course));

        table.getColumns().addAll(colId, colName, colCourse);

        // Register
        reg.setOnAction(e -> {
            try {
                int sid = Integer.parseInt(id.getText());
                String sname = name.getText();
                String course = cmb.getValue();

                if (sname.isEmpty() || course == null) {
                    lbl.setText("Invalid input");
                    return;
                }

                for (Student s : students) {
                    if (s.id == sid) {
                        lbl.setText("Already registered");
                        return;
                    }
                }

                students.add(new Student(sid, sname, course));
                lbl.setText("Registered");

                id.clear();
                name.clear();

            } catch (Exception ex) {
                lbl.setText("Invalid input");
            }
        });

        // Drop
        drop.setOnAction(e -> {
            try {
                int sid = Integer.parseInt(id.getText());

                for (Student s : students) {
                    if (s.id == sid) {
                        students.remove(s);
                        lbl.setText("Dropped");
                        return;
                    }
                }

                lbl.setText("Student not found");

            } catch (Exception ex) {
                lbl.setText("Invalid input");
            }
        });

        // Layout
        GridPane grid = new GridPane();
        grid.setHgap(10);
        grid.setVgap(10);

        grid.add(new Label("ID"), 0, 0);
        grid.add(id, 1, 0);

        grid.add(new Label("Name"), 0, 1);
        grid.add(name, 1, 1);

        grid.add(new Label("Course"), 0, 2);
        grid.add(cmb, 1, 2);

        HBox actions = new HBox(10, reg, drop);
        VBox root = new VBox(10, grid, actions, table, lbl);

        Scene scene = new Scene(root, 400, 500);
        stage.setScene(scene);
        stage.setTitle("Student Course Registration");
        stage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}