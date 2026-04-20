import javafx.application.Application;
import javafx.scene.*;
import javafx.stage.*;
import javafx.scene.layout.*;
import javafx.scene.control.*;
import javafx.collections.*;
import javafx.beans.property.SimpleStringProperty;

import java.util.*;

public class hospital_gui extends Application{
    @Override
    public void start(Stage stage){
        class Appointment{
            int id; 
            String pname;
            String dname = " - "; 
            String date = " - ";
            String time = " - ";

            Appointment(int id, String pname, String dname, String date, String time){
                this.id = id; 
                this.pname = pname; 
                this.dname = dname;
                this.date = date;
                this.time = time;
            }
        }

    TextField id = new TextField();
    TextField name = new TextField();
    TextField dname = new TextField(); 
    TextField date = new TextField();
    TextField time = new TextField();

    Label msg = new Label();

    Button reg = new Button("Register");
    Button search = new Button("Search");
    Button cancel = new Button("cancel");
    Button searchDoc = new Button("Search doc");

    ObservableList<Appointment> list = FXCollections.observableArrayList();
    TableView<Appointment> table = new TableView<>(list);
    TableColumn<Appointment, String> colno = new TableColumn<>("ID");
    colno.setCellValueFactory(d -> new SimpleStringProperty(String.valueOf(d.getValue().id)));

    TableColumn<Appointment,String> colname = new TableColumn<>("Pname");
    colname.setCellValueFactory(d -> new SimpleStringProperty(d.getValue().pname));

    TableColumn<Appointment, String> colname2 = new TableColumn<>("Dname");
    colname2.setCellValueFactory(d -> new SimpleStringProperty(d.getValue().dname));

    TableColumn<Appointment, String> dates = new TableColumn<>("Date");
    dates.setCellValueFactory(d -> new SimpleStringProperty(d.getValue().date));

    TableColumn<Appointment, String> timescol = new TableColumn<>("Time");
    timescol.setCellValueFactory(d -> new SimpleStringProperty(d.getValue().time));

    table.getColumns().addAll(colno, colname, colname2, dates, timescol);

    reg.setOnAction(e -> {
        try{
            int no = Integer.parseInt(id.getText());
            String pname = name.getText();
            String docname = dname.getText();
            String dated = date.getText();
            String times = time.getText();
            if (pname.isEmpty() ||
                docname.isEmpty() ||
                dated.isEmpty() ||
                times.isEmpty()){

                msg.setText("Enter all fields");
                return;
            }

            for(Appointment a : list){
                if(a.id == no){
                    msg.setText("Already exists");
                    return;
                }
            }

            list.add(new Appointment(no, pname, docname, dated, times));
            table.refresh();
            msg.setText("Added Appointment");
            id.clear();
            name.clear();
            dname.clear();
            date.clear();
            time.clear();
        } catch (Exception ex){
            msg.setText("Invalid INput");
            return;
        }
    });


    search.setOnAction(e ->{
        try{
            int sid = Integer.parseInt(id.getText());
            for(Appointment a : list){
                if(a.id==sid){
                    msg.setText("id "+sid+" name " + a.pname + " pname " + a.dname);
                    return;
                }
            }
            msg.setText("Not found");
        } catch (Exception ex){
            msg.setText("Invalid INput");
            return;
        }
    });

    searchDoc.setOnAction(e -> {
    String doc = dname.getText();

    if (doc.isEmpty()) {
        msg.setText("Enter doctor name");
        return;
    }

    String result = "";

    for (Appointment a : list) {
        if (a.dname.equalsIgnoreCase(doc)) {
            result += "ID " + a.id + " " + a.pname + "\n";
        }
    }

    if (result.isEmpty()) {
        msg.setText("No records found");
    } else {
        msg.setText(result);
    }
});

    cancel.setOnAction(e -> {
    try {
        int sid = Integer.parseInt(id.getText());

        if (list.removeIf(x -> x.id == sid)) {
            msg.setText("Removed");
            id.clear();
            return;
        }

        msg.setText("ID not found");
        id.clear();
        return;

    } catch (Exception ex) {
        msg.setText("Invalid input");
        return;
    }
});

    GridPane grid = new GridPane();
    grid.setHgap(10);
    grid.setVgap(10);

    grid.add(new Label("Id: "), 0, 0);
    grid.add(id, 1, 0);
    grid.add(new Label("Patient Name: "), 0, 1);
    grid.add(name, 1 ,1);
    grid.add(new Label("Doc name: "), 0, 2);
    grid.add(dname,1 ,2);
    grid.add(new Label("Date: "), 0, 3);
    grid.add(date,1,3);
    grid.add(new Label("Time: "), 0, 4);
    grid.add(time,1,4);

    grid.add(reg,0,5);
    grid.add(search,1,5);
    grid.add(searchDoc,2,5);
    grid.add(cancel,3,5);

    HBox actions = new HBox(10,reg, search, searchDoc, cancel);
    VBox root = new VBox(10, grid,actions, table, msg);

    Scene scene = new Scene(root, 500, 500);
    stage.setTitle("HOS");
    stage.setScene(scene);
    stage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
    
}
