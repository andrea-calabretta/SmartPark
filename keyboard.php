<?php
ini_set('error_reporting', E_ALL);
$servername = "localhost";
$username = "<USERNAME>";
$password = "<PASSWORD>";
$dbname = "<DB_NAME>";

$botToken="<TOKEN>";
$website="https://api.telegram.org/bot".$botToken;


$FilejSON = file_get_contents("php://input"); //webhook
$FilejSON= json_decode($FilejSON,TRUE);

$NomeUtente = $FilejSON["message"]["chat"]["first_name"]; 
$chatId = $FilejSON["message"]["chat"]["id"];
$Message = $FilejSON["message"]["text"];

switch ($Message) {
	case '/start':
    	
		$msg= "Ciao $GLOBALS[NomeUtente],\n"."sono il chatbot dei parcheggi di Siracusa.\n"
        ."Cosa posso fare per te? \n(ATTENZIONE: Versione beta con dati fittizi)\n";
		visualizzaTastiera($chatId,$msg);
		break;
    case 'Situazione attuale':
        // Create connection to DB
		$conn = mysqli_connect($servername, $username, $password, $dbname);
		// Check connection to DB
		if (!$conn) {
		    die("Connection failed: " . mysqli_connect_error());
		}
        $result = mysqli_query($conn,"SELECT * FROM SIRACUSA_PARK");
        $data= array();
		while($row = mysqli_fetch_array($result)) 
        $data[] = $row;
        print_r($data);
        // Close connection to DB
		mysqli_close($conn);
        
        foreach ($data as $park)
        {
    		$msg .= $park['NOME']." : ". $park['DISPONIBILI']." posti disponibili"."\n";
		}
        
        visualizzaTastiera($chatId,$msg);
		break;
    case 'Ricevi aggiornamenti':
    	$msg_succ = "Aggiornamenti: ATTIVATI.\n\n"."Riceverai una notifica ogni volta che un parcheggio sta per esaurire oppure ha appena esaurito i propri posti disponibili.";
       // Create connection to DB
		$conn = mysqli_connect($servername, $username, $password, $dbname);
		if (!$conn) {
		    die("Connection failed: " . mysqli_connect_error());
		}
       $sql = "INSERT INTO AGGIORNAMENTI VALUES('$NomeUtente', $chatId);";
       // Check connection to DB
        if (mysqli_query($conn, $sql)) {
    	visualizzaTastiera($chatId,$msg_succ);
		} else {
    		visualizzaTastiera($chatId,"Aggiornamenti: Errore nell'attivazione.");
		}
        // Close connection to DB
		mysqli_close($conn);
        
        visualizzaTastiera($chatId,$msg);
        break;
    case 'Interrompi aggiornamenti':
       // Create connection to DB
		$conn = mysqli_connect($servername, $username, $password, $dbname);
		// Check connection to DB
		if (!$conn) {
		    die("Connection failed: " . mysqli_connect_error());
		}
       $sql = "DELETE FROM AGGIORNAMENTI WHERE CHAT_ID = $chatId;";
       
        if (mysqli_query($conn, $sql)) {
    	visualizzaTastiera($chatId,"Aggiornamenti: DISATTIVATI.");
		} else {
    		visualizzaTastiera($chatId,"Aggiornamenti: Errore nella disattivazione.");
		}
        // Close connection to DB
		mysqli_close($conn);
        
        visualizzaTastiera($chatId,$msg);
        break;
	default:
    	
		$msg= "Comando non disponibile.\n\nScegli una delle opzioni del Menù.";
	    
        visualizzaTastiera($chatId,$msg);
		break;
}


function inviaMessaggio($chat_id,$text)
{
	global $website;
	echo "website:".$website;
	$url = $website.'/sendMessage?chat_id='.$chat_id.'&text='.urlencode($text);
	file_get_contents($url);
}

function visualizzaTastiera($chat_id,$text)
{
	global $website;
	
	$tastiera = '&reply_markup={"keyboard":[["Situazione%20attuale"],["Ricevi%20aggiornamenti"],["Interrompi%20aggiornamenti"]],"one_time_keyboard":true}';
	$url = $website.'/sendMessage?chat_id='.$chat_id.'&text='.urlencode($text).$tastiera;
	file_get_contents($url);
}

?>