package web.controller;

import core.domain.CategoryEntity;
import core.service.ICategoryService;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import web.converter.CategoryConverter;
import web.dto.CategoriesDTO;
import web.dto.CategoryDTO;

import java.util.List;

@RestController
public class CategoryController {
    public static final Logger logger = LoggerFactory.getLogger(CategoryController.class);

    @Autowired
    private ICategoryService categoryService;

    @Autowired
    CategoryConverter categoryConverter;

    @RequestMapping(value = "/categories")
    CategoriesDTO getCategoriesFromRepository() {
        logger.trace("getAllCategories - method entered");
        List<CategoryEntity> categories = categoryService.getAllCategories();
        CategoriesDTO categoriesDTO = new CategoriesDTO(categoryConverter.convertModelsToDTOs(categories));
        logger.trace("getAllCategories: " + categories);
        return categoriesDTO;
    }

    @RequestMapping(value = "/categories", method = RequestMethod.POST)
    void addCategory(@RequestBody CategoryDTO categoryDTO) {
        logger.trace("addCategory - method entered - categoryDTO: " + categoryDTO);
        var category = categoryConverter.convertDtoToModel(categoryDTO);
        categoryService.addCategory(category.getName());
        logger.trace("addCategory - category added");
    }

    @RequestMapping(value = "/categories/{id}", method = RequestMethod.DELETE)
    ResponseEntity<?> deleteCategory(@PathVariable Long id) {
        categoryService.deleteCategory(id);
        return new ResponseEntity<>(HttpStatus.OK);
    }

    @RequestMapping(value = "/categories/{id}", method = RequestMethod.PUT)
    void updateCategory(@PathVariable Long id, @RequestBody CategoryDTO categoryDTO) {
        logger.trace("updateCategory - method entered - categoryDTO: " + categoryDTO);
        var category = categoryConverter.convertDtoToModel(categoryDTO);
        categoryService.updateCategory(id, category.getName());
        logger.trace("updateCategory - category updated");
    }

    @RequestMapping(value = "/categories/sort/name")
    CategoriesDTO getCategoriesSortedByName() {
        logger.trace("getCategoriesSortedByName - method entered");
        List<CategoryEntity> categories = categoryService.getCategoriesSortedByName();
        CategoriesDTO categoriesDTO = new CategoriesDTO(categoryConverter.convertModelsToDTOs(categories));
        logger.trace("getCategoriesSortedByName: " + categories);
        return categoriesDTO;
    }
}
