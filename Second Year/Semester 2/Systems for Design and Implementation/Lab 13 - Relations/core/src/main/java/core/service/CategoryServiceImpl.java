package core.service;

import core.domain.CategoryEntity;
import core.domain.validators.CategoryValidator;
import core.exceptions.NewsException;
import core.repository.IArticleRepository;
import core.repository.ICategoryRepository;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;

@Service
public class CategoryServiceImpl implements ICategoryService{
    public static final Logger logger = LoggerFactory.getLogger(CategoryServiceImpl.class);

    @Autowired
    private CategoryValidator validator;

    @Autowired
    private ICategoryRepository categoryRepository;

    @Autowired
    private IArticleRepository articleRepository;

    @Override
    public List<CategoryEntity> getAllCategories() {
        logger.trace("getAllCategories - method entered");
        List<CategoryEntity> categories = categoryRepository.findAll();
        logger.trace("getAllCategories: " + categories);
        return categories;
    }

    @Override
    public void addCategory(String name) {
        logger.trace("addCategory - method entered - name: " + name);
        CategoryEntity category = new CategoryEntity();
        category.setName(name);
        validator.validate(category);
        categoryRepository.save(category);
        logger.trace("addCategory - method finished");
    }

    @Override
    public void deleteCategory(Long id) {
        logger.trace("deleteCategory - method entered - id: " + id);
//        articleRepository.findAllByCategoryId(id).stream()
//                .findAny()
//                .ifPresent((article) -> {
//                    throw new NewsException("Category is assigned to an article!");
//                });
        categoryRepository.findById(id)
                .ifPresentOrElse((category) -> categoryRepository.deleteById(id), () -> {
                    throw new NewsException("Category does not exist!");
                });
        logger.trace("deleteCategory - method finished");
    }

    @Override
    @Transactional
    public void updateCategory(Long id, String name) {
        logger.trace("updateCategory - method entered - id: " + id + ", name: " + name);
        CategoryEntity categoryEntity = new CategoryEntity();
        categoryEntity.setId(id);
        categoryEntity.setName(name);
        validator.validate(categoryEntity);
        categoryRepository.findById(id)
                .ifPresentOrElse((category) -> {
                    category.setName(name);
                }, () -> {
                    throw new NewsException("Category does not exist!");
                });
        logger.trace("updateCategory - method finished");
    }

    @Override
    public List<CategoryEntity> getCategoriesSortedByName() {
        logger.trace("getCategoriesSortedByName - method entered");
        var categories = categoryRepository.findAllByOrderByNameAsc();
        logger.trace("getCategoriesSortedByName - result = {}", categories);
        return categories;
    }
}
