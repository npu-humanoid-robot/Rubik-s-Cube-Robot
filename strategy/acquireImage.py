
import numpy as np
import cv2
import time
import serial

def getImage(id):
    capture = cv2.VideoCapture(id)
    #cv2.namedWindow("cube")
    while True:
        valid, frame = capture.read()
        if not valid:
            continue
        else:
            #cv2.imshow("c",frame)
            #cv2.imwrite("test" + str(id) + ".jpg",frame)
            return frame


def rotate():
    ser = serial.Serial("/dev/ttyAMA0",921600)
    hex_str = bytes.fromhex('ff ff 03 59 6d ae 74 00')
    ser.write(hex_str)
    ser.close()


def main():
    result = []

    result.append(getImage(0))
    result.append(getImage(1))
    #rotate()
    #time.sleep(2)
    result.append(getImage(0))
    result.append(getImage(1))
    

    return result

    
    #print("hello world")



if __name__ == "__main__":
    main()