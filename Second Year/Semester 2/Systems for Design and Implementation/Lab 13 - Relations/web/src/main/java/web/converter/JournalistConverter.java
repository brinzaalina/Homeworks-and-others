package web.converter;

import core.domain.JournalistEntity;
import org.springframework.stereotype.Component;
import web.dto.JournalistDTO;

@Component
public class JournalistConverter extends BaseConverter<Long, JournalistEntity, JournalistDTO> {
    @Override
    public JournalistEntity convertDtoToModel(JournalistDTO dto) {
        var model = new JournalistEntity();
        model.setId(dto.getId());
        model.setLastName(dto.getLastName());
        model.setFirstName(dto.getFirstName());
        model.setEmail(dto.getEmail());
        model.setDob(dto.getDob());
        return model;
    }

    @Override
    public JournalistDTO convertModelToDto(JournalistEntity userEntity) {
        var userDTO = new JournalistDTO(userEntity.getLastName(), userEntity.getFirstName(), userEntity.getEmail(), userEntity.getDob());
        userDTO.setId(userEntity.getId());
        return userDTO;
    }
}
