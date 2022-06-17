package core.domain;

import lombok.*;

import javax.persistence.*;

@Entity
@Table(name = "reader")
@NoArgsConstructor
@Getter
@Setter
@AllArgsConstructor
@Builder
public class ReaderEntity extends BaseEntity<Long>{
    String first_name;
    String last_name;

    @Embedded
    ContactEntity contact;
}
