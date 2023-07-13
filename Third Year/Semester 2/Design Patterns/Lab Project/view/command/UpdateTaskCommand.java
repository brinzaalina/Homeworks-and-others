package view.command;

import exceptions.ToDoException;
import service.Service;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;
import java.util.Scanner;

public class UpdateTaskCommand extends Command{
    private final Service service;

    public UpdateTaskCommand(Service service, String key) {
        super(key, "Update a task from the list");
        this.service = service;
    }

    @Override
    public void execute() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Task title: ");
        String title = scanner.nextLine();
        System.out.println("Description: ");
        String description = scanner.nextLine();
        if (description.isBlank()) {
            System.out.println("Description cannot be blank");
            return;
        }
        System.out.println("Due Date(yyyy-MM-dd hh:mm): ");
        String dueDateString = scanner.nextLine();
        if (dueDateString.isBlank()) {
            System.out.println("Due date cannot be blank");
            return;
        }
        System.out.println("Done(y/n): ");
        String doneString = scanner.nextLine();
        if (doneString.isBlank()) {
            System.out.println("Done cannot be blank");
            return;
        }
        try {
            boolean done = doneString.equals("y");
            DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd H:mm");
            LocalDateTime dueDate = LocalDateTime.parse(dueDateString, formatter);
            service.updateTask(title, description, dueDate, done);
        } catch (DateTimeParseException e) {
            System.out.println("Failed to parse date: " + e.getMessage());
        } catch (ToDoException e) {
            System.out.println("Failed to update task: " + e.getMessage());
        }
    }
}
