package core.domain;

import lombok.*;

import javax.persistence.Entity;
import javax.persistence.Table;

@Entity
@Table(name = "category")
@NoArgsConstructor
@Getter
@Setter
@AllArgsConstructor
@Data
@EqualsAndHashCode(callSuper = true)
@ToString
public class CategoryEntity extends BaseEntity<Long>{
    private String name;
}
