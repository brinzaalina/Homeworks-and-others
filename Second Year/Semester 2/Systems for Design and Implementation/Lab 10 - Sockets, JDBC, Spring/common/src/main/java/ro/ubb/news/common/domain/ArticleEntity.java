package ro.ubb.news.common.domain;

import lombok.*;

@Getter
@Setter
@NoArgsConstructor
@AllArgsConstructor
@ToString
public class ArticleEntity extends BaseEntity<Long>{
    private String title;
    private String text;
    private Long categoryId;
}
