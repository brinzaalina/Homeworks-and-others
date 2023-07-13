package view.command;

import exceptions.ToDoException;
import service.Service;
import strategy.AlphabeticalSortStrategy;
import strategy.DueDateSortStrategy;

import java.util.Scanner;

public class GetTasksCommand extends Command{
    private final Service service;

    public GetTasksCommand(Service service, String key) {
        super(key, "Get all tasks");
        this.service = service;
    }

    @Override
    public void execute() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Sort type - 1) alphabetical, 2) by due date, 3) none ");
        String sortTypeString = scanner.nextLine();
        switch (sortTypeString) {
            case "1" -> {
                service.setTaskSortStrategy(new AlphabeticalSortStrategy());
                service.getTasks().forEach(System.out::println);
            }
            case "2" -> {
                service.setTaskSortStrategy(new DueDateSortStrategy());
                service.getTasks().forEach(System.out::println);
            }
            case "3" -> service.getUnsortedTasks().forEach(System.out::println);
            default -> System.out.println("Invalid sort type");
        }
    }
}
