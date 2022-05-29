package controller;

import database.DBManager;
import domain.Topic;
import domain.User;

import javax.servlet.ServletException;
import javax.servlet.http.*;
import java.io.IOException;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class MainController extends HttpServlet {
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
        DBManager dbManager = new DBManager();
        List<Topic> topics = dbManager.getAllTopics();
        Map<Topic,User> topicUserMap = new HashMap<>();
        for (Topic topic: topics) {
            topicUserMap.put(topic, dbManager.getTopicUser(topic.getId()));
        }
        req.getSession().setAttribute("topics", topicUserMap);
        req.getRequestDispatcher("main.jsp").include(req, resp);
    }
}
