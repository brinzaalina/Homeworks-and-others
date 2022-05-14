package core.domain;

import lombok.*;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Table;
import java.util.Date;

@Entity
@Table(name = "journalist")
@NoArgsConstructor
@Getter
@Setter
@RequiredArgsConstructor
@AllArgsConstructor
@Data
@EqualsAndHashCode(callSuper = true)
@ToString
public class JournalistEntity extends BaseEntity<Long> {
    @Column(name = "last_name")
    @NonNull
    private String lastName;

    @Column(name = "first_name")
    @NonNull
    private String firstName;

    @NonNull
    private String email;
    private Date dob;
}
