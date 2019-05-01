'''
Author: Alex Beng
Date: 2019.01.29->2019.01.30
'''

# 采样 rect 顺序
# rect_0---rect_1---rect_2
# |          |        |
# |          |        |
# rect_3---rect_4---rect_5
# |          |        |
# |          |        |
# rect_6---rect_7---rect_8

import copy
import numpy as np
import cv2
import configparser
import time
#from numba import jit

color_sample_point_col =[
    # U
    [45, 45, 45, 
     45, 45, 45, 
     45, 45, 45], 
    # R
    [45, 45, 45, 
     45, 45, 45, 
     45, 45, 45],
    # F
    [45, 45, 45, 
     45, 45, 45, 
     45, 45, 45],
    # D
    [45, 45, 45, 
     45, 45, 45, 
     45, 45, 45],
    # L
    [45, 45, 45, 
     60, 45, 30, 
     45, 45, 45],
    # B
    [45, 45, 45, 
     60, 45, 30, 
     45, 45, 45],
]

color_sample_point_row =[
    # U
    [45, 45, 45, 
     45, 45, 45, 
     45, 45, 45], 
    # R
    [45, 45, 45, 
     45, 45, 45, 
     45, 45, 45],
    # F
    [45, 45, 45, 
     45, 45, 45, 
     45, 45, 45],
    # D
    [45, 60, 45, 
     45, 45, 45, 
     45, 30, 45],
    # L
    [45, 45, 45, 
     45, 45, 45, 
     45, 45, 45],
    # B
    [45, 45, 45, 
     45, 45, 45, 
     45, 45, 45],
]

class Pretreat:
    def __init__(self,  config):
        self.SetParams(config)      # get points from config objuect

        # 激活jit🙃，别问，问了就是玄学
        scalars = np.array([1,1,1]).reshape(1, 1, 3).astype(np.uint8)
        cv2.warpPerspective(scalars,
                        self.trans_mats[0],
                        (self.perspectived_width, self.perspectived_width)
                )
        cv2.GaussianBlur(scalars, (5, 5), 0)
        t_lab = cv2.cvtColor(scalars, cv2.COLOR_BGR2LAB)
        t_hsv = cv2.cvtColor(scalars, cv2.COLOR_BGR2HSV_FULL)
        np.concatenate((t_hsv, t_lab), axis=2)
        self.sample_scalars = []
        self.sample_scalars.append(scalars)
        self.To9Dim()
        del self.sample_scalars
    def GetResult(self, raw_four_images_):
        self.raw_four_images = raw_four_images_

        # starttime = time.time()
        self.DoPreproc()
        # endtime = time.time()
        # print("p1 cost:", (endtime-starttime))

        # starttime = time.time()
        self.CutImage()
        # endtime = time.time()
        # print("p2 cost:", (endtime-starttime))

        # starttime = time.time()
        self.GetSampleRectAvg()
        # endtime = time.time()
        # print("p3 cost:", (endtime-starttime))

        # starttime = time.time()
        self.To9Dim()
        # endtime = time.time()
        # print("p4 cost:", (endtime-starttime))


        return self.sample_scalars
    def DoPreproc(self):
        for i in range(len(self.raw_four_images)):
            self.raw_four_images[i] = cv2.GaussianBlur(self.raw_four_images[i], (5, 5), 0)    # make the scalars up to 9 dimension
#    @jit
    def To9Dim(self):
        for i in range(len(self.sample_scalars)):

            # starttime = time.time()
            # for j in range(100000):
            #     t_lab = cv2.cvtColor(self.sample_scalars[i], cv2.COLOR_BGR2LAB)
            #     t_hsv = cv2.cvtColor(self.sample_scalars[i], cv2.COLOR_BGR2HSV_FULL)
            t_lab = cv2.cvtColor(self.sample_scalars[i], cv2.COLOR_BGR2LAB)
            t_hsv = cv2.cvtColor(self.sample_scalars[i], cv2.COLOR_BGR2HSV_FULL)
            # endtime = time.time()
            # print("c2 cost:", (endtime-starttime))

            # print(t_hsv[0][0])
            # print()

            # starttime = time.time()
            # for j in range(100000):
            #     # print(type(self.sample_scalars[i][0][0]), self.sample_scalars[i][0][0].shape)
                 
            #     ttt = np.vstack((self.sample_scalars[i][0][0], t_hsv[0][0], t_lab[0][0]))
            self.sample_scalars[i] = np.concatenate((self.sample_scalars[i], t_hsv, t_lab), axis=2)
            # endtime = time.time()
            # print("circle cost:", (endtime-starttime))
            # print()
    def CutImage(self):
        # do 透视变换
        self.perspectived_imgs = []
        for i in range(4):# 后两张要特别处理
            if i < 2:
                t_idx = 0
            else:
                t_idx = 1
            self.perspectived_imgs.append(
                cv2.warpPerspective(self.raw_four_images[t_idx],
                                    self.trans_mats[i],
                                    (self.perspectived_width, self.perspectived_width)
                )
            )
        self.perspectived_imgs.append(
            cv2.warpPerspective(self.raw_four_images[2],
                                self.trans_mats[1],
                                (self.perspectived_width, self.perspectived_width)
            )
        )
        self.perspectived_imgs.append(
            cv2.warpPerspective(self.raw_four_images[3],
                                self.trans_mats[2],
                                (self.perspectived_width, self.perspectived_width)
            )
        )
        # 改顺序
        self.perspectived_imgs[2], self.perspectived_imgs[4] = self.perspectived_imgs[4], self.perspectived_imgs[2]
    def GetSampleRectAvg(self):
        # sum the scalar and get avg
        # at the same time to show the rect 
        self.sample_scalars = [] 
        for j in range(6):
            for i in range(9):
                rect_cols = 100*(i%3)  + color_sample_point_col[j][i]
                rect_rows = 100*(i//3) + color_sample_point_row[j][i]

                t_sum = (self.perspectived_imgs[j][rect_rows:rect_rows+10, rect_cols:rect_cols+10].sum(axis=1).sum(axis=0)/100.0).reshape(1,1,3)
                t_sum = t_sum.astype(np.uint8)

                cv2.rectangle(self.perspectived_imgs[j], (rect_cols, rect_rows), (rect_cols+10, rect_rows+10), (0, 0, 0), 5)
                self.sample_scalars.append(t_sum)

    # params related
    # store & read can be done by the module :-)
    def SetParams(self, params):
        # set the trans'matrix
        self.trans_mats = []
        for i in range(4):
            self.trans_mats.append(np.eye(3))
            section = 'tran_mat_' + str(i)
            for j in range(9):
                key = 'element_' + str(j)
                self.trans_mats[i][int(j/3)][int(j%3)] = float(params[section][key])

        # set perspectived size
        self.perspectived_width = int(params['perspectived_size']['width'])
        return 

if __name__ == "__main__":
    # test set params
    config = configparser.ConfigParser()
    config.read("../configs/vision_pretreat.ini")

    _ = []
    t_233 = Pretreat(_, config)
    print(t_233.trans_mats[0])
    print(t_233.trans_mats[1])
    print(t_233.trans_mats[2])
    print(t_233.trans_mats[3])
    t_233.CutImage()
    for i in range(6):
        cv2.imshow("233", t_233.perspectived_imgs[i])
        cv2.waitKey()
