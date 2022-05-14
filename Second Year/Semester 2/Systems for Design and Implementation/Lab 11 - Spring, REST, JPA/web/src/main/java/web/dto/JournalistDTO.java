package web.dto;

import lombok.*;

import java.util.Date;

@NoArgsConstructor
@AllArgsConstructor
@Data
@EqualsAndHashCode(callSuper = true)
@ToString(callSuper = true)
public class JournalistDTO extends BaseDTO<Long>{
    private String lastName, firstName, email;
    private Date dob;
}

