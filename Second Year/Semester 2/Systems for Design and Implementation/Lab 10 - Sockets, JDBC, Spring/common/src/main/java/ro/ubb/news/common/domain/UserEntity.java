package ro.ubb.news.common.domain;


import lombok.*;

import java.util.Date;

@Getter
@Setter
@NoArgsConstructor
@RequiredArgsConstructor
@ToString
public class UserEntity extends BaseEntity<Long> {
    @NonNull
    private String lastName;

    @NonNull
    private String firstName;

    @NonNull
    private String email;

    private Date dob;
}
