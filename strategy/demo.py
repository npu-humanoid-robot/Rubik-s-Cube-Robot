import os
import numpy as np
import acquireImage
import cv2
import configparser
import time

import sys
#sys.path.append("../")
sys.path.insert(0, "../")
from vision.Pretreat import Pretreat 
from vision.KmeansVersion import Img2Status



def getImageResut():
    return acquireImage.main()


def getColorResult(pics):
    config = configparser.ConfigParser()
    config.read("../configs/vision_pretreat.ini")

    pretreat = Pretreat(pics, config)
    color_scalars = pretreat.GetResult()
    
    kmeans_proc = Img2Status(color_scalars)
    str_result = kmeans_proc.ToStatus()

    return str_result

def getFinalResult(str_result):
    #java_res = os.popen("cd ..\n cd min2phase-dev-min\n java demo {0} | ../transform/build/main\n cd ..\n cd strategy".format(str_result))
    #test = "RLUFURBDLDULLRBLRFUFBRFFUFDRRFDDDDDDUULBLBBBFFUBLBURLR"
    java_res = os.popen("cd ..\n cd min2phase-dev-min\n java demo {0} | ../transform/build/transform".format(str_result))
    print(java_res.read())
    return java_res.read()



def main():
    pics = getImageResut()


    #str_result =''
    final_result = getFinalResult(str_result)

    
    cv2.imwrite("a.jpg",pics[0])
    cv2.imwrite("b.jpg",pics[1])
    cv2.imwrite("c.jpg",pics[2])
    cv2.imwrite("d.jpg",pics[3])

    



if __name__ == '__main__':
    main()