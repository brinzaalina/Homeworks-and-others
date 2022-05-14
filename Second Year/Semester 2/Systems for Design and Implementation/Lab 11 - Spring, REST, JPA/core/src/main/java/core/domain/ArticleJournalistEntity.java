package core.domain;

import lombok.Data;
import lombok.EqualsAndHashCode;
import lombok.NoArgsConstructor;
import lombok.ToString;
import org.apache.commons.lang3.tuple.Pair;

import javax.persistence.*;

@Entity
@Table(name = "article_journalist")
@NoArgsConstructor
@Data
@EqualsAndHashCode(callSuper = true)
@ToString
public class ArticleJournalistEntity extends BaseEntity<ArticleJournalistPrimaryKey> {

    public ArticleJournalistEntity(ArticleJournalistPrimaryKey id) {
        this.setId(id);
    }
}
