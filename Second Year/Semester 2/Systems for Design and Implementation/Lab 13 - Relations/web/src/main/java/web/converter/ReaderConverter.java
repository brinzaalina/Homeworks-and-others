package web.converter;

import core.domain.ContactEntity;
import core.domain.ReaderEntity;
import org.springframework.stereotype.Component;
import web.dto.ContactDTO;
import web.dto.ReaderDTO;

@Component
public class ReaderConverter extends BaseConverter<Long, ReaderEntity, ReaderDTO>{
    @Override
    public ReaderEntity convertDtoToModel(ReaderDTO dto) {
        var model = new ReaderEntity();
        var contact = ContactEntity.builder()
                        .email(dto.getContact().getEmail())
                .phone(dto.getContact().getPhone())
                .address(dto.getContact().getAddress())
                                .build();
        model.setId(dto.getId());
        model.setLast_name(dto.getLastName());
        model.setFirst_name(dto.getFirstName());
        model.setContact(contact);
        return model;
    }

    @Override
    public ReaderDTO convertModelToDto(ReaderEntity readerEntity) {
        var userDTO = new ReaderDTO(readerEntity.getLast_name(), readerEntity.getFirst_name(), new ContactDTO(readerEntity.getContact().getEmail(), readerEntity.getContact().getPhone(), readerEntity.getContact().getAddress()));
        userDTO.setId(readerEntity.getId());
        return userDTO;
    }
}
