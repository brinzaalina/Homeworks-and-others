package view.command;

public abstract class Command {
    private String key;
    private String description;

    public Command(String name, String description) {
        this.key = name;
        this.description = description;
    }

    public abstract void execute();

    public String getKey() {
        return key;
    }

    public String getDescription() {
        return description;
    }
}
