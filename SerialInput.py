import serial
import time
import csv

ser = serial.Serial('/dev/ttyACM0')#set to arduino serial port

ser.flushInput()#clears previous serial data

while True:
    try:
        #print("display")#testing
        ser_bytes = ser.readline()
        #print ("printing ser_bytes:")
        print(ser_bytes)
        #decoded_bytes = float(ser_bytes[0:len(ser_bytes)-2].decode("utf-8"))
        
        with open("/home/pi/Desktop/test_data.txt","a") as f:#set location as needed(where you want to save file and name of file)
            writer = csv.writer(f,delimiter=",")
            writer.writerow([ser_bytes])
    except:
        print("Keyboard Interrupt")
        break

        #have another way to stop program