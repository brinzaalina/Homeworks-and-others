package core.domain;
import lombok.*;
import org.springframework.stereotype.Component;

import javax.persistence.*;
import java.io.Reader;

@Embeddable
@NoArgsConstructor
@Getter
@Setter
@AllArgsConstructor
@ToString
@Builder
public class ContactEntity  {
    String email;
    String phone;
    String address;
}
