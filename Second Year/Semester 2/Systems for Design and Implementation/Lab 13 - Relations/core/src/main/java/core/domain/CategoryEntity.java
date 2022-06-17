package core.domain;

import com.fasterxml.jackson.annotation.JsonIgnore;
import lombok.*;

import javax.persistence.Entity;
import javax.persistence.OneToMany;
import javax.persistence.Table;
import java.util.HashSet;
import java.util.Set;

@Entity
@Table(name = "category")
@NoArgsConstructor
@Getter
@Setter
@AllArgsConstructor
@ToString(callSuper = true)
@Builder
public class CategoryEntity extends BaseEntity<Long>{
    private String name;

    @OneToMany(mappedBy = "category")
    @JsonIgnore
    @ToString.Exclude
    Set<ArticleEntity> articles = new HashSet<>();

    public void addArticle(ArticleEntity article) {
        articles.add(article);
    }
}
