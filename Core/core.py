# 20:15:05:11:32:44 - itead - radar
# 30:14:11:21:15:80 - HC-06 - redbot
from bluetooth import *
import time

# Generate the master table
masterTable = [[0 for x in range(10)] for x in range(10)] 


def scan():
	# Connect
	print "Connecting to ITEAD"
	sock=BluetoothSocket( RFCOMM )
	sock.connect(("20:15:05:11:32:44", 1))

	# Send data and wait for output
	res = sock.send('r')
	data = ""
	while True:
		data += sock.recv(1024)
		if 'end' in data :
			break

	# Parse result
	table = list()
	for row in data.split("\n"):
		rowToInsert = list()
		for column in row.split(","):
			rowToInsert.append(column)

		try:
			table.append({ 
				"degrees": 	float(rowToInsert[0]),
				"x" : 		float(rowToInsert[1]),
				"y": 		float(rowToInsert[2])
			})
		except:
			pass #print "Table processing done."

	# Output result and close connection
	print(table)
	sock.close()
	return table

def move():
	pass

def calculateMove():
	pass

# Waits for 30 seconds
def wait():
	print "Waiting for 30 secs..."
	time.sleep(30)


while True:
	scan()
	wait()