package domain;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;
import java.util.UUID;

public class Task {
    private String title;
    private String description;
    private LocalDateTime dueDate;
    private boolean isDone;
    private List<TaskObserver> observers = new ArrayList<>();

    public Task() {
    }

    public String getTitle() {
        return title;
    }

    public String getDescription() {
        return description;
    }

    public LocalDateTime getDueDate() {
        return dueDate;
    }

    public boolean isDone() {
        return isDone;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public void setDescription(String desc) {
        this.description = desc;
    }

    public void setDueDate(LocalDateTime dueDate) {
        this.dueDate = dueDate;
        notifyObservers();
    }

    public void setDone(boolean done) {
        this.isDone = done;
        notifyObservers();
    }

    public void addObserver(TaskObserver observer) {
        observers.add(observer);
    }

    public void removeObserver(TaskObserver observer) {
        observers.remove(observer);
    }

    public void notifyObservers() {
        for (TaskObserver observer : observers) {
            observer.update(this);
        }
    }

    @Override
    public String toString() {
        return "domain.Task{" + "title=" + title + ", description=" + description + ", dueDate=" + dueDate + ", isDone=" + isDone + '}';
    }
}
