<?php

$servername = "localhost";
$username = "<USERNAME>";
$password = "<PASSWORD>";
$dbname = "<DB_NAME>";

$botToken="<TOKEN>";
$website="https://api.telegram.org/bot".$botToken;

// Create connection to DB
$conn = mysqli_connect($servername, $username, $password, $dbname);
// Check connection to DB
if (!$conn) {
    die("Connection failed: " . mysqli_connect_error());
}
// Update table with GET values (if present in the URL)

if (!empty($_GET))
 {
    
	foreach ($_GET as $key => $value)
    {
		echo "aggiornamento:".$key." ".$value."<br>";
	}
    
// sql to update table

	$sql = "UPDATE SIRACUSA_PARK
	SET disponibili = $value
	WHERE nome = '$key';";

	if (mysqli_query($conn, $sql)) {
    	echo "Table updated successfully <br>";
	} else {
    	echo "Error updating table: " . mysqli_error($conn);
	}
}

//print the table with new data (if present in the URL) or the old table (if not)
$result = mysqli_query($conn,"SELECT * FROM SIRACUSA_PARK");

echo "<table border='1'>
<tr>
	<th>ID</th>
	<th>Parcheggio</th>
	<th>Posti disponibili</th>
</tr>";

$flag = 0; // Non ci sono parcheggi esauriti
$data= array();
while($row = mysqli_fetch_array($result))
{
$data[] = $row;
echo "<tr>";
echo "<td>" . $row['ID'] . "</td>";
echo "<td>" . $row['NOME'] . "</td>";
echo "<td>" . $row['DISPONIBILI'] . "</td>";
echo "</tr>";


	if($row['DISPONIBILI']==0)
    {
    	$msg .= $row['NOME']." : ". "ESAURITO\n";
    	$flag = 1; //C'è almeno un parcheggio con posti esauriti
    }
    else
    {
    	$msg .= $row['NOME']." : ". $row['DISPONIBILI']." posti disponibili"."\n";
    }
}
if($flag ==1)
	{
    	// Create connection to DB
		$conn = mysqli_connect($servername, $username, $password, $dbname);
		// Check connection to DB
		if (!$conn) {
		    die("Connection failed: " . mysqli_connect_error());
		}
        $result = mysqli_query($conn,"SELECT CHAT_ID FROM AGGIORNAMENTI");
        $data= array();
		while($row = mysqli_fetch_array($result)) 
        $data[] = $row;
        
       for($i=0; $i <count($data); $i++)
       {
       		$chatid = $data[$i]["CHAT_ID"];
            inviaMessaggio($chatid,$msg);
       }
      
        // Close connection to DB
		mysqli_close($conn);
    }

echo "</table>";


// Close connection to DB
mysqli_close($conn);

function inviaMessaggio($chat_id,$text)
{
	global $website;
	echo "website:".$website;
	$url = $website.'/sendMessage?chat_id='.$chat_id.'&text='.urlencode($text);
	file_get_contents($url);
}
?>