package core.domain;

import com.fasterxml.jackson.annotation.JsonIgnore;
import lombok.*;

import javax.persistence.*;
import java.util.Collection;
import java.util.Collections;
import java.util.HashSet;
import java.util.Set;
import java.util.stream.Collectors;

@Entity
@Getter
@Setter
@Table(name = "article")
@NoArgsConstructor
@AllArgsConstructor
@EqualsAndHashCode(callSuper = true)
@Builder
@ToString(callSuper = true, exclude = {"articleJournalists"})
public class ArticleEntity extends BaseEntity<Long> {
    private String title;
    private String text;
//    @Column(name = "category_id")
//    private Long categoryId;
    @ManyToOne()
    @JsonIgnore
    @JoinColumn(name = "category_id", foreignKey = @ForeignKey(name = "article_category", value = ConstraintMode.PROVIDER_DEFAULT))
    CategoryEntity category;

    @OneToMany(mappedBy = "article", cascade = CascadeType.ALL, fetch = FetchType.EAGER)
    @JsonIgnore
    private Set<ArticleJournalistEntity> articleJournalists = new HashSet<>();

    public Set<JournalistEntity> getJournalists() {
        return articleJournalists.stream()
                .map(ArticleJournalistEntity::getJournalist).collect(Collectors.toUnmodifiableSet());
    }

    public void addJournalist(ArticleJournalistEntity articleJournalist) {
        articleJournalists.add(articleJournalist);
    }

    public void removeArticleJournalist(Long journalistId) {
        ArticleJournalistEntity articleJournalist = this.articleJournalists.stream()
                .filter(aj -> aj.getJournalist().getId().equals(journalistId))
                .collect(Collectors.toList())
                .get(0);
        this.articleJournalists.remove(articleJournalist);
    }
}
