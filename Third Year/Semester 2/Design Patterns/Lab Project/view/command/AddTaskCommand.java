package view.command;

import exceptions.ToDoException;
import service.Service;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;
import java.util.Scanner;

public class AddTaskCommand extends Command{
    private final Service service;

    public AddTaskCommand(Service service, String key) {
        super(key, "Add a new task to the list");
        this.service = service;
    }

    @Override
    public void execute() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Title: ");
        String title = scanner.nextLine();
        if (title.isBlank()) {
            System.out.println("Title cannot be blank");
            return;
        }
        System.out.println("Description: ");
        String description = scanner.nextLine();
        if (description.isBlank()) {
            System.out.println("Description cannot be blank");
            return;
        }
        System.out.println("Due Date(yyyy-MM-dd H:mm): ");
        String dueDateString = scanner.nextLine();
        if (dueDateString.isBlank()) {
            System.out.println("Due date cannot be blank");
            return;
        }
        try {
            DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd H:mm");
            LocalDateTime dueDate = LocalDateTime.parse(dueDateString, formatter);
            service.addTask(title, description, dueDate);
        } catch (DateTimeParseException e) {
            System.out.println("Failed to parse due date: " + e.getMessage());
        } catch (ToDoException e) {
            System.out.println("Failed to add task: " + e.getMessage());
        }
    }
}
