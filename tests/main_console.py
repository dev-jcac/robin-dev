import mysql.connector
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
while(True):
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
        points = 0
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
            points = 0
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
        