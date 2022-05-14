package web.converter;

import core.domain.CategoryEntity;
import org.springframework.stereotype.Component;
import web.dto.CategoryDTO;

@Component
public class CategoryConverter extends BaseConverter<Long, CategoryEntity, CategoryDTO> {
    @Override
    public CategoryEntity convertDtoToModel(CategoryDTO dto) {
        var model = new CategoryEntity();
        model.setId(dto.getId());
        model.setName(dto.getName());
        return model;
    }

    @Override
    public CategoryDTO convertModelToDto(CategoryEntity categoryEntity) {
        var categoryDTO = new CategoryDTO(categoryEntity.getName());
        categoryDTO.setId(categoryEntity.getId());
        return categoryDTO;
    }
}
