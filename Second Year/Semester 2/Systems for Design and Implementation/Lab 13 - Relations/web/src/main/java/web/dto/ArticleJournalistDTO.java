package web.dto;

import core.domain.ArticleJournalistPrimaryKey;
import lombok.*;
import org.apache.commons.lang3.tuple.Pair;

import java.io.Serializable;

@NoArgsConstructor
@AllArgsConstructor
@Data
@Builder
@EqualsAndHashCode
@ToString(callSuper = true)
public class ArticleJournalistDTO implements Serializable {
    ArticleDTO article;
    JournalistDTO journalist;
}
