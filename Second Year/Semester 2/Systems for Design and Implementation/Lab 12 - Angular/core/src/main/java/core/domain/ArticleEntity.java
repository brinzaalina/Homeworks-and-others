package core.domain;

import lombok.*;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Table;

@Entity
@Table(name = "article")
@NoArgsConstructor
@AllArgsConstructor
@Data
@EqualsAndHashCode(callSuper = true)
@ToString(callSuper = true)
public class ArticleEntity extends BaseEntity<Long> {
    private String title;
    private String text;
    @Column(name = "category_id")
    private Long categoryId;
}
