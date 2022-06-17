package web.dto;

import lombok.*;

@NoArgsConstructor
@AllArgsConstructor
@Getter
@Setter
@ToString
public class ContactDTO {
    String email;
    String phone;
    String address;
}
