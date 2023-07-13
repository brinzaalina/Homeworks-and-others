import Message.BaseMessage;
import Message.CloseMessage;
import Message.SubscribeMessage;
import Message.UpdateMessage;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
import mpi.MPI;

public class DSM {
    private Map<String, Set<Integer>> subscribers;
    private static final Lock lock = new ReentrantLock();
    private Map<String, Integer> variables;

    public DSM() {
        this.variables = new HashMap<>();
        this.variables.put("first", 0);
        this.variables.put("second", 1);
        this.variables.put("third", 2);
        this.subscribers = new HashMap<>();
        this.subscribers.put("first", new HashSet<>());
        this.subscribers.put("second", new HashSet<>());
        this.subscribers.put("third", new HashSet<>());
    }

    public void setVariable(String variable, int value) {
        this.variables.put(variable, value);
    }

    public void updateVariable(String variable, int value) {
        lock.lock();
        this.setVariable(variable, value);
        this.sendMessageToSubscribers(variable, new UpdateMessage(variable, value));
        lock.unlock();
    }

    public void checkAndReplace(String variable, int oldValue, int newValue) {
        lock.lock();
        if (this.variables.get(variable).equals(oldValue)) {
            lock.unlock();
            this.updateVariable(variable, newValue);
        } else {
            lock.unlock();
        }
    }

    public void subscribeTo(String variable) {
        Set<Integer> subscribers = this.subscribers.get(variable);
        subscribers.add(MPI.COMM_WORLD.Rank());
        this.subscribers.put(variable, subscribers);
        this.sendMessageToAll(new SubscribeMessage(variable, MPI.COMM_WORLD.Rank()));
    }

    public void syncSubscription(String variable, int rank) {
        Set<Integer> subscribers = this.subscribers.get(variable);
        subscribers.add(rank);
        this.subscribers.put(variable, subscribers);
    }

    public void sendMessageToSubscribers(String variable, BaseMessage message) {
        for (int i = 0; i < MPI.COMM_WORLD.Size(); i++) {
            if (MPI.COMM_WORLD.Rank() == i || !subscribers.get(variable).contains(i)) {
                continue;
            }
            MPI.COMM_WORLD.Send(new Object[]{message}, 0, 1, MPI.OBJECT, i, 0);
        }
    }

    public void sendMessageToAll(BaseMessage message) {
        for (int i = 0; i < MPI.COMM_WORLD.Size(); i++) {
            if (MPI.COMM_WORLD.Rank() == i || !(message instanceof CloseMessage)) {
                continue;
            }
            MPI.COMM_WORLD.Send(new Object[]{message}, 0, 1, MPI.OBJECT, i, 0);
        }
    }

    public void close() {
        this.sendMessageToAll(new CloseMessage());
    }

    @Override
    public String toString() {
        return "DSM:\n" +
                "subscribers = " + subscribers + "\n" +
                "variables = " + variables + "\n";
    }
}
