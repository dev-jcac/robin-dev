
import mysql.connector
from db_config import *
import string    
import random 

import requests
import serial
import time
import re

mydb = mysql.connector.connect(
  host=localdb_host,
  user=localdb_user,
  password=localdb_password,
  database = localdb_database
)
mycursor = mydb.cursor()

class Identify():
    def USBPORT(a):
        b=a
        try:
            ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
            ser.reset_input_buffer()
            for x in range(15):
                ser.write(b"a")
                response = ser.readline()
                time.sleep(1)
                res = str(response)
                if b in res:
                    return "/dev/ttyUSB0"
            return "/dev/ttyUSB1"
        except:
            print("FAILED to identify usb ports")
print("Booting up....")
arduino_for_sensor = Identify.USBPORT("sensor")
# print(arduino_for_sensor)


def Arduino(ttyport, command):
    port = ttyport
    cmd = bytes(command, 'utf-8')
    # try:
    #     ser = serial.Serial(port, 9600, timeout=1)
    #     ser.reset_input_buffer()
    #     for x in range(25):
    #         ser.write(cmd)
    #         response = ser.readline()
    #         time.sleep(1)
    #         res = str(response)
    #         print("Classifying...")
    #         if "PET" in res:
    #             return "PET"
    #         elif "CAN" in res:
    #             return "CAN"
    #     return "unidentifiable item."        
    # except:
    #     print("FAILED SENDING DATA TO USB")
    try:
        ser = serial.Serial(port, 9600, timeout=1)
        ser.reset_input_buffer()
        for x in range(15):
            ser.write(cmd)
            response = ser.readline()
            
            time.sleep(1)
            res = str(response)
            res = re.sub('[\\\\br''n'']', '', res)
            res = res.replace("'","")
            print(res)
            if command == "x" and res != "''" and res!= "" and res.isdecimal():
                return res
            elif command == "z" and res != "''" and res!= "":
                return res
    except:
        print("FAILED SENDING DATA TO USB")
S = 10
print("Done!")
while(True):
    total_points = 0
    tally = 0
    points = 0
    tap = input('Touch anywhere to start... ')
    trans_id = ''.join(random.choices(string.ascii_uppercase + string.digits, k = S))
    print(trans_id)
    # mat_type = input('Kindly insert recyclable (PET/CAN/DONE)...')
    print("Kindly insert recyclable (PET/CAN/DONE)...")
    d = 12
    while(d >=11):
        d = int(Arduino(arduino_for_sensor, "x"))
    print("Recyclable Detected!")
    diameter = 12-d
    print("Diameter: "+str(diameter)+" cm.")
    print("Adjusting Z-axis...")
    time.sleep(1)
    print("Classifying...")
    mat_type = Arduino(arduino_for_sensor, "z")
    print(mat_type)
    
    while (mat_type!='DONE'):
        
        if mat_type == 'PET':
            points = 0.5
        elif mat_type == 'CAN':
            points = 0.2
        else:
            print("invalid material. try again.")
            points = 0
        total_points += points
        insert_string = "INSERT INTO user_records (transaction_id, recyclable_type, points_given, time_inserted) VALUES ('"+str(trans_id)+"','"+str(mat_type)+"','"+str(points)+"',now())"
        mycursor.execute(insert_string)
        mydb.commit()
        tally_string = "SELECT recyclable_type FROM user_records WHERE transaction_id = '"+str(trans_id)+"' AND (recyclable_type = 'PET' OR recyclable_type = 'CAN')"
        mycursor.execute(tally_string)
        tally = mycursor.fetchall()
        print("=============================================")
        print("Total recyclables inserted:" +str(len(tally)))
        print("Accumulated points: "+str(total_points))
        print("Kindly insert recyclable (PET/CAN/DONE)...")
        d = 12
        while(d >=11):
            d = int(Arduino(arduino_for_sensor, "x"))
        print("Recyclable Detected!")
        diameter = 12-d
        print("Diameter: "+str(diameter)+" cm.")
        print("Adjusting Z-axis...")
        time.sleep(1)
        print("Classifying...")
        mat_type = Arduino(arduino_for_sensor, "z")
        print(mat_type)
    print("=============================================")
    print("Thank you for using ROBIN!")
    if total_points>0:
        print("Total recyclables inserted:" +str(len(tally)))
        print("Accumulated points: "+str(round(total_points,2)))
        print("Scan QR-Code below or input the transaction ID to your mobile app.")
        print("*shows qr-code*")
        print("Transaction ID: "+str(trans_id))
    print("=============================================")