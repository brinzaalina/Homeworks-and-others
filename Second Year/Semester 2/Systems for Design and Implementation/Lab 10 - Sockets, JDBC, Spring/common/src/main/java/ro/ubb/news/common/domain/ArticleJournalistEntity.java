package ro.ubb.news.common.domain;

import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;
import lombok.ToString;
import org.apache.commons.lang3.tuple.Pair;

@Setter
@Getter
@NoArgsConstructor
@ToString
public class ArticleJournalistEntity extends BaseEntity<Pair<Long, Long>>{
    public ArticleJournalistEntity(Pair<Long, Long> longLongPair) {
        super(longLongPair);
    }
}
