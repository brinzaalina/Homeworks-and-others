package web.converter;

import core.domain.ArticleEntity;
import org.springframework.stereotype.Component;
import web.dto.ArticleDTO;

@Component
public class ArticleConverter extends BaseConverter<Long, ArticleEntity, ArticleDTO> {
    @Override
    public ArticleEntity convertDtoToModel(ArticleDTO dto) {
        var model = new ArticleEntity();
        model.setId(dto.getId());
        model.setTitle(dto.getTitle());
        model.setText(dto.getText());
        model.setCategoryId(dto.getCategoryId());
        return model;
    }

    @Override
    public ArticleDTO convertModelToDto(ArticleEntity articleEntity) {
        var articleDTO = new ArticleDTO(articleEntity.getTitle(), articleEntity.getText(), articleEntity.getCategoryId());
        articleDTO.setId(articleEntity.getId());
        return articleDTO;
    }
}
