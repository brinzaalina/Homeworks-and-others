<%--
  Created by IntelliJ IDEA.
  User: selen
  Date: 18/05/2022
  Time: 20:05
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ page import="domain.Topic" %>
<%@ page import="domain.User" %>
<%@ page import="java.util.List" %>
<%@ page import="java.util.Map" %>
<%@ page contentType="text/html;charset=UTF-8" %>
<html>
<head>
    <meta charset="UTF-8">
    <title>Forum</title>
    <script src="scripts/jquery-3.6.0.js"></script>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css">
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/js/bootstrap.min.js"></script>
</head>
<body>
<div class="container-fluid text-center">
    <%
        User user = (User) session.getAttribute("user");
        if (user == null) {
            response.sendRedirect("login");
            return;
        }
        Integer userId = user.getId();
        out.println("<h4>Hello there, " + ((User) request.getSession().getAttribute("user")).getUsername() + "!</h4>");
    %>
    <script>
        var sessionUserId = "<%=userId%>";
    </script>
    <div class="container-fluid text-left">
        <p>The following topics are in the system now: </p>
        <%
            @SuppressWarnings("unchecked") Map<Topic, User> topics = (Map<Topic, User>) request.getSession().getAttribute("topics");
            out.println("<ul class=\"elements\">");
            for (Map.Entry<Topic, User> topic : topics.entrySet()) {
                out.println("<li>" + topic.getKey().getName() + " - user: " + topic.getValue().getUsername() + " <button class='btn btn-primary' onClick=goToTopic(" + topic.getKey().getId() + ")>Go to this topic</button></li>");
            }
            out.println("</ul>");
        %>
    </div>

    <div class="add container-fluid text-left">
        <h4>Add a new topic</h4>
        <div class="input-field">
            <label for="topic" class="form-label">Name: </label>
            <input id="topic" name="topic" type="text" class="form-control">
        </div>
        <button class='btn btn-primary' onclick="addTopic()">Add Topic</button>
    </div>

    <button class='btn btn-primary m-5' onclick="logout()">LOGOUT</button>

</div>
</body>
<script src="scripts/main.js"></script>

</html>
