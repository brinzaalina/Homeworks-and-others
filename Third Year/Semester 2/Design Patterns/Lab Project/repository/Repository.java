package repository;

import domain.Task;
import exceptions.ToDoException;
import logger.Logger;

import java.util.ArrayList;
import java.util.List;

public class Repository {
    private List<Task> tasks;
    private final Logger logger = Logger.getInstance();

    public Repository() {
        this.tasks = new ArrayList<>();
    }

    public void addTask(Task task) throws ToDoException {
        for (Task t : tasks) {
            if (t.getTitle().equals(task.getTitle())) {
                throw new ToDoException("Task with the same title already exists");
            }
        }
        logger.log("Adding task: " + task.getTitle());
        tasks.add(task);
        logger.log("domain.Task added: " + task.getTitle());
    }

    public void removeTask(String title) throws ToDoException {
        boolean exists = false;
        for (Task task : tasks) {
            if (task.getTitle().equals(title)) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            throw new ToDoException("Task with the given title does not exist");
        }
        logger.log("Removing task: " + title);
        // remove task with the given title
        for (Task task : tasks) {
            if (task.getTitle().equals(title)) {
                tasks.remove(task);
                break;
            }
        }
        logger.log("domain.Task removed: " + title);
    }

    public void updateTask(Task task) throws ToDoException {
        // throw exception if task with the given title does not exist
        boolean exists = false;
        for (Task t : tasks) {
            if (t.getTitle().equals(task.getTitle())) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            throw new ToDoException("Task with the given title does not exist");
        }
        logger.log("Updating task: " + task.getTitle());
        for (Task t : tasks) {
            if (t.getTitle().equals(task.getTitle())) {
                t.setDescription(task.getDescription());
                t.setDueDate(task.getDueDate());
                t.setDone(task.isDone());
            }
        }
        logger.log("domain.Task updated: " + task.getTitle());
    }

    public List<Task> getTasks() {
        logger.log("Getting all tasks");
        return tasks;
    }

    public Task getTask(String title) throws ToDoException {
        logger.log("Getting task: " + title);
        for (Task task : tasks) {
            if (task.getTitle().equals(title)) {
                return task;
            }
        }
        throw new ToDoException("Task with the given title does not exist");
    }
}
