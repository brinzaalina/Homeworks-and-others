package core.repository;

import core.domain.ArticleEntity;

import java.util.List;

public interface IArticleRepository extends IRepository<ArticleEntity, Long> {
    List<ArticleEntity> findAllByCategoryId(Long categoryId);
}
