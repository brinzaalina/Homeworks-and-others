package web.dto;

import lombok.*;

@NoArgsConstructor
@AllArgsConstructor
@Data
@EqualsAndHashCode(callSuper = true)
@ToString(callSuper = true)
public class ReaderDTO extends BaseDTO<Long>{
    private String lastName, firstName;
    private ContactDTO contact;
}
