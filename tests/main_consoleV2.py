import mysql.connector
import requests
import serial
import time
from db_config import *
import string    
import random 
S = 10
mydb = mysql.connector.connect(
  host=localdb_host,
  user=localdb_user,
  password=localdb_password,
  database = localdb_database
)
mycursor = mydb.cursor()

class Connection:
    def internet():
        url = "https://www.google.com"
        timeout = 5
        try:
            request = requests.get(url, timeout=timeout)
            return True
        except (requests.ConnectionError, requests.Timeout) as exception:
            return False

    def remoteServer():
        url = "https://www.twitter.com" #replace
        timeout = 5
        try:
            request = requests.get(url, timeout=timeout)
            return True
        except (requests.ConnectionError, requests.Timeout) as exception:
            return False
    def advertisementServer():
        url = "https://www.facebook.com"#replace
        timeout = 5
        try:
            request = requests.get(url, timeout=timeout)
            return True
        except (requests.ConnectionError, requests.Timeout) as exception:
            return False

class Check:
    def ttyUSB0():
        try:
            ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
            ser.reset_input_buffer()
            return True
        except:
            return False

    def ttyUSB1():
        try:
            ser = serial.Serial('/dev/ttyUSB1', 9600, timeout=1)
            ser.reset_input_buffer()
            return True
        except:
            return False

class Identify:
    def ttyUSB0():
        try:
            ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
            ser.reset_input_buffer()
            for x in range(15):
                ser.write(b"a")
                response = ser.readline()
                time.sleep(1)
                res = str(response)
                if res != "b\'\'":
                    return res
            ttyUSB0_status = False
            return "unidentified"
        except:
            ttyUSB0_status = False
            return "No device connected"

    def ttyUSB1():
        try:
            ser = serial.Serial('/dev/ttyUSB1', 9600, timeout=1)
            ser.reset_input_buffer()
            for x in range(15):
                ser.write(b"a")
                response = ser.readline()
                time.sleep(1)
                res = str(response)
                if res != "b\'\'":
                    return res
            ttyUSB1_status = False
            return "unidentified"
        except:
            ttyUSB1_status = False
            return "No device connected"


print("internet connection: " + str(Connection.internet()))
print("connection to remote server: " +str(Connection.remoteServer()))
print("ttyUSB0: "+str(Identify.ttyUSB0()))
print("ttyUSB1: "+str(Identify.ttyUSB1()))
print("USB0 status: " +str(Check.ttyUSB0()))
print("USB1 status: " +str(Check.ttyUSB1()))


while(True):
    while(Connection.internet() and Connection.remoteServer() and Connection.advertisementServer() and Check.ttyUSB0() ):
        total_points = 0
        tally = 0
        points = 0
        tap = input('Touch anywhere to start... ')
        trans_id = ''.join(random.choices(string.ascii_uppercase + string.digits, k = S))
        print(trans_id)  
        tally_string = "SELECT recyclable_type FROM user_records WHERE transaction_id = '"+str(trans_id)+"' AND (recyclable_type = 'PET' OR recyclable_type = 'CAN')"
        mycursor.execute(tally_string)
        tally = mycursor.fetchall()
        print("=============================================")
        print("Total recyclables inserted:" +str(len(tally)))
        print("Accumulated points: "+str(total_points))
        mat_type = input('Kindly insert recyclable (PET/CAN/DONE)...')
        if mat_type == 'PET':
            points = 0.5
        elif mat_type == 'CAN':
            points = 0.2
        elif mat_type == 'DONE':
            print("=============================================")
            print("Thank you for using ROBIN!")
            print("=============================================")
        else:
            print("invalid material. try again")
            points = 0
        total_points += points
        insert_string = "INSERT INTO user_records (transaction_id, recyclable_type, points_given, time_inserted) VALUES ('"+str(trans_id)+"','"+str(mat_type)+"','"+str(points)+"',now())"
        mycursor.execute(insert_string)
        mydb.commit()
        while(mat_type != 'DONE'):
            tally_string = "SELECT recyclable_type FROM user_records WHERE transaction_id = '"+str(trans_id)+"' AND (recyclable_type = 'PET' OR recyclable_type = 'CAN')"
            mycursor.execute(tally_string)
            tally = mycursor.fetchall()
            print("=============================================")
            print("Total recyclables inserted:" +str(len(tally)))
            print("Accumulated points: "+str(round(total_points,2)))
            mat_type = input('Insert more recyclables (PET/CAN/DONE)...')
            if mat_type == 'PET':
                points = 0.5
            elif mat_type == 'CAN':
                points = 0.2
            elif mat_type == 'DONE':
                print("=============================================")
                print("Thank you for using ROBIN!")
                print("Total recyclables inserted:" +str(len(tally)))
                print("Accumulated points: "+str(round(total_points,2)))
                print("Scan QR-Code below or input the transaction ID to your mobile app.")
                print("*shows qr-code*")
                print("Transaction ID: "+str(trans_id))
                print("=============================================")
            else:
                print("invalid material. try again.")
                points = 0
            total_points += points
            insert_string = "INSERT INTO user_records (transaction_id, recyclable_type, points_given, time_inserted) VALUES ('"+str(trans_id)+"','"+str(mat_type)+"','"+str(points)+"',now())"
            mycursor.execute(insert_string)
            mydb.commit()

    print("Something is wrong")
        