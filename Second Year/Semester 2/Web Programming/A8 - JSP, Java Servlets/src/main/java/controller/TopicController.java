package controller;

import database.DBManager;
import domain.Comment;
import domain.Topic;
import domain.User;

import javax.servlet.ServletException;
import javax.servlet.http.*;
import java.io.IOException;
import java.util.List;

public class TopicController extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        resp.setContentType("text/html");
        HttpSession session = req.getSession();
        User user = (User) session.getAttribute("user");
        if (user == null) {
            resp.getWriter().println("No user logged in!");
            resp.sendRedirect("login");
            return;
        }
        int ok = 0;
        for (Cookie cookie: req.getCookies()) {
            if (cookie.getName().equals("topicId")) {
                DBManager dbManager = new DBManager();
                List<Topic> topics = dbManager.getAllTopics();
                Topic currentTopic = topics.stream()
                        .filter(topic -> topic.getId() == Integer.parseInt(cookie.getValue()))
                        .findFirst()
                        .get();
                req.getSession().setAttribute("currentTopic", currentTopic);
                List<Comment> comments = dbManager.getTopicComments(Integer.parseInt(cookie.getValue()));
                req.getSession().setAttribute("comments", comments);
                ok++;
            }
            if (ok == 1) {
                req.getRequestDispatcher("topic.jsp").include(req, resp);
                return;
            }
        }
        resp.getWriter().println("Invalid request!");
    }
}
