package web.dto;

import lombok.*;

@NoArgsConstructor
@AllArgsConstructor
@Data
@EqualsAndHashCode
@ToString(callSuper = true)
public class ArticleJournalistPrimaryKeyDTO {
    Long articleId, journalistId;
}
