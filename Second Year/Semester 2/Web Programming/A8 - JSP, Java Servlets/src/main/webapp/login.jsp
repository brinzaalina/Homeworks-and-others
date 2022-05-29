<%--
  Created by IntelliJ IDEA.
  User: selen
  Date: 18/05/2022
  Time: 15:32
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" %>
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>Login Forum</title>
  <script src="scripts/jquery-3.6.0.js"></script>
  <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css">
  <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/js/bootstrap.min.js"></script>
</head>
<body>
<div class="container-fluid text-center">
  <form action="login" method="post">
    <div class="input-field mb-5 mt-5">
      <label for="username" class="form-label">Username:</label>
      <input id="username" name="username" type="text" class="form-control">
    </div>
    <div class="input-field mb-5 mt-5">
      <label for="password" class="form-label">Password:</label>
      <input id="password" name="password" type="password" class="form-control">
    </div>
    <%
      String error = (String) session.getAttribute("error");
      if (error != null) {
        out.println("<p class=\"alert alert-danger\" role=\"alert\">" + error + "</p>");
      }
    %>
    <div class="m-5">
      <button type="submit" class="btn btn-primary">Login</button>
    </div>
  </form>
</div>
</body>
</html>
