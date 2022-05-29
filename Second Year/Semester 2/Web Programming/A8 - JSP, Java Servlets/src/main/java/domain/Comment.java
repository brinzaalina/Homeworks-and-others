package domain;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.Setter;
import lombok.ToString;

@Getter
@Setter
@AllArgsConstructor
@ToString
public class Comment {
    private Integer id;
    private Integer userId;
    private String content;
    private Integer topicId;
}
