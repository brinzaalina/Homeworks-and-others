package web.dto;

import core.domain.ArticleJournalistPrimaryKey;
import lombok.*;
import org.apache.commons.lang3.tuple.Pair;

@AllArgsConstructor
@Data
@EqualsAndHashCode(callSuper = true)
@ToString(callSuper = true)
public class ArticleJournalistDTO extends BaseDTO<ArticleJournalistPrimaryKey> {
}
