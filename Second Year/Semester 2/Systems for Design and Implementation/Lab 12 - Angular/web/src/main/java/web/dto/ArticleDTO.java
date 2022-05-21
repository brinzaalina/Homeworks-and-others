package web.dto;

import lombok.*;

@NoArgsConstructor
@AllArgsConstructor
@Data
@EqualsAndHashCode(callSuper = true)
@ToString(callSuper = true)
public class ArticleDTO extends BaseDTO<Long>{
    private String title, text;
    private Long categoryId;
}
