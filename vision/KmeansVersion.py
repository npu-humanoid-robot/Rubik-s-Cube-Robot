import cv2
import numpy as np
import glob
from sklearn.cluster import KMeans
from sklearn.decomposition import PCA
import configparser

from Pretreat import *

class Img2Status:
    def __init__(self, scalars):
        self.scalars = scalars 
        # for i in self.scalars:
        #     i = (i[1], i[2])
        self.Cluster()
        return 
    def Cluster(self):
        kmeans_cluster = KMeans(n_clusters=6)
        kmeans_cluster.fit(self.scalars)
        self.labels = kmeans_cluster.labels_
        return
    def ToStatus(self):
        label2str = {}
        faces = ['U', 'R', 'F', 'D', 'L', 'B']
        for i in range(6):
            label2str[self.labels[i*9+4]] = faces[i]
            print(self.labels[i*9+4], faces[i])

        status = [label2str[i] for i in self.labels]
        self.status = "".join(status)

    # turn status string to visual pics
    def ToPics(self):
        faces = ['U', 'R', 'F', 'D', 'L', 'B']
        color = [(255, 255, 255), (0, 0, 255), (0, 255, 0), (0, 255, 255), (0, 127, 255), (255, 0, 0)]
        face2color = dict(zip(faces, color))

        anchor = [(0, 300), (300, 600), (300, 300), (600, 300), (300, 0), (300, 900)]

        pic = np.zeros((900, 1200, 3), dtype="uint8")

        cv2.namedWindow("pic", cv2.WINDOW_NORMAL)
        for i in range(6):
            for j in range(9):
                t_col = anchor[i][1] + 100*(j%3)
                t_row = anchor[i][0] + 100*(j//3)
                cv2.rectangle(pic, (t_col, t_row), (t_col+45, t_row+45), face2color[self.status[6*i+j]], 6)
            cv2.imshow("pic", pic)
            cv2.waitKey()

        cv2.imshow("pic", pic)
        cv2.waitKey()

if __name__ == "__main__":
    config = configparser.ConfigParser()
    config.read("../configs/vision_pretreat.ini")
    
    pi_pic_root_path  = "../BackupSource/"
    pic_paths = [pi_pic_root_path+"%d.jpg"%i for i in range(4)]
    pics = []
    for i in pic_paths:
        img = cv2.imread(i)
        print(i)

        pics.append(img)

    pp = Pretreat(pics, config)
    result = pp.GetResult()

    # arr = np.array(result)
    # pca = PCA(n_components = 3)
    # result = pca.fit_transform(arr)

    # for i in pp.raw_four_images:
    #     cv2.imshow("raw four", i)
    #     cv2.waitKey()
    for i in pp.perspectived_imgs:
        cv2.imshow("single img", i[:,:,3])
        cv2.waitKey()
    ya = Img2Status(result)
    ya.Cluster()
    labels = ya.labels
    
    ya.ToStatus()
    for i in range(6):
        for j in range( 3):
            for k in range(3):
                print(ya.status[i*9+3*j+k], end=" ")
            print()
        print()
    print(ya.status)
    # ya.ToPics()
