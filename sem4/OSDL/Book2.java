import javafx.application.Application;
import javafx.scene.*;
import javafx.stage.*;
import javafx.scene.layout.*;
import javafx.scene.control.*;
import javafx.collections.*;
import javafx.beans.property.SimpleStringProperty;

import java.io.*;
import java.util.*;

    class Book implements Serializable {
        int id;
        String title;
        String author;
        double price;

        Book(int id, String t, String a, double p) {
            this.id = id;
            this.title = t;
            this.author = a;
            this.price = p;
        }
    }

public class Book2 extends Application {

 
    class Record<T> implements Serializable {
        T data;
        Record(T data) { this.data = data; }
        public T get() { return data; }
    }

    ObservableList<Book> list = FXCollections.observableArrayList();

    @Override
    public void start(Stage stage) {

        TextField id = new TextField();
        TextField title = new TextField();
        TextField author = new TextField();
        TextField price = new TextField();

        Label msg = new Label();

        Button add = new Button("Add");
        Button save = new Button("Save");
        Button load = new Button("Load");

        TableView<Book> table = new TableView<>(list);

        TableColumn<Book, String> c1 = new TableColumn<>("ID");
        c1.setCellValueFactory(d ->
                new SimpleStringProperty(String.valueOf(d.getValue().id)));

        TableColumn<Book, String> c2 = new TableColumn<>("Title");
        c2.setCellValueFactory(d ->
                new SimpleStringProperty(d.getValue().title));

        TableColumn<Book, String> c3 = new TableColumn<>("Author");
        c3.setCellValueFactory(d ->
                new SimpleStringProperty(d.getValue().author));

        TableColumn<Book, String> c4 = new TableColumn<>("Price");
        c4.setCellValueFactory(d ->
                new SimpleStringProperty(String.valueOf(d.getValue().price)));

        table.getColumns().addAll(c1, c2, c3, c4);

    
        add.setOnAction(e -> {
            try {
                int bid = Integer.parseInt(id.getText());
                double p = Double.parseDouble(price.getText());

                if (title.getText().isEmpty() || author.getText().isEmpty()) {
                    msg.setText("Enter all fields");
                    return;
                }

                for (Book b : list) {
                    if (b.id == bid) {
                        msg.setText("Already exists");
                        return;
                    }
                }

                list.add(new Book(bid, title.getText(), author.getText(), p));
                msg.setText("Added");

            } catch (Exception ex) {
                msg.setText("Invalid input");
            }
        });

        
        save.setOnAction(e -> {
            try {
                ObjectOutputStream oos =
                        new ObjectOutputStream(new FileOutputStream("books.dat"));

                oos.writeObject(new ArrayList<>(list));
                oos.close();

                msg.setText("Saved");

            } catch (Exception ex) {
                msg.setText("Save error");
            }
        });

        load.setOnAction(e -> {
            try {
                ObjectInputStream ois =
                        new ObjectInputStream(new FileInputStream("books.dat"));

                ArrayList<Book> temp = (ArrayList<Book>) ois.readObject();
                list.setAll(temp);

                ois.close();

                msg.setText("Loaded");

            } catch (Exception ex) {
                msg.setText("Load error");
            }
        });

        GridPane grid = new GridPane();
        grid.setHgap(10);
        grid.setVgap(10);

        grid.add(new Label("ID"), 0, 0);
        grid.add(id, 1, 0);

        grid.add(new Label("Title"), 0, 1);
        grid.add(title, 1, 1);

        grid.add(new Label("Author"), 0, 2);
        grid.add(author, 1, 2);

        grid.add(new Label("Price"), 0, 3);
        grid.add(price, 1, 3);

        grid.add(add, 1, 4);

        HBox actions = new HBox(10, save, load);

        VBox root = new VBox(10, grid, actions, table, msg);

        Scene scene = new Scene(root, 400, 500);
        stage.setScene(scene);
        stage.setTitle("Library System");
        stage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}