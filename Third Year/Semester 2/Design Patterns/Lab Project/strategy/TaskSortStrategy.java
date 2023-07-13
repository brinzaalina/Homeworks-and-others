package strategy;

import domain.Task;

import java.util.List;

public interface TaskSortStrategy {
    List<Task> sort(List<Task> tasks);
}
