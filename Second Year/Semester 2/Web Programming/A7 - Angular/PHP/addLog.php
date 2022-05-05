<?php

header('Access-Control-Allow-Origin: *');

session_start();
$conn = new mysqli("localhost", "root", "", "logreports");
if ($conn->connect_error)
{
    die("Connection failed: " . $conn->connect_error);
}
$user = $_GET["user"];

$type = $_GET["type"];
$severity = $_GET["severity"];
$date = $_GET["date"];
$message = $_GET["message"];

$query = "INSERT INTO logreports.logs(type, severity, date, user, logtext) VALUES (?, ?, ?, ?, ?)";
$statement = $conn->prepare($query);
$statement->bind_param("sssss", $type, $severity, $date, $user, $message);
$statement->execute();
$queryResult = $statement->get_result();
$conn->close();
?>