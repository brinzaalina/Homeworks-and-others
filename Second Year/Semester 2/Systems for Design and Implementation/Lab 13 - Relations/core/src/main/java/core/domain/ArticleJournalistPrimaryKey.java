package core.domain;

import lombok.*;

import javax.persistence.Embeddable;
import java.io.Serializable;

@NoArgsConstructor
@AllArgsConstructor
@Getter
@Setter
@ToString
@EqualsAndHashCode
public class ArticleJournalistPrimaryKey implements Serializable {
    private ArticleEntity article;
    private JournalistEntity journalist;
}
