# Receive data from Arduino and write them on the database 

import time
import serial
import requests

url = 'https://smartpark.altervista.org/db_update.php'

def main():
	port = serial.Serial("/dev/ttyACM0", baudrate=9600, timeout=None)	
	while True:
		line = port.readline()	
		data=int(line)
		payload = {'Molo': data}
		try:
			r = requests.get(url,params=payload)
			if r.status_code == 200: 
				print " [ OK ] Database updated successfully." 
		except requests.exceptions.RequestException as e:
			print " [ FAIL ] Database not updated." 
			print e
			pass	

		print("%d" % data)
		time.sleep(0.01)
		
if __name__ == "__main__":
	main()

