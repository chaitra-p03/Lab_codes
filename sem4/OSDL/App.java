import javafx.application.Application;
import javafx.scene.*;
import javafx.scene.control.*;
import javafx.scene.layout.*;
import javafx.stage.*;

public class App extends Application {
    public void start(Stage stage) {


    Label nameLabel = new Label("Name:");
        Label emailLabel = new Label("Email:");
        Label roomLabel = new Label("Room Type:");
        Label result = new Label();

        // TextFields
        TextField nameField = new TextField();
        TextField emailField = new TextField();

        // ComboBox
        ComboBox<String> roomType = new ComboBox<>();
        roomType.getItems().addAll("Single", "Double", "Deluxe");

        // Button
        Button submit = new Button("Submit");

        // Event handling
        submit.setOnAction(e -> {
            String name = nameField.getText();
            String email = emailField.getText();
            String room = roomType.getValue();

            if (name.isEmpty() || email.isEmpty() || room == null) {
                result.setText("Please fill all fields");
            } else {
                result.setText(
                    "Name: " + name +
                    "\nEmail: " + email +
                    "\nRoom: " + room
                );

                // Clear fields
                nameField.clear();
                emailField.clear();
                roomType.setValue(null);
            }
        });

        // GridPane layout
        GridPane grid = new GridPane();
        grid.setHgap(10);
        grid.setVgap(10);

        grid.add(nameLabel, 0, 0);
        grid.add(nameField, 1, 0);

        grid.add(emailLabel, 0, 1);
        grid.add(emailField, 1, 1);

        grid.add(roomLabel, 0, 2);
        grid.add(roomType, 1, 2);

        grid.add(submit, 1, 3);
        grid.add(result, 1, 4);

        Scene scene = new Scene(grid, 350, 300);
        stage.setScene(scene);
        stage.setTitle("Hotel Form");
        stage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}