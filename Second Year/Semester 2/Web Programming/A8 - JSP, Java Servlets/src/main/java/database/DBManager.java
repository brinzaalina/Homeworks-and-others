package database;

import domain.Comment;
import domain.Topic;
import domain.User;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class DBManager {
    private static final String DATABASE = "jdbc:postgresql://localhost:5432/forum";
    private static final String USERNAME = "postgres";
    private static final String PASSWORD = "test123";

    public DBManager() {
        try {
            Class.forName("org.postgresql.Driver");
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    public User getUserWithUsername(String username) {
        User user = null;
        String statement = "SELECT * FROM users U WHERE U.username = ?";
        try (var connection = DriverManager.getConnection(DATABASE, USERNAME, PASSWORD);
        var preparedStatement = connection.prepareStatement(statement)) {
            preparedStatement.setString(1, username);
            var rs = preparedStatement.executeQuery();
            if (rs.next()) {
                user = new User(rs.getInt("id"), rs.getString("username"), rs.getString("password"));
            }
        } catch (SQLException exception) {
            exception.printStackTrace();
        }
        return user;
    }

    public User authenticate(String username, String password) {
        User user = getUserWithUsername(username);
        if (user != null && user.getPassword().equals(password)) {
            return user;
        }
        return null;
    }

    public User getUserWithId(int userId) {
        User user = null;
        String statement = "SEELCT * FROM users U WHERE U.id = ?";
        try (var connection = DriverManager.getConnection(DATABASE, USERNAME, PASSWORD);
        var preparedStatement = connection.prepareStatement(statement)) {
            preparedStatement.setInt(1, userId);
            var rs = preparedStatement.executeQuery();
            if (rs.next()) {
                user = new User(rs.getInt("id"), rs.getString("username"), rs.getString("password"));
            }
        } catch (SQLException exception) {
            exception.printStackTrace();
        }
        return user;
    }

    public List<Topic> getAllTopics() {
        List<Topic> topics = new ArrayList<>();
        String statement = "SELECT * FROM topics";
        try (var connection = DriverManager.getConnection(DATABASE, USERNAME, PASSWORD);
        var preparedStatement = connection.prepareStatement(statement);
        var rs = preparedStatement.executeQuery()) {
            while (rs.next()) {
                topics.add(new Topic(rs.getInt("id"), rs.getInt("user_id"), rs.getString("name")));
            }
        } catch (SQLException exception) {
            exception.printStackTrace();
        }
        return topics;
    }

    public void addTopic(Topic topic) {
        String statement = "INSERT INTO topics(user_id, name) VALUES (?, ?)";
        try (var connection = DriverManager.getConnection(DATABASE, USERNAME, PASSWORD);
        var preparedStatement = connection.prepareStatement(statement)) {
            preparedStatement.setInt(1, topic.getUserId());
            preparedStatement.setString(2, topic.getName());
            preparedStatement.execute();
        } catch (SQLException exception) {
            exception.printStackTrace();
        }
    }

    public List<Comment> getTopicComments(int topicId) {
        List<Comment> comments = new ArrayList<>();
        String statement = "SELECT * FROM comments C WHERE c.topic_id = ?";
        try (var connection = DriverManager.getConnection(DATABASE, USERNAME, PASSWORD);
        var preparedStatement = connection.prepareStatement(statement)) {
            preparedStatement.setInt(1, topicId);
            var rs = preparedStatement.executeQuery();
            while (rs.next()) {
                comments.add(new Comment(
                        rs.getInt("id"),
                        rs.getInt("user_id"),
                        rs.getString("content"),
                        rs.getInt("topic_id")
                ));
            }
        } catch (SQLException exception) {
            exception.printStackTrace();
        }
        return comments;
    }

    public void addComment(Comment comment) {
        String statement = "INSERT INTO comments(user_id, content, topic_id) VALUES (?, ?, ?)";
        try (var connection = DriverManager.getConnection(DATABASE, USERNAME, PASSWORD);
        var preparedStatement = connection.prepareStatement(statement)) {
            preparedStatement.setInt(1, comment.getUserId());
            preparedStatement.setString(2, comment.getContent());
            preparedStatement.setInt(3, comment.getTopicId());
            preparedStatement.execute();
        } catch (SQLException exception) {
            exception.printStackTrace();
        }
    }

    public void deleteComment(int commentId) {
        String statement = "DELETE FROM comments WHERE id = ?";
        try (var connection = DriverManager.getConnection(DATABASE, USERNAME, PASSWORD);
        var preparedStatement = connection.prepareStatement(statement)) {
            preparedStatement.setInt(1, commentId);
            preparedStatement.execute();
        } catch (SQLException exception) {
            exception.printStackTrace();
        }
    }

    public User getTopicUser(int topicId) {
        User user = null;
        String statement = "SELECT * FROM users U WHERE U.id IN (SELECT user_id FROM topics T WHERE T.id = ?)";
        try (var connection = DriverManager.getConnection(DATABASE, USERNAME, PASSWORD);
             var preparedStatement = connection.prepareStatement(statement)) {
            preparedStatement.setInt(1, topicId);
            var rs = preparedStatement.executeQuery();
            if (rs.next()) {
                user = new User(rs.getInt("id"), rs.getString("username"), rs.getString("password"));
            }
        } catch (SQLException exception) {
            exception.printStackTrace();
        }
        return user;
    }
}
