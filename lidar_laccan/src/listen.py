#!/usr/bin/python

import serial

ser = serial.Serial('/dev/ttyACM0', 115200)

while True:
    data = ser.readline() #read a byte string
    string_n = data.decode() #decode byte string into Unicode
    string = string_n.rstrip() # remove \n and \r
    flt = float(string)        # convert string to float
    print(flt)