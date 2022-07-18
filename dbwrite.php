

<?php



    $host = "localhost";		         // host = localhost because database hosted on the same server where PHP files are hosted
    $dbname = "IOT";              // Database name
    $username = "root";		// Database username
    $password = "";	        // Database password


// Establish connection to MySQL database
$conn = new mysqli($host, $username, $password, $dbname);


// Check if connection established successfully
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

else { echo "Connected to mysql database. "; }

   
// Get date and time variables
   
    
// If values send by NodeMCU are not empty then insert into MySQL database table

  if(!empty($_POST['sendval']) && !empty($_POST['sendval2']) )
    {
		$val = $_POST['sendval'];
                $va2 = $_POST['sendval2'];


// Update your tablename here
	        $sql = "INSERT INTO sensordata (val, va2) VALUES ('".$val."','".$va2."')"; 
 


		if ($conn->query($sql) === TRUE) {
		    echo "Values inserted in MySQL database table.";
		} else {
		    echo "Error: " . $sql . "<br>" . $conn->error;
		}
	}


// Close MySQL connection
$conn->close();



?>
