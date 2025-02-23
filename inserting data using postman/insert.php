<?php
header("Access-Control-Allow-Origin: *"); 
header("Access-Control-Allow-Methods: GET"); 
header("Content-Type: application/json; charset=UTF-8"); 

// Database credentials
$host = "localhost";
$username = "root"; // Default XAMPP user
$password = ""; // Default XAMPP password (empty)
$database = "integrative1";

// Connect to MySQL
$conn = new mysqli($host, $username, $password, $database);

// Check connection
if ($conn->connect_error) {
    die(json_encode(["error" => "Connection failed: " . $conn->connect_error]));
}

// Read JSON input
$data = json_decode(file_get_contents("php://input"), true);

if (isset($data['name']) && isset($data['email']) && isset($data['age']) && isset($data['gender']) && isset($data['phoneNumber'])) {
    $name = $conn->real_escape_string($data['name']);
    $email = $conn->real_escape_string($data['email']);
    $age = intval($data['age']);
    $gender = $conn->real_escape_string($data['gender']);
    $phoneNumber = $conn->real_escape_string($data['phoneNumber']);

    // SQL Insert Query
    $sql = "INSERT INTO clients (name, email, age, gender, phoneNumber) VALUES ('$name', '$email', '$age', '$gender', '$phoneNumber')";

    if ($conn->query($sql) === TRUE) {
        echo json_encode(["message" => "User added successfully"]);
    } else {
        echo json_encode(["error" => "Error: " . $conn->error]);
    }
} else {
    echo json_encode(["error" => "Invalid input, all fields required"]);
}

// Close connection
$conn->close();
?>
