#!/usr/bin/env python3
import requests
import serial
import time

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
        url = "https://www.twitter.com"
        timeout = 5
        try:
            request = requests.get(url, timeout=timeout)
            return True
        except (requests.ConnectionError, requests.Timeout) as exception:
            return False
    def advertisementServer():
        url = "https://www.facebook.com"
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

    while( Connection.internet() and Connection.remoteServer() and Connection.advertisementServer() and Check.ttyUSB0() and Check.ttyUSB1()):
        print("Operation mode")
        time.sleep(2)

    print("Something is wrong")
