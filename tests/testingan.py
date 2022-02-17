import serial
import time
import re 
cmd = "z"
ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
ser.reset_input_buffer()
for x in range(15):
    # f = "{cmd}".format(cmd=cmd) # cmd ay string na "z"
    # print(b"z") #b"z" pag pinrint is nagiging b'z'
    command_string = "x"
    command = bytes(command_string, 'utf-8')
    ser.write(command)
    response = ser.readline()
    time.sleep(1)
    res = str(response)
    res = re.sub('[\\\\br''n'']', '', res)
    res = res.replace("'","")
    if res != "''" and res!= "":
        print(type(res))
        print(res)
        print(int(res))
        print(res)
print("unidentifiable item.")


# test_string = "There are 24444 apples for 4 persons"
# res = [int(i) for i in test_string.split() if i.isdigit()]
  
# # print result
# print(type(res[0]))