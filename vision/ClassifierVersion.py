import cv2
import numpy as np
import pickle
import configparser

class Img2Status:
    def __init__(self, scalars):
        sample_num = len(scalars)
        self.scalars = np.array(scalars).reshape(sample_num, 9)

        f = open("./SvmTrain/now.model", 'rb')
        self.clf = pickle.load(f)

        # do classification
        self.labels = self.clf.predict(self.scalars)
        self.ToStatus()
    def ToStatus(self):
        label2str = {}
        faces = ['U', 'R', 'F', 'D', 'L', 'B']
        for i in range(6):
            label2str[self.labels[i*9+4]] = faces[i]
            print(self.labels[i*9+4], faces[i])
        status = [label2str[i] for i in self.labels]
        self.status = "".join(status)
    def ToPics(self):
        color = [(255, 255, 255), (0, 0, 255), (0, 255, 0), (0, 255, 255), (0, 127, 255), (255, 0, 0)]
        face2color = dict(zip(range(6), color))

        anchor = [(0, 300), (300, 600), (300, 300), (600, 300), (300, 0), (300, 900)]

        pic = np.zeros((900, 1200, 3), dtype="uint8")

        cv2.namedWindow("pic", cv2.WINDOW_NORMAL)
        for i in range(6):
            print(self.status[9*i+4])
            for j in range(9):
                t_col = anchor[i][1] + 100*(j%3)
                t_row = anchor[i][0] + 100*(j//3)
                cv2.rectangle(pic, (t_col, t_row), (t_col+45, t_row+45), face2color[self.labels[9*i+j]], 6)
            cv2.imshow("pic", pic)
            cv2.waitKey()

        cv2.imshow("pic", pic)
        cv2.waitKey()

if __name__ == "__main__":
    from Pretreat import *
    import datetime


    config = configparser.ConfigParser()
    config.read("../configs/vision_pretreat.ini")
    
    pi_pic_root_path  = "../BackupSource/"
    pic_paths = [pi_pic_root_path+"%d.jpg"%i for i in range(4)]
    pics = []
    for i in pic_paths:
        img = cv2.imread(i)
        print(i)

        pics.append(img)
    
    starttime = datetime.datetime.now()
    pp = Pretreat(pics, config)
    result = pp.GetResult()
    for i in pp.perspectived_imgs:
        cv2.imshow("233", i[::,3])
        cv2.waitKey()
    ya = Img2Status(result)
    endtime = datetime.datetime.now()

    print("cost: ", (endtime-starttime))
    print(ya.status)
    ya.ToPics()