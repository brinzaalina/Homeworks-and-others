package Message;

import java.io.Serializable;

public class SubscribeMessage extends BaseMessage implements Serializable {
    public String variable;
    public int rank;

    public SubscribeMessage(String variable, int rank) {
        this.variable = variable;
        this.rank = rank;
    }
}
