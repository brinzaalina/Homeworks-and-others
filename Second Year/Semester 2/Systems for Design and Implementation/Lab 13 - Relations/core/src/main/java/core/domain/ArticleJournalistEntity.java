package core.domain;

import com.fasterxml.jackson.annotation.JsonIgnore;
import lombok.*;
import org.apache.commons.lang3.tuple.Pair;

import javax.persistence.*;
import java.io.Serializable;
import java.util.Objects;

@Entity
@Getter
@Setter
@IdClass(ArticleJournalistPrimaryKey.class)
@Table(name = "article_journalist")
@NoArgsConstructor
@AllArgsConstructor
@Builder
public class ArticleJournalistEntity implements Serializable {
    @Id
    @ManyToOne(optional = false, fetch = FetchType.EAGER, cascade = CascadeType.ALL)
    @JsonIgnore
    @JoinColumn(name = "journalistid", referencedColumnName = "id", foreignKey = @ForeignKey(name = "article_journalist_journalist", value = ConstraintMode.PROVIDER_DEFAULT))
    private JournalistEntity journalist;

    @Id
    @ManyToOne(optional = false, fetch = FetchType.EAGER, cascade = CascadeType.ALL)
    @JsonIgnore
    @JoinColumn(name = "articleid", referencedColumnName = "id", foreignKey = @ForeignKey(name = "article_journalist_article", value = ConstraintMode.PROVIDER_DEFAULT))
    private ArticleEntity article;

    @Override
    public boolean equals(Object o) {
        return o instanceof ArticleJournalistEntity && getJournalist().equals(((ArticleJournalistEntity) o).getJournalist()) && getArticle().equals(((ArticleJournalistEntity) o).getArticle());
    }

    @Override
    public String toString() {
        return "ArticleJournalistEntity{" +
                "journalist=" + journalist +
                ", article=" + article +
                '}';
    }
}
