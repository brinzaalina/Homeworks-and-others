package client.ui;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;
import org.springframework.web.client.HttpStatusCodeException;
import org.springframework.web.client.RestTemplate;
import web.dto.*;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;

@Component
public class UI {
    @Autowired
    private RestTemplate restTemplate;

    private final Map<Integer, Runnable> menu = new HashMap<>();
    String journalistsUrl = "http://localhost:8080/api/journalists";
    String categoriesUrl = "http://localhost:8080/api/categories";
    String articlesUrl = "http://localhost:8080/api/articles";
    String articleJournalistsUrl = "http://localhost:8080/api/articles-journalists";

    public void runConsole() {
        menu.put(1, this::addJournalist);
        menu.put(2, this::deleteJournalist);
        menu.put(3, this::updateJournalist);
        menu.put(4, this::showJournalists);

        menu.put(5, this::addCategory);
        menu.put(6, this::deleteCategory);
        menu.put(7, this::updateCategory);
        menu.put(8, this::showCategories);

        menu.put(9, this::addArticle);
        menu.put(10, this::deleteArticle);
        menu.put(11, this::updateArticle);
        menu.put(12, this::showArticles);

        menu.put(13, this::addArticleJournalist);
        menu.put(14, this::deleteArticleJournalist);
        menu.put(15, this::showArticleJournalistPairs);

        menu.put(16, this::filterJournalistByDob);
        menu.put(17, this::getJournalistWithTheMostArticles);
        menu.put(18, this::getCategoriesSortedByName);
        menu.put(19, this::filterArticlesByCategory);

        boolean done = false;
        Scanner scanner = new Scanner(System.in);
        while (!done) {
            printMenu();
            try {
                int choice = scanner.nextInt();
                if (choice == 0)
                    done = true;
                else {
                    Runnable toRun = menu.get(choice);
                    if (toRun == null) {
                        System.out.println("Bad choice!");
                    } else {
                        toRun.run();
                    }
                }
            } catch (InputMismatchException inputMismatchException) {
                System.out.println("Invalid integer!");
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }
        }
    }

    static void printMenu() {
        System.out.println("0. Exit.");

        System.out.println("1. Add a journalist.");
        System.out.println("2. Delete a journalist.");
        System.out.println("3. Update a journalist.");
        System.out.println("4. View all journalist.");

        System.out.println("5. Add a category.");
        System.out.println("6. Delete a category.");
        System.out.println("7. Update a category.");
        System.out.println("8. View all categories.");

        System.out.println("9. Add an article.");
        System.out.println("10. Delete an article.");
        System.out.println("11. Update an article.");
        System.out.println("12. View all articles.");

        System.out.println("13. Add an article-journalist.");
        System.out.println("14. Delete an article-journalist.");
        System.out.println("15. View all article-journalist pairs.");

        System.out.println("16. Filter journalists by date of birth before.");
        System.out.println("17. Get journalists with the most articles.");
        System.out.println("18. Get categories sorted by name.");
        System.out.println("19. Filter articles by category.");
    }

    private void filterJournalistByDob() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter date (dd-mm-yyyy): ");
        String date = scanner.next();
        try {
            JournalistsDTO journalistsDTO = restTemplate.getForObject(journalistsUrl + "/filter/{date}", JournalistsDTO.class, date);
            if (journalistsDTO == null)
                System.out.println("No journalists born before the given date!");
            else
                journalistsDTO.getJournalists().forEach(System.out::println);
        } catch (HttpStatusCodeException ex) {
            System.out.println("Cannot filter journalists!");
        }
    }

    private void getJournalistWithTheMostArticles() {
        try {
            JournalistDTO journalistDTO = restTemplate.getForObject(articleJournalistsUrl + "/most", JournalistDTO.class);
            if (journalistDTO == null)
                System.out.println("No journalist!");
            else
                System.out.println(journalistDTO);
        } catch (HttpStatusCodeException ex) {
            System.out.println("Cannot get journalist!");
        }
    }

    private void getCategoriesSortedByName() {
        try {
            CategoriesDTO categoriesDTO = restTemplate.getForObject(categoriesUrl + "/sort/name", CategoriesDTO.class);
            if (categoriesDTO == null)
                System.out.println("No categories!");
            else
                categoriesDTO.getCategories().forEach(System.out::println);
        } catch (HttpStatusCodeException ex) {
            System.out.println("Cannot get journalist!");
        }
    }

    private void filterArticlesByCategory() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Category id: ");
        Long categoryId = scanner.nextLong();
        try {
            ArticlesDTO articlesDTO = restTemplate.getForObject(articlesUrl + "/filter/{categoryId}", ArticlesDTO.class, categoryId);
            if (articlesDTO == null)
                System.out.println("No articles with the given category!");
            else
                articlesDTO.getArticles().forEach(System.out::println);
        } catch (HttpStatusCodeException ex) {
            System.out.println("Cannot get journalist!");
        }
    }

    private void addJournalist() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter last name: ");
        String lastName = scanner.next();
        System.out.println("Enter first name: ");
        String firstName = scanner.next();
        System.out.println("Enter email: ");
        String email = scanner.next();
        System.out.println("Date of birth (dd-mm-yyyy): ");
        String dobString = scanner.next();
        SimpleDateFormat dateFormat = new SimpleDateFormat("dd-MM-yyyy");
        try {
            Date dob = dateFormat.parse(dobString);
            JournalistDTO journalistDTO = new JournalistDTO(lastName, firstName, email, dob);
            restTemplate.postForObject(journalistsUrl, journalistDTO, JournalistDTO.class);
            System.out.println("Journalist added successfully.");
        } catch (ParseException e) {
            System.out.println("Wrong date format!");
        } catch (HttpStatusCodeException ex) {
            System.out.println("Cannot add journalist!");
        }
    }

    private void deleteJournalist() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Journalist id:");
        Long id = scanner.nextLong();
        try {
            restTemplate.delete(journalistsUrl + "/{id}", id);
            System.out.println("Journalist deleted successfully!");
        } catch (HttpStatusCodeException ex) {
            System.out.println("Cannot delete journalist!");
        }
    }

    private void updateJournalist() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter journalist id: ");
        Long id = scanner.nextLong();
        System.out.println("Enter last name: ");
        String lastName = scanner.next();
        System.out.println("Enter first name: ");
        String firstName = scanner.next();
        System.out.println("Enter email: ");
        String email = scanner.next();
        System.out.println("Date of birth (dd-mm-yyyy): ");
        String dobString = scanner.next();
        SimpleDateFormat dateFormat = new SimpleDateFormat("dd-MM-yyyy");
        try {
            Date dob = dateFormat.parse(dobString);
            JournalistDTO journalistDTO = new JournalistDTO(lastName, firstName, email, dob);
            restTemplate.put(journalistsUrl + "/{id}", journalistDTO, id);
            System.out.println("Journalist updated successfully.");
        } catch (ParseException e) {
            System.out.println("Wrong date format!");
        } catch (HttpStatusCodeException ex) {
            System.out.println("Cannot update journalist!");
        }
    }

    private void showJournalists() {
        JournalistsDTO journalistsDTO = restTemplate.getForObject(journalistsUrl, JournalistsDTO.class);
        assert journalistsDTO != null;
        journalistsDTO.getJournalists().forEach(System.out::println);
    }

    private void addCategory() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter name: ");
        String name = scanner.next();
        try {
            CategoryDTO categoryDTO = new CategoryDTO(name);
            restTemplate.postForObject(categoriesUrl, categoryDTO, CategoryDTO.class);
            System.out.println("Category added successfully.");
        } catch (HttpStatusCodeException ex) {
            System.out.println("Cannot add category!");
        }
    }

    private void deleteCategory() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Category id:");
        Long id = scanner.nextLong();
        try {
            restTemplate.delete(categoriesUrl + "/{id}", id);
            System.out.println("Category deleted successfully!");
        } catch (HttpStatusCodeException ex) {
            System.out.println("Cannot delete category!");
        }
    }

    private void updateCategory() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Category id:");
        Long id = scanner.nextLong();
        System.out.println("Enter name: ");
        String name = scanner.next();
        try {
            CategoryDTO categoryDTO = new CategoryDTO(name);
            categoryDTO.setId(id);
            restTemplate.put(categoriesUrl + "/{id}", categoryDTO, id);
            System.out.println("Category updated successfully.");
        } catch (HttpStatusCodeException ex) {
            System.out.println("Cannot update category!");
        }
    }

    private void showCategories() {
        CategoriesDTO categoriesDTO = restTemplate.getForObject(categoriesUrl, CategoriesDTO.class);
        assert categoriesDTO != null;
        categoriesDTO.getCategories().forEach(System.out::println);
    }

    private void addArticle() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Title: ");
        String title = scanner.next();
        System.out.println("Text: ");
        String text = scanner.next();
        System.out.println("Category ID: ");
        Long categoryId = scanner.nextLong();
        try {
            ArticleDTO articleDTO = new ArticleDTO(title, text, categoryId);
            restTemplate.postForObject(articlesUrl, articleDTO, ArticleDTO.class);
            System.out.println("Article added successfully!");
        } catch (HttpStatusCodeException ex) {
            System.out.println("Cannot add article!");
        }
    }

    private void deleteArticle() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Id: ");
        Long id = scanner.nextLong();
        try {
            restTemplate.delete(articlesUrl + "/{id}", id);
            System.out.println("Article deleted successfully!");
        } catch (HttpStatusCodeException ex) {
            System.out.println("Cannot delete article!");
        }
    }

    private void updateArticle() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Id: ");
        Long id = scanner.nextLong();
        System.out.println("Title: ");
        String title = scanner.next();
        System.out.println("Text: ");
        String text = scanner.next();
        System.out.println("Category ID: ");
        Long categoryId = scanner.nextLong();
        try {
            ArticleDTO articleDTO = new ArticleDTO(title, text, categoryId);
            articleDTO.setId(id);
            restTemplate.put(articlesUrl + "/{id}", articleDTO, id);
            System.out.println("Article updated successfully!");
        } catch (HttpStatusCodeException ex) {
            System.out.println("Cannot update article!");
        }
    }

    private void showArticles() {
        ArticlesDTO articlesDTO = restTemplate.getForObject(articlesUrl, ArticlesDTO.class);
        assert articlesDTO != null;
        articlesDTO.getArticles().forEach(System.out::println);
    }

    private void addArticleJournalist() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Article id: ");
        Long articleId = scanner.nextLong();
        System.out.println("Journalist id: ");
        Long journalistId = scanner.nextLong();
        try {
            ArticleJournalistPrimaryKeyDTO articleJournalistPrimaryKeyDTO = new ArticleJournalistPrimaryKeyDTO(articleId, journalistId);
            restTemplate.postForObject(articleJournalistsUrl, articleJournalistPrimaryKeyDTO, ArticleJournalistPrimaryKeyDTO.class);
            System.out.println("Article-journalist added successfully!");
        } catch (HttpStatusCodeException ex) {
            System.out.println("Cannot add article-journalist!");
        }
    }

    private void deleteArticleJournalist() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Article id: ");
        Long articleId = scanner.nextLong();
        System.out.println("Journalist id: ");
        Long journalistId = scanner.nextLong();
        try {
            restTemplate.delete(articleJournalistsUrl + "/{articleId}&{journalistId}", articleId, journalistId);
            System.out.println("Article-journalist deleted successfully!");
        } catch (HttpStatusCodeException ex) {
            System.out.println("Cannot delete article-journalist!");
        }
    }

    private void showArticleJournalistPairs() {
        ArticleJournalistsDTO articleJournalistsDTO = restTemplate.getForObject(articleJournalistsUrl, ArticleJournalistsDTO.class);
        assert articleJournalistsDTO != null;
        articleJournalistsDTO.getArticleJournalists().forEach(System.out::println);
    }
}
