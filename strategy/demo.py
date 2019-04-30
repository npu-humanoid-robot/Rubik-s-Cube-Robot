import os
import numpy as np
import serial
import cv2
import configparser
import pickle
import time

import sys
sys.path.insert(0, "../")
from vision.Pretreat import Pretreat 
from vision.KmeansVersion import Img2Status



def rotate():
    ser = serial.Serial("/dev/ttyAMA0",115200)
    hex_str = bytes.fromhex('ff ff 03 59 6d ae 74 00')
    ser.write(hex_str)
    ser.close()

def make_sure_open(idx):
    cp = cv2.VideoCapture(idx)
    __, frame = cp.read()
    if not __:
        __, frame = cp.read()
    return cp

def getFinalResult(str_result):
    #java_res = os.popen("cd ..\n cd min2phase-dev-min\n java demo {0} | ../transform/build/main\n cd ..\n cd strategy".format(str_result))
    #test = "RLUFURBDLDULLRBLRFUFBRFFUFDRRFDDDDDDUULBLBBBFFUBLBURLR"
    java_res = os.popen("cd ..\n cd min2phase-dev-min\n java demo {0} | ../transform/build/transform".format(str_result))
    print(java_res.read())
    return java_res.read()


def main():
    # take-lots-time part
    cam_idx_file = open("../BackupSource/cam_idx.bin", 'rb')
    cam_idx_list = pickle.load(cam_idx_file)

    up_cam_cp = make_sure_open(cam_idx_list[0])
    dw_cam_cp = make_sure_open(cam_idx_list[1])

    config = configparser.ConfigParser()
    config.read("../configs/vision_pretreat.ini")

    pretreater = Pretreat(config)
    solver = Img2Status()

    ################
    # Ready Signal #
    ################
    print("Ready?", end="")
    input()

    # stage-1 image
    pics = []
    __, frame = up_cam_cp.read()
    pics.append(frame)
    __, frame = dw_cam_cp.read()
    pics.append(frame)

    ################
    # Begin Signal #
    ################
    print("Begin?", end="")
    input()

    # stage-2 image
    rotate()
    time.sleep(20)
    __, frame = up_cam_cp.read()
    pics.append(frame)
    __, frame = dw_cam_cp.read()
    pics.append(frame)

    # image process part
    color_vectors = pretreater.GetResult(pics)
    solver.GetResult(color_vectors)

    # min2phase part
    cube_status = solver.status
    moves = getFinalResult(cube_status)


    for i in range(4):
        cv2.imwrite("../BackupSource/%d.jpg"%(i+4), pics[i])

if __name__ == '__main__':
    main()