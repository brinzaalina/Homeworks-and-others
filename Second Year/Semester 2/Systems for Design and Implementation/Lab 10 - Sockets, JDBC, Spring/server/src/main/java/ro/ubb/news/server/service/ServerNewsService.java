package ro.ubb.news.server.service;

import org.apache.commons.lang3.tuple.Pair;
import org.springframework.beans.factory.annotation.Autowired;
import ro.ubb.news.common.NewsService;
import ro.ubb.news.common.domain.*;
import ro.ubb.news.common.exceptions.NewsServiceException;
import ro.ubb.news.server.repository.IRepository;

import java.util.Date;
import java.util.Optional;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutorService;
import java.util.stream.StreamSupport;

public class ServerNewsService implements NewsService {
    @Autowired
    private ExecutorService executorService;
    @Autowired
    private IRepository<Long, UserEntity> userRepository;
    @Autowired
    private IRepository<Long, JournalistEntity> journalistRepository;
    @Autowired
    private IRepository<Long, CategoryEntity> categoryRepository;
    @Autowired
    private IRepository<Long, ArticleEntity> articleRepository;
    @Autowired
    private IRepository<Pair<Long, Long>, ArticleJournalistEntity> articleJournalistRepository;

//    public ServerNewsService(ExecutorService executorService, IRepository<Long, UserEntity> userRepository, IRepository<Long, JournalistEntity> journalistRepository, IRepository<Long, CategoryEntity> categoryRepository, IRepository<Long, ArticleEntity> articleRepository, IRepository<Pair<Long, Long>, ArticleJournalistEntity> articleJournalistRepository) {
//        this.executorService = executorService;
//        this.userRepository = userRepository;
//        this.journalistRepository = journalistRepository;
//        this.categoryRepository = categoryRepository;
//        this.articleRepository = articleRepository;
//        this.articleJournalistRepository = articleJournalistRepository;
//    }

    @Override
    public CompletableFuture<Iterable<UserEntity>> getAllUsers() {
        return CompletableFuture.supplyAsync(userRepository::findAll, executorService);
    }

    @Override
    public CompletableFuture<String> addUser(String lastName, String firstName, String email, Date dob) {
        return CompletableFuture.supplyAsync(() -> {
            UserEntity user = new UserEntity(lastName, firstName, email);
            user.setDob(dob);
            userRepository.save(user);
            return "User added successfully";
        }, executorService);
    }

    @Override
    public CompletableFuture<String> deleteUser(Long id) {
        return CompletableFuture.supplyAsync(() -> {
            try {
                StreamSupport.stream(journalistRepository.findAll().spliterator(), false)
                        .filter(journalist -> journalist.getId().equals(id))
                        .findAny()
                        .ifPresent((journalist -> {
                            throw new NewsServiceException("User is assigned as a journalist, can't be deleted!");
                        }));
                userRepository.delete(id).orElseThrow(() -> new NewsServiceException("User does not exist!"));
                return "User deleted successfully";
            } catch (NewsServiceException e) {
                return e.getMessage();
            }
        }, executorService);
    }

    @Override
    public CompletableFuture<String> updateUser(Long id, String lastName, String firstName, String email, Date dob) {
        return CompletableFuture.supplyAsync(() -> {
            try {
                UserEntity user = new UserEntity(lastName, firstName, email);
                user.setId(id);
                user.setDob(dob);
                userRepository.update(user).orElseThrow(() -> new NewsServiceException("User does not exist!"));
                return "User updated successfully";
            } catch (NewsServiceException e) {
                return e.getMessage();
            }
        }, executorService);
    }

    @Override
    public CompletableFuture<Iterable<JournalistEntity>> getAllJournalists() {
        return CompletableFuture.supplyAsync(journalistRepository::findAll, executorService);
    }

    @Override
    public CompletableFuture<String> addJournalist(Long userId) {
        return CompletableFuture.supplyAsync(() -> {
            try {
                Optional<UserEntity> user = userRepository.findOne(userId);
                user.ifPresentOrElse((UserEntity u) -> {
                    JournalistEntity journalist = new JournalistEntity(userId);
                    journalistRepository.save(journalist);
                }, () -> {
                    throw new NewsServiceException("User does not exist.");
                });
                return "Journalist added successfully";
            } catch (NewsServiceException e) {
                return e.getMessage();
            }
        }, executorService);
    }

    @Override
    public CompletableFuture<String> deleteJournalist(Long userId) {
        return CompletableFuture.supplyAsync(() -> {
            try {
                StreamSupport.stream(articleJournalistRepository.findAll().spliterator(), false)
                        .filter(articleJournalist -> articleJournalist.getId().getRight().equals(userId))
                        .findAny()
                        .ifPresent((articleJournalist -> {
                            throw new NewsServiceException("Journalist is assigned to an article, can't be deleted!");
                        }));
                journalistRepository.delete(userId).orElseThrow(() -> new NewsServiceException("Journalist does not exist!"));
                return "Journalist deleted successfully";
            } catch (NewsServiceException e) {
                return e.getMessage();
            }
        }, executorService);
    }

    @Override
    public CompletableFuture<Iterable<CategoryEntity>> getAllCategories() {
        return CompletableFuture.supplyAsync(categoryRepository::findAll, executorService);
    }

    @Override
    public CompletableFuture<String> addCategory(String name) {
        return CompletableFuture.supplyAsync(() -> {
            CategoryEntity category = new CategoryEntity(name);
            categoryRepository.save(category);
            return "Category added successfully";
        }, executorService);
    }

    @Override
    public CompletableFuture<String> deleteCategory(Long id) {
        return CompletableFuture.supplyAsync(() -> {
            try {
                StreamSupport.stream(articleRepository.findAll().spliterator(), false)
                        .filter(article -> article.getCategoryId().equals(id))
                        .findAny()
                        .ifPresent((article -> {
                            throw new NewsServiceException("Category is assigned to an article, can't be deleted!");
                        }));
                categoryRepository.delete(id).orElseThrow(() -> new NewsServiceException("Category does not exist!"));
                return "Category deleted successfully";
            } catch (NewsServiceException e) {
                return e.getMessage();
            }
        }, executorService);
    }

    @Override
    public CompletableFuture<String> updateCategory(Long id, String name) {
        return CompletableFuture.supplyAsync(() -> {
            try {
                CategoryEntity category = new CategoryEntity(name);
                category.setId(id);
                categoryRepository.update(category).orElseThrow(() -> new NewsServiceException("Category does not exist!"));
                return "Category updated successfully";
            } catch (NewsServiceException e) {
                return e.getMessage();
            }
        }, executorService);
    }

    @Override
    public CompletableFuture<Iterable<ArticleEntity>> getAllArticles() {
        return CompletableFuture.supplyAsync(articleRepository::findAll, executorService);
    }

    @Override
    public CompletableFuture<String> addArticle(String title, String text, Long categoryId) {
        return CompletableFuture.supplyAsync(() -> {
            try {
                Optional<CategoryEntity> category = categoryRepository.findOne(categoryId);
                category.ifPresentOrElse((CategoryEntity c) -> {
                    ArticleEntity article = new ArticleEntity(title, text, categoryId);
                    articleRepository.save(article);
                }, () -> {
                    throw new NewsServiceException("Category does not exist.");
                });
                return "Article added successfully";
            } catch (NewsServiceException e) {
                return e.getMessage();
            }
        }, executorService);
    }

    @Override
    public CompletableFuture<String> deleteArticle(Long id) {
        return CompletableFuture.supplyAsync(() -> {
            try {
                StreamSupport.stream(articleJournalistRepository.findAll().spliterator(), false)
                        .filter(articleJournalist -> articleJournalist.getId().getLeft().equals(id))
                        .findAny()
                        .ifPresent((articleJournalist -> {
                            throw new NewsServiceException("Article is assigned to a journalist, can't be deleted!");
                        }));
                articleRepository.delete(id).orElseThrow(() -> new NewsServiceException("Article does not exist!"));
                return "Article deleted successfully";
            } catch (NewsServiceException e) {
                return e.getMessage();
            }
        }, executorService);
    }

    @Override
    public CompletableFuture<String> updateArticle(Long id, String title, String text, Long categoryId) {
        return CompletableFuture.supplyAsync(() -> {
            try {
                categoryRepository.findOne(categoryId).orElseThrow(() -> new NewsServiceException("Category does not exist!"));
                ArticleEntity article = new ArticleEntity(title, text, categoryId);
                article.setId(id);
                articleRepository.update(article).orElseThrow(() -> new NewsServiceException("Article does not exist!"));
                return "Article updated successfully";
            } catch (NewsServiceException e) {
                return e.getMessage();
            }
        }, executorService);
    }

    @Override
    public CompletableFuture<Iterable<ArticleJournalistEntity>> getAllArticleJournalists() {
        return CompletableFuture.supplyAsync(articleJournalistRepository::findAll, executorService);
    }

    @Override
    public CompletableFuture<String> addArticleJournalist(Long articleId, Long journalistId) {
        return CompletableFuture.supplyAsync(() -> {
            try {
                Optional<ArticleEntity> article = articleRepository.findOne(articleId);
                article.ifPresentOrElse((ArticleEntity a) -> {
                    Optional<JournalistEntity> journalist = journalistRepository.findOne(journalistId);
                    journalist.ifPresentOrElse((JournalistEntity j) -> {
                        ArticleJournalistEntity articleJournalist = new ArticleJournalistEntity();
                        articleJournalist.setId(Pair.of(articleId, journalistId));
                        articleJournalistRepository.save(articleJournalist);
                    }, () -> {throw new NewsServiceException("Journalist does not exist");});
                }, () -> {throw new NewsServiceException("Article does not exist.");});
                return "Article journalist added successfully!";
            } catch (NewsServiceException e) {
                return e.getMessage();
            }
        }, executorService);
    }

    @Override
    public CompletableFuture<String> deleteArticleJournalist(Long articleId, Long journalistId) {
        return CompletableFuture.supplyAsync(() -> {
            try {
                articleJournalistRepository.delete(Pair.of(articleId, journalistId)).orElseThrow(() -> new NewsServiceException("Article-journalist does not exist!"));
                return "Article-journalist deleted successfully";
            } catch (NewsServiceException e) {
                return e.getMessage();
            }
        }, executorService);
    }

    @Override
    public CompletableFuture<String> updateArticleJournalist(Long articleId, Long journalistId) {
        return CompletableFuture.supplyAsync(() -> {
            try {
                articleRepository.findOne(articleId).orElseThrow(() -> new NewsServiceException("Article does not exist!"));
                journalistRepository.findOne(journalistId).orElseThrow(() -> new NewsServiceException("Journalist does not exist!"));
                ArticleJournalistEntity articleJournalist = new ArticleJournalistEntity();
                articleJournalist.setId(Pair.of(articleId, journalistId));
                articleJournalistRepository.update(articleJournalist).orElseThrow(() -> new NewsServiceException("Article-journalist does not exist!"));
                return "Article-journalist updated successfully";
            } catch (NewsServiceException e) {
                return e.getMessage();
            }
        }, executorService);
    }
}
