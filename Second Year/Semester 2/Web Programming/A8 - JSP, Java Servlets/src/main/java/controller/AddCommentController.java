package controller;

import database.DBManager;
import domain.Comment;
import domain.Topic;
import domain.User;

import javax.servlet.ServletException;
import javax.servlet.http.*;
import java.io.IOException;
import java.util.List;

public class AddCommentController extends HttpServlet {
    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        HttpSession session = req.getSession();
        User user = (User) session.getAttribute("user");
        if (user == null) {
            resp.getWriter().println("No user logged in!");
            return;
        }
        Topic currentTopic = null;
        DBManager dbManager = new DBManager();
        int ok = 0;
        for (Cookie cookie: req.getCookies()) {
            if (cookie.getName().equals("topicId")) {
                ok++;
                List<Topic> topics = dbManager.getAllTopics();
                currentTopic = topics.stream()
                        .filter(topic -> topic.getId() == Integer.parseInt(cookie.getValue()))
                        .findFirst()
                        .get();
            }
            if (ok == 1) {
                String content = req.getParameter("text");
                dbManager.addComment(new Comment(0, user.getId(), content, currentTopic.getId()));
                return;
            }
        }
        resp.getWriter().println("Invalid request!");
    }
}
