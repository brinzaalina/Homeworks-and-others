package domain;

import java.time.LocalDateTime;

public class Reminder implements TaskObserver{
    private Task task;

    public Reminder(Task task) {
        this.task = task;
        task.addObserver(this);
    }

    @Override
    public void update(Task task) {
        if (task == this.task && !task.isDone() && task.getDueDate().isAfter(LocalDateTime.now())) {
            sendNotification("Reminder: Task " + task.getTitle() + " is due!");
        }
    }

    private void sendNotification(String message) {
        System.out.println(message);
    }
}
