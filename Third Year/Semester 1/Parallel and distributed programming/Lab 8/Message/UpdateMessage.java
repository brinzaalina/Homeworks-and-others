package Message;

import java.io.Serializable;

public class UpdateMessage extends BaseMessage implements Serializable {
    public String variable;
    public int value;

    public UpdateMessage(String variable, int value) {
        this.variable = variable;
        this.value = value;
    }
}
