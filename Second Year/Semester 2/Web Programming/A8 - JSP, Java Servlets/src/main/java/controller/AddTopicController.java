package controller;

import database.DBManager;
import domain.Topic;
import domain.User;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

public class AddTopicController extends HttpServlet {
    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        resp.setContentType("text/html");
        HttpSession session = req.getSession();
        User user = (User) session.getAttribute("user");
        if (user == null) {
            resp.getWriter().println("No user logged in!");
            return;
        }
        String name = req.getParameter("name");
        Integer userId = Integer.parseInt(req.getParameter("userId"));
        DBManager dbManager = new DBManager();
        dbManager.addTopic(new Topic(0, userId, name));
    }
}
