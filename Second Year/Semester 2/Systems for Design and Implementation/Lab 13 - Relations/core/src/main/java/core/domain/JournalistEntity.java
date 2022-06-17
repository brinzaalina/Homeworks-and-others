package core.domain;

import com.fasterxml.jackson.annotation.JsonIgnore;
import lombok.*;

import javax.persistence.*;
import java.util.Collections;
import java.util.Date;
import java.util.HashSet;
import java.util.Set;
import java.util.stream.Collectors;

@Entity
@Table(name = "journalist")
@NoArgsConstructor
@Getter
@Setter
@RequiredArgsConstructor
@AllArgsConstructor
@EqualsAndHashCode(callSuper = true)
@ToString(callSuper = true, exclude = {"articleJournalists"})
@Builder
public class JournalistEntity extends BaseEntity<Long> {
    @Column(name = "last_name")
    @NonNull
    private String lastName;

    @Column(name = "first_name")
    @NonNull
    private String firstName;

    @NonNull
    private String email;
    private Date dob;

    @OneToMany(mappedBy = "journalist", cascade = CascadeType.ALL, fetch = FetchType.EAGER)
    @JsonIgnore
    Set<ArticleJournalistEntity> articleJournalists = new HashSet<>();

    public Set<ArticleEntity> getArticles() {
        return articleJournalists.stream()
                .map(ArticleJournalistEntity::getArticle).collect(Collectors.toUnmodifiableSet());
    }

    public void addArticle(ArticleJournalistEntity articleJournalist) {
        articleJournalists.add(articleJournalist);
    }

    public void removeArticleJournalist(Long articleId) {
        ArticleJournalistEntity articleJournalist = this.articleJournalists.stream()
                .filter(aj -> aj.getArticle().getId().equals(articleId))
                .collect(Collectors.toList())
                .get(0);
        this.articleJournalists.remove(articleJournalist);
    }
}
