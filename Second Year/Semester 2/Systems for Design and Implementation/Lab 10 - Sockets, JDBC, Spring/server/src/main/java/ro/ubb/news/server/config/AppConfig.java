package ro.ubb.news.server.config;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import ro.ubb.news.common.NewsService;
import ro.ubb.news.common.domain.ArticleJournalistEntity;
import ro.ubb.news.common.domain.validators.*;
import ro.ubb.news.server.repository.*;
import ro.ubb.news.server.service.ServerNewsService;
import ro.ubb.news.server.tcp.TcpServer;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

@Configuration
public class AppConfig {
    @Bean
    ExecutorService executorService() {
        return Executors.newFixedThreadPool(
                Runtime.getRuntime().availableProcessors()
        );
    }

    @Bean
    UserValidator userValidator() {
        return new UserValidator();
    }

    @Bean
    JournalistValidator journalistValidator() {
        return new JournalistValidator();
    }

    @Bean
    CategoryValidator categoryValidator() {
        return new CategoryValidator();
    }

    @Bean
    ArticleValidator articleValidator() {
        return new ArticleValidator();
    }

    @Bean
    ArticleJournalistValidator articleJournalistValidator() {
        return new ArticleJournalistValidator();
    }

    @Bean
    UserDatabaseRepository userDatabaseRepository() {
        return new UserDatabaseRepository();
    }

    @Bean
    JournalistDatabaseRepository journalistDatabaseRepository() {
        return new JournalistDatabaseRepository();
    }

    @Bean
    CategoryDatabaseRepository categoryDatabaseRepository() {
        return new CategoryDatabaseRepository();
    }

    @Bean
    ArticleDatabaseRepository articleDatabaseRepository() {
        return new ArticleDatabaseRepository();
    }

    @Bean
    ArticleJournalistDatabaseRepository articleJournalistDatabaseRepository() {
        return new ArticleJournalistDatabaseRepository();
    }

    @Bean
    ServerNewsService serverNewsService() {
        return new ServerNewsService();
    }

    @Bean
    TcpServer tcpServer() {
        return new TcpServer(NewsService.PORT);
    }
}
