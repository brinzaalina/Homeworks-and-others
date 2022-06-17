package core.repository;

import core.domain.ArticleEntity;
import core.domain.CategoryEntity;

import java.util.List;

public interface IArticleRepository extends IRepository<ArticleEntity, Long> {
    List<ArticleEntity> findAllByCategory(CategoryEntity category);
}
