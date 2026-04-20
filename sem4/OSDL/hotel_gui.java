
import javafx.application.Application;
import javafx.scene.*;
import javafx.stage.*;
import javafx.scene.layout.*;
import javafx.scene.control.*;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.*;

import java.util.*;


public class hotel_gui extends Application {

    class Room {
        int number;
        String type;
        double price;
        int days;
        boolean available = true;

        String customer = "-";
        String phone = "-";

        Room(int n, String t, double p) {
            number = n;
            type = t;
            price = p;
        }
    }

    ObservableList<Room> rooms = FXCollections.observableArrayList();

    @Override
    public void start(Stage stage) {

        TextField txtRoomNo = new TextField();
        TextField txtPrice = new TextField();
        TextField txtDays = new TextField();
        ComboBox<String> cmbType = new ComboBox<>();
        cmbType.getItems().addAll("Single", "Double", "Deluxe");

        TextField txtCustName = new TextField();
        TextField txtPhone = new TextField();
        TextField txtBookRoom = new TextField();

        Button btnAddRoom = new Button("Add Room");
        Button btnBook = new Button("Book");
        Button btnCheckout = new Button("Checkout");

        Label lblMsg = new Label();

        TableView<Room> table = new TableView<>(rooms);

        TableColumn<Room, String> colNo = new TableColumn<>("Room No");
        colNo.setCellValueFactory(d ->
                new SimpleStringProperty(String.valueOf(d.getValue().number)));

        TableColumn<Room, String> colType = new TableColumn<>("Type");
        colType.setCellValueFactory(d ->
                new SimpleStringProperty(d.getValue().type));

        TableColumn<Room, String> colPrice = new TableColumn<>("Price");
        colPrice.setCellValueFactory(d ->
                new SimpleStringProperty(String.valueOf(d.getValue().price)));

        TableColumn<Room, String> colAvail = new TableColumn<>("Available");
        colAvail.setCellValueFactory(d ->
                new SimpleStringProperty(
                        d.getValue().available ? "Yes" : "No"));

        TableColumn<Room, String> colCust = new TableColumn<>("Customer");
        colCust.setCellValueFactory(d ->
                new SimpleStringProperty(d.getValue().customer));

        TableColumn<Room, String> colPhone = new TableColumn<>("Phone");
        colPhone.setCellValueFactory(d ->
                new SimpleStringProperty(d.getValue().phone));
                TableColumn<Room, String> coldays = new TableColumn<>("days");
        coldays.setCellValueFactory(d ->
                new SimpleStringProperty(String.valueOf(d.getValue().days)));

        table.getColumns().addAll(colNo, colType, colPrice, colAvail, colCust, colPhone, coldays);

       
        btnAddRoom.setOnAction(e -> {
            try {
                int no = Integer.parseInt(txtRoomNo.getText());
                double price = Double.parseDouble(txtPrice.getText());
                String type = cmbType.getValue();

                rooms.add(new Room(no, type, price));
                lblMsg.setText("Room added");

                txtRoomNo.clear();
                txtPrice.clear();

            } catch (Exception ex) {
                lblMsg.setText("Invalid input");
            }
        });

       
        btnBook.setOnAction(e -> {
            try {
                int roomNo = Integer.parseInt(txtBookRoom.getText());
                int days = Integer.parseInt(txtDays.getText());

                for (Room r : rooms) {
                    if (r.number == roomNo) {

                        if (!r.available) {
                            lblMsg.setText("Already booked");
                            return;
                        }

                        r.available = false;
                        r.customer = txtCustName.getText();
                        r.phone = txtPhone.getText();
                        r.days = days;

                        table.refresh();
                        lblMsg.setText("Booked");
                        return;
                    }
                }

                lblMsg.setText("Room does not exist");

            } catch (Exception ex) {
                lblMsg.setText("Invalid input");
            }
        });

       
        btnCheckout.setOnAction(e -> {
            try {
                int roomNo = Integer.parseInt(txtBookRoom.getText());

                for (Room r : rooms) {
                    if (r.number == roomNo) {

                        if (r.available) {
                            lblMsg.setText("Room is already vacant");
                            return;
                        }
                        double total = r.price * r.days;
                        lblMsg.setText("Bill: " + total);
                        r.available = true;
                        r.customer = "-";
                        r.phone = "-";
                        r.days = 0;
                        table.refresh();
                        return;
                    }
                }

                lblMsg.setText("Room does not exist");

            } catch (NumberFormatException ex) {
                lblMsg.setText("Invalid input");
            }
        });

     
        GridPane grid = new GridPane();
        grid.setHgap(10);
        grid.setVgap(10);

        grid.add(new Label("Room No:"), 0, 0);
        grid.add(txtRoomNo, 1, 0);

        grid.add(new Label("Type:"), 0, 1);
        grid.add(cmbType, 1, 1);

        grid.add(new Label("Price:"), 0, 2);
        grid.add(txtPrice, 1, 2);

        grid.add(btnAddRoom, 1, 3);

        grid.add(new Label("Customer Name:"), 0, 4);
        grid.add(txtCustName, 1, 4);

        grid.add(new Label("Phone:"), 0, 5);
        grid.add(txtPhone, 1, 5);

        grid.add(new Label("Room No (Book/Checkout):"), 0, 6);
        grid.add(txtBookRoom, 1, 6);

        grid.add(new Label("Days:"), 0, 7);
grid.add(txtDays, 1, 7);

        HBox actions = new HBox(10, btnBook, btnCheckout);

        VBox root = new VBox(10, grid, actions, lblMsg, table);

        Scene scene = new Scene(root, 600, 450);
        stage.setTitle("Hotel Management System");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}