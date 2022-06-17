package web.converter;

import core.domain.ArticleJournalistEntity;
import core.domain.ArticleJournalistPrimaryKey;
import org.springframework.stereotype.Component;
import web.dto.ArticleJournalistDTO;

import java.util.Collection;
import java.util.List;
import java.util.stream.Collectors;

@Component
public class ArticleJournalistConverter{
    ArticleConverter articleConverter;
    JournalistConverter journalistConverter;

    public ArticleJournalistConverter(ArticleConverter articleConverter, JournalistConverter journalistConverter) {
        this.articleConverter = articleConverter;
        this.journalistConverter = journalistConverter;
    }

    public ArticleJournalistEntity convertDtoToModel(ArticleJournalistDTO dto) {
        return ArticleJournalistEntity.builder()
                .article(this.articleConverter.convertDtoToModel(dto.getArticle()))
                .journalist(this.journalistConverter.convertDtoToModel(dto.getJournalist()))
                .build();
    }

    public ArticleJournalistDTO convertModelToDto(ArticleJournalistEntity articleJournalistEntity) {
        return ArticleJournalistDTO.builder()
                .article(this.articleConverter.convertModelToDto(articleJournalistEntity.getArticle()))
                .journalist(this.journalistConverter.convertModelToDto(articleJournalistEntity.getJournalist()))
                .build();
    }

    public List<ArticleJournalistDTO> convertModelsToDtos(Collection<ArticleJournalistEntity> articleJournalistEntities) {
        return articleJournalistEntities.stream()
                .map(this::convertModelToDto)
                .collect(Collectors.toList());
    }
}
