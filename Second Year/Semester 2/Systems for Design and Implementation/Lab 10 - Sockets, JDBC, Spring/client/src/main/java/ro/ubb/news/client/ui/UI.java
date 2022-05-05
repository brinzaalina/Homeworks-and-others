package ro.ubb.news.client.ui;

import ro.ubb.news.common.NewsService;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;
import java.util.stream.StreamSupport;

public class UI {
    private final NewsService service;
    private final Map<Integer, Runnable> menuTable;

    public UI(NewsService service) {
        this.service = service;
        menuTable = new HashMap<>();
    }

    static void printMenu() {
        System.out.println("Welcome to News Sweet.");

        System.out.println("1.Add a user.");
        System.out.println("2.Delete a user.");
        System.out.println("3.Update a user.");
        System.out.println("4.View all users.");

        System.out.println("5.Add a journalist.");
        System.out.println("6.Delete a journalist.");
        System.out.println("7.View all journalists.");

        System.out.println("8.Add a category.");
        System.out.println("9.Delete a category.");
        System.out.println("10.Update a category.");
        System.out.println("11.View all categories.");

        System.out.println("12.Add an article.");
        System.out.println("13.Delete an article.");
        System.out.println("14.Update an article.");
        System.out.println("15.View all articles.");

        System.out.println("16.Add an article journalist.");
        System.out.println("17.Delete an article journalist.");
        System.out.println("18.Update an article journalist.");
        System.out.println("19.View all article journalists.");

        System.out.println("0.Exit.");
    }

    public void addUser() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Last name: ");
        String lastName = scanner.next();
        System.out.println("First name: ");
        String firstName = scanner.next();
        System.out.println("Email: ");
        String email = scanner.next();
        System.out.println("Date of birth (dd-mm-yyyy): ");
        String dateString = scanner.next();
        SimpleDateFormat dateFormat = new SimpleDateFormat("dd-MM-yyyy");
        try {
            Date dob = dateFormat.parse(dateString);
            service.addUser(lastName, firstName, email, dob).whenComplete((status, exception) -> {
                if (exception == null)
                    System.out.println(status);
                else
                    System.out.println(exception.getMessage());
            });
        }catch (ParseException e) {
            System.out.println("Wrong date format.");
        }
    }

    public void deleteUser() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("User id: ");
        Long userId = scanner.nextLong();
        service.deleteUser(userId).whenComplete((status, exception) -> {
            if (exception == null) {
                System.out.println(status);
            } else {
                System.out.println(exception.getMessage());
            }
        });
    }

    public void updateUser() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("User id: ");
        Long userId = scanner.nextLong();
        System.out.println("Last name: ");
        String lastName = scanner.next();
        System.out.println("First name: ");
        String firstName = scanner.next();
        System.out.println("Email: ");
        String email = scanner.next();
        System.out.println("Date of birth (dd-mm-yyyy): ");
        String dateString = scanner.next();
        SimpleDateFormat dateFormat = new SimpleDateFormat("dd-MM-yyyy");
        try {
            Date dob = dateFormat.parse(dateString);
            service.updateUser(userId, lastName, firstName, email, dob).whenComplete((status, exception) -> {
                if (exception == null)
                    System.out.println(status);
                else
                    System.out.println(exception.getMessage());
            });
        }catch (ParseException e) {
            System.out.println("Wrong date format.");
        }
    }

    public void showUsers() {
        service.getAllUsers().whenComplete((result, exception) -> {
            if (exception == null) {
                StreamSupport.stream(result.spliterator(), false)
                        .forEach(System.out::println);
            } else {
                System.out.println(exception.getMessage());
            }
        });
    }

    public void addJournalist() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("UserId: ");
        Long userId = scanner.nextLong();
        service.addJournalist(userId).whenComplete((status, exception) -> {
            if (exception == null)
                System.out.println(status);
            else
                System.out.println(exception.getMessage());
        });
    }

    public void deleteJournalist() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Journalist id: ");
        Long journalistId = scanner.nextLong();
        service.deleteJournalist(journalistId).whenComplete((status, exception) -> {
            if (exception == null) {
                System.out.println(status);
            } else {
                System.out.println(exception.getMessage());
            }
        });
    }

    public void showJournalists() {
        service.getAllJournalists().whenComplete((result, exception) -> {
            if (exception == null) {
                StreamSupport.stream(result.spliterator(), false)
                        .forEach(System.out::println);
            } else {
                System.out.println(exception.getMessage());
            }
        });
    }

    public void addCategory() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Name: ");
        String name = scanner.next();
        service.addCategory(name).whenComplete((status, exception) -> {
            if (exception == null)
                System.out.println(status);
            else
                System.out.println(exception.getMessage());
        });
    }

    public void deleteCategory() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Category id: ");
        Long categoryId = scanner.nextLong();
        service.deleteCategory(categoryId).whenComplete((status, exception) -> {
            if (exception == null) {
                System.out.println(status);
            } else {
                System.out.println(exception.getMessage());
            }
        });
    }

    public void updateCategory() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Category id: ");
        Long categoryId = scanner.nextLong();
        System.out.println("Name: ");
        String name = scanner.next();
        service.updateCategory(categoryId, name).whenComplete((status, exception) -> {
            if (exception == null)
                System.out.println(status);
            else
                System.out.println(exception.getMessage());
        });
    }

    public void showCategories() {
        service.getAllCategories().whenComplete((result, exception) -> {
            if (exception == null) {
                StreamSupport.stream(result.spliterator(), false)
                        .forEach(System.out::println);
            } else {
                System.out.println(exception.getMessage());
            }
        });
    }

    public void addArticle() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Title: ");
        String title = scanner.next();
        System.out.println("Text: ");
        String text = scanner.next();
        System.out.println("Category id: ");
        Long categoryId = scanner.nextLong();
        service.addArticle(title, text, categoryId).whenComplete((status, exception) -> {
            if (exception == null)
                System.out.println(status);
            else
                System.out.println(exception.getMessage());
        });
    }

    public void deleteArticle() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Article id: ");
        Long articleId = scanner.nextLong();
        service.deleteArticle(articleId).whenComplete((status, exception) -> {
            if (exception == null) {
                System.out.println(status);
            } else {
                System.out.println(exception.getMessage());
            }
        });
    }

    public void updateArticle() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Article id: ");
        Long articleId = scanner.nextLong();
        System.out.println("Title: ");
        String title = scanner.next();
        System.out.println("Text: ");
        String text = scanner.next();
        System.out.println("Category id: ");
        Long categoryId = scanner.nextLong();
        service.updateArticle(articleId, title, text, categoryId).whenComplete((status, exception) -> {
            if (exception == null)
                System.out.println(status);
            else
                System.out.println(exception.getMessage());
        });
    }

    public void showArticles() {
        service.getAllArticles().whenComplete((result, exception) -> {
            if (exception == null) {
                StreamSupport.stream(result.spliterator(), false)
                        .forEach(System.out::println);
            } else {
                System.out.println(exception.getMessage());
            }
        });
    }

    public void addArticleJournalist() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Article id: ");
        Long articleId = scanner.nextLong();
        System.out.println("Journalist id: ");
        Long journalistId = scanner.nextLong();
        service.addArticleJournalist(articleId, journalistId).whenComplete((status, exception) -> {
            if (exception == null)
                System.out.println(status);
            else
                System.out.println(exception.getMessage());
        });
    }

    public void deleteArticleJournalist() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Article id: ");
        Long articleId = scanner.nextLong();
        System.out.println("Journalist id: ");
        Long journalistId = scanner.nextLong();
        service.deleteArticleJournalist(articleId, journalistId).whenComplete((status, exception) -> {
            if (exception == null)
                System.out.println(status);
            else
                System.out.println(exception.getMessage());
        });
    }

    public void updateArticleJournalist() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Article id: ");
        Long articleId = scanner.nextLong();
        System.out.println("Journalist id: ");
        Long journalistId = scanner.nextLong();
        service.updateArticleJournalist(articleId, journalistId).whenComplete((status, exception) -> {
            if (exception == null)
                System.out.println(status);
            else
                System.out.println(exception.getMessage());
        });
    }

    public void showArticleJournalists() {
        service.getAllArticleJournalists().whenComplete((result, exception) -> {
            if (exception == null) {
                StreamSupport.stream(result.spliterator(), false)
                        .forEach(System.out::println);
            } else {
                System.out.println(exception.getMessage());
            }
        });
    }

    public void run() {
        menuTable.put(1, this::addUser);
        menuTable.put(2, this::deleteUser);
        menuTable.put(3, this::updateUser);
        menuTable.put(4, this::showUsers);

        menuTable.put(5, this::addJournalist);
        menuTable.put(6, this::deleteJournalist);
        menuTable.put(7, this::showJournalists);

        menuTable.put(8, this::addCategory);
        menuTable.put(9, this::deleteCategory);
        menuTable.put(10, this::updateCategory);
        menuTable.put(11, this::showCategories);

        menuTable.put(12, this::addArticle);
        menuTable.put(13, this::deleteArticle);
        menuTable.put(14, this::updateArticle);
        menuTable.put(15, this::showArticles);

        menuTable.put(16, this::addArticleJournalist);
        menuTable.put(17, this::deleteArticleJournalist);
        menuTable.put(18, this::updateArticleJournalist);
        menuTable.put(19, this::showArticleJournalists);

        boolean done = false;
        Scanner scanner = new Scanner(System.in);
        while (!done) {
            printMenu();
            try {
                int choice = scanner.nextInt();
                if (choice == 0)
                    done = true;
                else {
                    Runnable toRun = menuTable.get(choice);
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
}
