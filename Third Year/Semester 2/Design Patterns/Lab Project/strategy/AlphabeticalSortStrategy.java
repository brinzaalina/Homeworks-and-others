package strategy;

import domain.Task;

import java.util.Comparator;
import java.util.List;

public class AlphabeticalSortStrategy implements TaskSortStrategy{
    @Override
    public List<Task> sort(List<Task> tasks) {
        tasks.sort(Comparator.comparing(Task::getTitle));
        return tasks;
    }
}
