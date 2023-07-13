package view.command;

import service.Service;

import java.util.Scanner;

public class AddTaskReminderCommand extends Command {
    private final Service service;

    public AddTaskReminderCommand(Service service, String key) {
        super(key, "Add a new task reminder to the list");
        this.service = service;
    }

    @Override
    public void execute() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Title: ");
        String title = scanner.nextLine();
        try {
            service.addTaskReminder(title);
        } catch (Exception e) {
            System.out.println("Failed to add task reminder: " + e.getMessage());
        }
    }
}
