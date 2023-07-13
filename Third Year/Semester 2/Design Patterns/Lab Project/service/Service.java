package service;

import domain.Reminder;
import domain.Task;
import domain.TaskBuilder;
import exceptions.ToDoException;
import logger.Logger;
import repository.Repository;
import strategy.AlphabeticalSortStrategy;
import strategy.TaskSortStrategy;

import java.time.LocalDateTime;
import java.util.List;

public class Service {
    private Repository repository;
    private final Logger logger = Logger.getInstance();
    private TaskSortStrategy taskSortStrategy;

    public Service(Repository repository) {
        this.repository = repository;
        this.taskSortStrategy = new AlphabeticalSortStrategy();
    }

    public void setTaskSortStrategy(TaskSortStrategy taskSortStrategy) {
        this.taskSortStrategy = taskSortStrategy;
    }

    public void addTask(String title, String description, LocalDateTime dueDate) throws ToDoException {
        Task task = new TaskBuilder()
                .setTitle(title)
                .setDescription(description)
                .setDueDate(dueDate)
                .setDone(false)
                .build();
        logger.log("Adding task: " + task.getTitle());
        repository.addTask(task);
        logger.log("domain.Task added: " + task.getTitle());
    }

    public void removeTask(String title) throws ToDoException {
        logger.log("Removing task: " + title);
        repository.removeTask(title);
        logger.log("domain.Task removed: " + title);
    }

    public void updateTask(String title, String description, LocalDateTime dueDate, boolean isDone) throws ToDoException {
        Task task = new TaskBuilder()
                .setTitle(title)
                .setDescription(description)
                .setDueDate(dueDate)
                .setDone(isDone)
                .build();
        logger.log("Updating task: " + task.getTitle());
        repository.updateTask(task);
        logger.log("domain.Task updated: " + task.getTitle());
    }

    public List<Task> getTasks() {
        logger.log("Getting sorted tasks");
        List<Task> tasks = repository.getTasks();
        tasks = taskSortStrategy.sort(tasks);
        logger.log("Returning sorted tasks");
        return tasks;
    }

    public List<Task> getUnsortedTasks() {
        logger.log("Getting unsorted tasks");
        List<Task> tasks = repository.getTasks();
        logger.log("Returning unsorted tasks");
        return tasks;
    }

    public void addTaskReminder(String title) throws ToDoException {
        logger.log("Adding reminder to task: " + title);
        Task task = repository.getTask(title);
        Reminder reminder = new Reminder(task);
        logger.log("Reminder added to task: " + title);
    }
}
