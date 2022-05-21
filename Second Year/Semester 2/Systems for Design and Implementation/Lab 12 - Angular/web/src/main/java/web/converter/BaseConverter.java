package web.converter;

import core.domain.BaseEntity;
import web.dto.BaseDTO;

import java.io.Serializable;
import java.util.Collection;
import java.util.List;
import java.util.Set;
import java.util.stream.Collectors;

public abstract class BaseConverter<ID extends Serializable, Model extends BaseEntity<ID>, DTO extends BaseDTO<ID>> implements Converter<ID, Model, DTO> {
    public List<ID> convertModelsToIDs(Collection<Model> models) {
        return models.stream().map(BaseEntity::getId).collect(Collectors.toList());
    }

    public List<ID> convertDTOsToIDs(Collection<DTO> dtos) {
        return dtos.stream().map(BaseDTO::getId).collect(Collectors.toList());
    }

    public List<DTO> convertModelsToDTOs(Collection<Model> models) {
        return models.stream().map(this::convertModelToDto).collect(Collectors.toList());
    }
}
