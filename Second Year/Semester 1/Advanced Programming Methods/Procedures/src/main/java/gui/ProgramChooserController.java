package gui;

import controller.Controller;
import exceptions.InterpreterException;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.util.Pair;
import model.expression.*;
import model.programState.ProgramState;
import model.statement.*;
import model.type.BoolType;
import model.type.IntType;
import model.type.RefType;
import model.type.StringType;
import model.utils.*;
import model.value.BoolValue;
import model.value.IntValue;
import model.value.StringValue;
import model.value.Value;
import repository.IRepository;
import repository.Repository;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class ProgramChooserController {
    private ProgramExecutorController programExecutorController;
    private MyIProcTable procTable;

    public void setProgramExecutorController(ProgramExecutorController programExecutorController) {
        this.programExecutorController = programExecutorController;
    }
    @FXML
    private ListView<IStatement> programsListView;

    @FXML
    private Button displayButton;

    @FXML
    public void initialize() {
        this.procTable = new MyProcTable();
        programsListView.setItems(getAllStatements());
        programsListView.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
    }

    @FXML
    private void displayProgram(ActionEvent actionEvent) {
        IStatement selectedStatement = programsListView.getSelectionModel().getSelectedItem();
        if (selectedStatement == null) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error encountered!");
            alert.setContentText("No statement selected!");
            alert.showAndWait();
        } else {
            int id = programsListView.getSelectionModel().getSelectedIndex();
            try {
                selectedStatement.typeCheck(new MyDictionary<>());
                MyIStack<MyIDictionary<String, Value>> symTableStack = new MyStack<>();
                symTableStack.push(new MyDictionary<>());
                ProgramState programState = new ProgramState(new MyStack<>(), symTableStack, new MyList<>(), new MyDictionary<>(), new MyHeap(), procTable, selectedStatement);
                IRepository repository = new Repository(programState, "log" + (id + 1) + ".txt");
                Controller controller = new Controller(repository);
                programExecutorController.setController(controller);
            } catch (InterpreterException | IOException exception) {
                Alert alert = new Alert(Alert.AlertType.ERROR);
                alert.setTitle("Error encountered!");
                alert.setContentText(exception.getMessage());
                alert.showAndWait();
            }
        }
    }

    @FXML
    private ObservableList<IStatement> getAllStatements() {
        List<IStatement> allStatements = new ArrayList<>();

        IStatement ex1 = new CompoundStatement(new VariableDeclarationStatement("v", new IntType()),
                new CompoundStatement(new AssignStatement("v", new ValueExpression(new IntValue(2))),
                        new PrintStatement(new VariableExpression("v"))));
        allStatements.add(ex1);

        IStatement sumProc = new CompoundStatement(
                new VariableDeclarationStatement("v", new IntType()),
                new CompoundStatement(
                        new AssignStatement("v", new ArithmeticExpression('+', new VariableExpression("a"), new VariableExpression("b"))),
                        new PrintStatement(new VariableExpression("v"))
                )
        );

        List<String> varSum = new ArrayList<>();
        varSum.add("a");
        varSum.add("b");
        procTable.put("sum", new Pair<>(varSum, sumProc));

        IStatement prodProc = new CompoundStatement(
                new VariableDeclarationStatement("v" , new IntType()),
                new CompoundStatement(
                        new AssignStatement("v", new ArithmeticExpression('*', new VariableExpression("a"), new VariableExpression("b"))),
                        new PrintStatement(new VariableExpression("v"))
                )
        );

        List<String> varProd = new ArrayList<>();
        varProd.add("a");
        varProd.add("b");
        procTable.put("product", new Pair<>(varProd, prodProc));

        IStatement ex2 = new CompoundStatement(
                new VariableDeclarationStatement("v", new IntType()),
                new CompoundStatement(
                        new VariableDeclarationStatement("w", new IntType()),
                        new CompoundStatement(
                                new AssignStatement("v", new ValueExpression(new IntValue(2))),
                                new CompoundStatement(
                                        new AssignStatement("w", new ValueExpression(new IntValue(5))),
                                        new CompoundStatement(
                                                new CallProcStatement("sum", new ArrayList<>(Arrays.asList(new ArithmeticExpression('*', new VariableExpression("v"), new ValueExpression(new IntValue(10))), new VariableExpression("w")))),
                                                new CompoundStatement(
                                                        new PrintStatement(new VariableExpression("v")),
                                                        new ForkStatement(
                                                                new CompoundStatement(
                                                                        new CallProcStatement("product", new ArrayList<>(Arrays.asList(new VariableExpression("v"), new VariableExpression("w")))),
                                                                        new ForkStatement(
                                                                                new CallProcStatement("sum", new ArrayList<>(Arrays.asList(new VariableExpression("v"), new VariableExpression("w"))))
                                                                        )
                                                                )
                                                        )
                                                )
                                        )
                                )
                        )
                )
        );
        allStatements.add(ex2);
        return FXCollections.observableArrayList(allStatements);
    }
}
