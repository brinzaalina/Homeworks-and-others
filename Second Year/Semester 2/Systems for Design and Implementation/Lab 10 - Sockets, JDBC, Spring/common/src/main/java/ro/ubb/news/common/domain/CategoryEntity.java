package ro.ubb.news.common.domain;

import lombok.*;

@Getter
@Setter
@NoArgsConstructor
@RequiredArgsConstructor
@ToString
public class CategoryEntity extends BaseEntity<Long>{
    @NonNull
    private String name;
}
