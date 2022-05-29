<%--
  Created by IntelliJ IDEA.
  User: selen
  Date: 18/05/2022
  Time: 20:06
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ page import="domain.User" %>
<%@ page import="domain.Topic" %>
<%@ page import="domain.Comment" %>
<%@ page import="java.util.List" %>
<%@ page import="java.util.Objects" %>
<%@ page contentType="text/html;charset=UTF-8" %>

<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Forum post</title>
    <script src="scripts/jquery-3.6.0.js"></script>
    <link rel="stylesheet" href="styles/topic.css">
    <script src="scripts/topic.js"></script>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css">
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/js/bootstrap.min.js"></script>
</head>
<body>
<div class="container-fluid text-center">
    <%
        User user = (User) request.getSession().getAttribute("user");
        if (user == null) {
            response.sendRedirect("login");
            return;
        }
        Topic currentTopic = (Topic) request.getSession().getAttribute("currentTopic");
        out.println("<h4> Hello there, " + user.getUsername() + "! Welcome to the forum topic: <b>" + currentTopic.getName() + "</b></h4>");
    %>

    <div class="comments">
        <h4>Comments:</h4>

        <%
            @SuppressWarnings("unchecked") List<Comment> commentList = (List<Comment>) request.getSession().getAttribute("comments");
            for (Comment comment: commentList) {
                String toPrint = "<div class=\"comment\">" + "<p>" + comment.getContent() + "</p>";
                if (Objects.equals(comment.getUserId(), user.getId())) {
                    toPrint += "<button class='btn btn-danger' onclick=\"deleteComment(" + comment.getId() + ")\">" + "DELETE" + "</button> </div>";
                } else {
                    toPrint += "</div>";
                }
                out.println(toPrint);
            }
        %>
    </div>
    <div class="add-div container-fluid">
        <div class="input-field">
            <label for="commentInput" class="form-label">Add a comment to the topic: </label>
            <input id="commentInput" type="text" class="form-control">
        </div>
        <button onclick="addComment()" class="btn btn-primary">Add Comment</button>
    </div>
    <button onclick="goBack()" class="btn btn-primary">Back</button>
</div>
</body>
</html>
