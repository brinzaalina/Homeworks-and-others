package ro.ubb.news.common.domain;

import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;
import lombok.ToString;

@Getter
@Setter
@NoArgsConstructor
@ToString
public class JournalistEntity extends BaseEntity<Long>{
    public JournalistEntity(Long userId) {
        super(userId);
    }
}
