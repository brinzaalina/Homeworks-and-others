<?php

header('Access-Control-Allow-Origin: *');
$conn = new mysqli("localhost", "root", "", "logreports");
if ($conn->connect_error)
{
    die("Connection failed: " . $conn->connect_error);
}
if (isset($_GET["user"]) && isset($_GET["logId"])) {
    $user = $_GET["user"];
    $logId = $_GET["logId"];
    $query = "SELECT user FROM logreports.logs where id = ? LIMIT 1";
    $statement = $conn->prepare($query);
    $statement->bind_param("s", $logId);
    $statement->execute();
    $queryResult = $statement->get_result();
    $result = mysqli_num_rows($queryResult);

    if($result != 0) {
        $row = $queryResult->fetch_row();
        if (!(is_null($row))) {
            $userDatabase = $row[0];
            if($userDatabase != $user)
            {
                echo "Invalid delete: current user does not have the permission to delete this log report!";
            }
            else{
                $query = "DELETE FROM logreports.logs WHERE id = ?";
                $statement = $conn->prepare($query);
                $statement->bind_param("s", $logId);
                $statement->execute();
                $queryResult = $statement->get_result();
                $conn->close();
                echo "";
            }
        } else {
            echo "The log does not exist";
        }
    } else {
        echo "The log id does not exist!";
    }
}
?>