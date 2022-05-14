package web.converter;

import core.domain.ArticleJournalistEntity;
import core.domain.ArticleJournalistPrimaryKey;
import org.springframework.stereotype.Component;
import web.dto.ArticleJournalistDTO;

@Component
public class ArticleJournalistConverter extends BaseConverter<ArticleJournalistPrimaryKey, ArticleJournalistEntity, ArticleJournalistDTO> {
    @Override
    public ArticleJournalistEntity convertDtoToModel(ArticleJournalistDTO dto) {
        var model = new ArticleJournalistEntity();
        model.setId(dto.getId());
        return model;
    }

    @Override
    public ArticleJournalistDTO convertModelToDto(ArticleJournalistEntity articleJournalistEntity) {
        var articleJournalistDTO = new ArticleJournalistDTO();
        articleJournalistDTO.setId(articleJournalistEntity.getId());
        return articleJournalistDTO;
    }
}
