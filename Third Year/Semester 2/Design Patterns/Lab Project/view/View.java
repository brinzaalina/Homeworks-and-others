package view;

import service.Service;
import view.command.*;

import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class View {
    private Map<String, Command> commands = new HashMap<>();
    private Service service;

    public View(Service service) {
        this.service = service;
        this.createCommandList();
    }

    private void addCommand(Command command) {
        commands.put(command.getKey(), command);
    }

    private void createCommandList() {
        this.addCommand(new ExitCommand("0"));
        this.addCommand(new AddTaskCommand(service, "1"));
        this.addCommand(new RemoveTaskCommand(service, "2"));
        this.addCommand(new UpdateTaskCommand(service, "3"));
        this.addCommand(new GetTasksCommand(service, "4"));
        this.addCommand(new AddTaskReminderCommand(service, "5"));
    }

    private void printMenu() {
        System.out.println("Menu:");
        commands.forEach((key, value) -> System.out.println(value.getKey() + " - " + value.getDescription()));
    }

    public void run() {
        Scanner scanner = new Scanner(System.in);
        while (true) {
            this.printMenu();
            System.out.println("Input the option: ");
            String key = scanner.nextLine();
            Command command = commands.get(key);
            if (command != null) {
                command.execute();
            } else {
                System.out.println("Invalid option");
            }
        }
    }
}
