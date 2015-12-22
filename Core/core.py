# 20:15:05:11:32:44 - itead - radar
# 30:14:11:21:15:80 - HC-06 - redbot
import time
from bluetooth import *
import matplotlib.pyplot as plt

# Generate the master table
# masterTable = [[0 for x in range(10)] for x in range(10)] 
all_results_x = list()
all_results_y = list()

WAIT_TIME = 10
RADAR_MAC = "20:15:05:11:32:44"
REDBOT_MAC = "30:14:11:21:15:80"
ITERATIONS_AMOUNT = 3

def scan():
	# Connect
	print "Connecting to Radar"
	sock=BluetoothSocket( RFCOMM )
	sock.connect((RADAR_MAC, 1))

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

def move(direction):
	print "Connecting to Redbot"
	sock=BluetoothSocket( RFCOMM )
	sock.connect((REDBOT_MAC, 1))

	# Send data and wait for output
	res = sock.send("go")
	# data = ""
	# while True:
	# 	data += sock.recv(1024)
	# 	if data is "1" or data is "0" :
	# 		break

	# Parse result
	
	# Output result and close connection
	sock.close()

def stopRedBot():
	sock=BluetoothSocket( RFCOMM )
	sock.connect((REDBOT_MAC, 1))

	# Send data and wait for output
	res = sock.send("stop")
	sock.close()


def calculateMove(coordinates):
	pass

def wait():
	print "Waiting..."
	time.sleep(WAIT_TIME)

def saveToMasterList(x,y):
	all_results_x.append(x)
	all_results_y.append(y)

def generateGraph():
	area = 3.1416 * 10 ** 2
	plt.scatter(all_results_x, all_results_y, s=area, alpha=0.5)
	plt.show()


# Main iteration 
for item in range(0,ITERATIONS_AMOUNT):

	# stopRedBot()
	res = scan()
	if res:
		print res[0]
		saveToMasterList(res[0]["x"], res[0]["y"])
	# move()
	# wait()

generateGraph()

