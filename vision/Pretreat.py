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

import numpy as np
import cv2
import configparser



class Pretreat:
    def __init__(self, raw_four_images, config):
        self.raw_four_images = raw_four_images  # raw images
        self.SetParams(config)      # get points from config objuect

        # Do pretreat
        self.DoPreproc()
        self.CutImage()
        self.GetSampleRectAvg()
    def GetResult(self):
        return self.sample_scalars
    def DoPreproc(self):
        for i in self.raw_four_images:
            i = cv2.GaussianBlur(i, (7, 7), 0)
            i = cv2.cvtColor(i, cv2.COLOR_BGR2HSV_FULL)
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
        return 
    
    def GetSampleRectAvg(self):
        # sum the scalar and get avg
        # at the same time to show the rect 
        self.sample_scalars = [] 
        for j in range(6):
            for i in range(9):
                t_sum = np.ndarray([3,], dtype='float64')
                rect_cols = 100*(i%3) + 45
                rect_rows = 100*(i//3) + 45
                for row_i in range(10):
                    for col_i in range(10):
                        t_sum += self.perspectived_imgs[j][rect_rows+row_i, rect_cols+col_i]
                t_sum /= 100

                cv2.rectangle(self.perspectived_imgs[j], (rect_cols, rect_rows), (rect_cols+10, rect_rows+10), (0, 0, 0), 5)
                self.sample_scalars.append(t_sum)
        # return them
        return 

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
