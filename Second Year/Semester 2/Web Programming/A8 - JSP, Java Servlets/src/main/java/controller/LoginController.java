package controller;

import database.DBManager;
import domain.User;

import javax.servlet.ServletException;
import javax.servlet.http.*;
import java.io.IOException;

public class LoginController extends HttpServlet {
    public LoginController() {
        super();
    }

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        resp.setContentType("text/html");
        req.getRequestDispatcher("login.jsp").include(req, resp);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        resp.setContentType("text/html");
        String username = req.getParameter("username");
        String password = req.getParameter("password");
        if (username.isEmpty()) {
            req.getSession().setAttribute("error", "Username must not be empty!");
            req.getRequestDispatcher("login.jsp").include(req, resp);
        } else if (password.isEmpty()) {
            req.getSession().setAttribute("error", "Password must not be empty!");
            req.getRequestDispatcher("login.jsp").include(req, resp);
        } else {
            DBManager dbManager = new DBManager();
            User user = dbManager.authenticate(username, password);
            if (user != null) {
                HttpSession session = req.getSession();
                session.setAttribute("user", user);
                resp.sendRedirect("main");
            } else {
                req.getSession().setAttribute("error", "Invalid username/password!");
                req.getRequestDispatcher("login.jsp").include(req, resp);
            }
        }
    }
}
