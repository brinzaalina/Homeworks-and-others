package core.service;

import core.domain.CategoryEntity;

import java.util.List;

public interface ICategoryService {
    List<CategoryEntity> getAllCategories();
    void addCategory(String name);
    void deleteCategory(Long id);
    void updateCategory(Long id, String name);
    List<CategoryEntity> getCategoriesSortedByName();
}
