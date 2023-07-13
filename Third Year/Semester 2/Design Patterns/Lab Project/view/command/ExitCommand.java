package view.command;

public class ExitCommand extends Command {
    public ExitCommand(String key) {
        super(key, "Exit the program");
    }

    @Override
    public void execute() {
        System.out.println("Exiting...");
        System.exit(0);
    }
}
