
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

def parseDataFromArduino(res):
  result = list(res.split(";"))
  return result

while(True):
  try:
    ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
    ser.reset_input_buffer()
    response = ser.readline()
    if response != b'':
      response = response.decode("utf-8")
      print(response)
      print(parseDataFromArduino(response))
      
  except:
    print("failed listening to ttyUSB0")

