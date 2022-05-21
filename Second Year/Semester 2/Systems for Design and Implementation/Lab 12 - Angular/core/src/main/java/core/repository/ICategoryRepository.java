package core.repository;

import core.domain.CategoryEntity;

import java.util.List;

public interface ICategoryRepository extends IRepository<CategoryEntity, Long> {
    List<CategoryEntity> findAllByOrderByNameAsc();
}
