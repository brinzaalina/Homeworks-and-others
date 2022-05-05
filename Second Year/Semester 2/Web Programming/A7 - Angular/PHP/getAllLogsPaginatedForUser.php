<?php

header('Access-Control-Allow-Origin: *');

$conn = new mysqli("localhost", "root", "", "logreports");
if ($conn->connect_error)
{
    die("Connection failed: " . $conn->connect_error);
}

$pageSize = $_GET["pageSize"];
$page = $_GET["page"];
$user = $_GET["user"];
$offset = ($page - 1) * $pageSize;

$query = "SELECT * FROM logreports.logs WHERE user = ? LIMIT ?, ?";
$statement = $conn->prepare($query);
$statement->bind_param("sss", $user, $offset, $pageSize);
$statement->execute();
$queryResult = $statement->get_result();

$logs = array();

while($row = $queryResult->fetch_assoc()) {
    $log = array();
    array_push($log, $row["id"]);
    array_push($log, $row["type"]);
    array_push($log, $row["severity"]);
    array_push($log, $row["date"]);
    array_push($log, $row["user"]);
    array_push($log, $row["logtext"]);

    array_push($logs, $log);
}

echo json_encode($logs);

$conn->close();

?>