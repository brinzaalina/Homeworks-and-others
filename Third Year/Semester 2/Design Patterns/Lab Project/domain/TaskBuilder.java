package domain;

import java.time.LocalDateTime;

public class TaskBuilder {
    private String title;
    private String description;
    private LocalDateTime dueDate;
    private boolean isDone;

    // builder design pattern
    public TaskBuilder setTitle(String title) {
        this.title = title;
        return this;
    }

    public TaskBuilder setDescription(String desc) {
        this.description = desc;
        return this;
    }

    public TaskBuilder setDueDate(LocalDateTime dueDate) {
        this.dueDate = dueDate;
        return this;
    }

    public TaskBuilder setDone(boolean done) {
        this.isDone = done;
        return this;
    }

    public Task build() {
        Task task = new Task();
        task.setTitle(title);
        task.setDescription(description);
        task.setDueDate(dueDate);
        task.setDone(isDone);
        return task;
    }
}
