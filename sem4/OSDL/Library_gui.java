import javafx.application.Application;
import javafx.scene.*;
import javafx.stage.*;
import javafx.scene.layout.*;
import javafx.scene.control.*;
import javafx.collections.*;
import javafx.beans.property.SimpleStringProperty;

import java.util.*;

public class Library_gui extends Application{
    @Override
    public void start(Stage stage){
        class Book{
            int id;
            String title; 
            String author; 
            Double price;
            String status = "Available";
            String borrower = " - ";

            Book(int id, String title, String author, Double price){
                this.id=id;
                this.title=title;
                this.author=author;
                this.price=price;
            }
        }

        TextField bid = new TextField();
        TextField btitle = new TextField();
        TextField bauthor = new TextField();
        TextField bprice = new TextField();
        TextField bborrower = new TextField();
        TextField days = new TextField();

        ComboBox<String> cmb = new ComboBox<>();
        cmb.getItems().addAll("Available","issued");

        Label lbl = new Label();
        
        Button add = new Button("add");
        Button issue = new Button("issue");
        Button returnb = new Button("return");
        Button author = new Button("search author");
        Button delete = new Button("delete");

        ObservableList<Book> books = FXCollections.observableArrayList();

        TableView<Book> table = new TableView<>(books);
        TableColumn<Book,String> colid = new TableColumn<>("Id");
        colid.setCellValueFactory(d -> new SimpleStringProperty(String.valueOf(d.getValue().id)));
        TableColumn<Book,String> coltitle = new TableColumn<>("Title");
        coltitle.setCellValueFactory(d -> new SimpleStringProperty(d.getValue().title));
        TableColumn<Book,String> colauthor = new TableColumn<>("Author");
        colauthor.setCellValueFactory(d -> new SimpleStringProperty(d.getValue().author));
        TableColumn<Book,String> colprice = new TableColumn<>("Price");
        colprice.setCellValueFactory(d -> new SimpleStringProperty(String.valueOf(d.getValue().price)));
        TableColumn<Book,String> colstat = new TableColumn<>("Status");
        colstat.setCellValueFactory(d -> new SimpleStringProperty(d.getValue().status));
        TableColumn<Book,String> colbor = new TableColumn<>("Borrower");
        colbor.setCellValueFactory(d -> new SimpleStringProperty(d.getValue().borrower));

        table.getColumns().addAll(colid,coltitle,colauthor,colprice,colstat,colbor);




        add.setOnAction(d ->{
            try{
                int bookid = Integer.parseInt(bid.getText());
                String booktitle = btitle.getText();
                String auth = bauthor.getText();
                Double price = Double.parseDouble(bprice.getText()); 
                if(booktitle.isEmpty() || auth.isEmpty() ){
                    lbl.setText("Enter all fields!");
                    return;
                } 
                for(Book b : books){
                    if(b.id==bookid){
                        lbl.setText("Already exists");
                        return;
                    }
                }

                Book newBook = new Book(bookid, booktitle, auth, price);

            if (cmb.getValue() != null) {
                newBook.status = cmb.getValue();
            }

            books.add(newBook);
            table.refresh();
            }catch (Exception ex) {
                lbl.setText("Invalid input");
            }
        });
        issue.setOnAction(d -> {
            try{
                int bookid = Integer.parseInt(bid.getText());
                String bname = bborrower.getText();
                int found = 0; 
                for(Book b : books){
                    if(b.id==bookid){
                        found = 1;
                        if(b.status.equals("issued")){
                            lbl.setText("Already issued");
                            bid.clear();
                            bborrower.clear();
                            return;
                        }
                    }
                }
                if(found==0){
                    lbl.setText("Book not found");
                    return;
                }
                for(Book b : books){
                    if(b.id==bookid){
                        b.status="issued";
                        b.borrower = bname;
                        lbl.setText("ISSUED");
                        table.refresh();
                        return;
                    }
                }

            } catch (Exception ex) {
                lbl.setText("Invalid input");
            }
        });

        returnb.setOnAction(e -> {
            int bookid = Integer.parseInt(bid.getText());
            int bdays = Integer.parseInt(days.getText());
            double total = 0;
            for(Book b : books){
                if(b.id==bookid){
                    if(b.status.equals("Available")){
                        lbl.setText("Already returned");
                        return;
                    }
                    total = bdays * 10;
                    b.status="Available";
                    b.borrower = "-";
                    lbl.setText("Returned. Price is"+total);
                    table.refresh();
                    return;
                }
            }
        });

        author.setOnAction(e -> {
            String aname = bauthor.getText();
            String result = "";
            for(Book b : books){
                if(b.author.equals(aname)){
                    result+="ID" + b.id + "-" + b.title+" || ";
                }
            }
            if(result.isEmpty()){
                lbl.setText("Not found");
            }else {
                lbl.setText(result);
            }
        });

        delete.setOnAction(e -> {
            try{
                int delid = Integer.parseInt(bid.getText());
                if(books.removeIf(x -> x.id == delid)){
                lbl.setText("Removed"); 
                return;
                }
                lbl.setText("Not found");
            } catch (Exception ex){
                lbl.setText("Invalid input");
                return;
            }
        });

        GridPane grid = new GridPane();
        grid.setVgap(10);
        grid.setHgap(10);

        grid.add(new Label("  ID"), 0,0 );
        grid.add(bid,1,0);
        grid.add(new Label("  Title"),0,1);
        grid.add(btitle,1,1);
        grid.add(new Label("  Author"), 0,2 );
        grid.add(bauthor,1,2);
        grid.add(new Label("  Price"), 0,3 );
        grid.add(bprice,1,3);
        grid.add(add,2,3);
        grid.add(new Label("  borrower"), 0,4 );
        grid.add(bborrower,1,4);
        grid.add(new Label("  days"), 0, 5);
        grid.add(days,1,5);
        grid.add(new Label("  Status"),0,6);
        grid.add(cmb,1,6);

        HBox actions = new HBox(10,issue,returnb,author,delete);
        VBox root = new VBox(10, grid, actions, lbl, table);

        Scene scene = new Scene(root,600,600);
        stage.setTitle("LIB");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}