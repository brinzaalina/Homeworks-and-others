package view.command;

import service.Service;

import java.util.Scanner;

public class RemoveTaskCommand extends Command{
    private final Service service;

    public RemoveTaskCommand(Service service,String key) {
        super(key, "Remove a task from the list");
        this.service = service;
    }

    @Override
    public void execute() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Task title: ");
        String title = scanner.nextLine();
        try {
            service.removeTask(title);
        } catch (Exception e) {
            System.out.println("Failed to remove task: " + e.getMessage());
        }
    }
}
