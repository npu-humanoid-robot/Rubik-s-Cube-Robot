import cv2
import glob
import pickle
import numpy as np
import configparser
from sklearn.svm import SVC

from Pretreat import *

class SvmTrain:
    def __init__(self, train_data, labels):
        self.train_data = train_data
        self.labels = labels
    def Train(self, save_path):
        classifier = SVC(kernel='linear')
        classifier.fit(self.train_data, self.labels)

        f = open(save_path, 'wb')
        pickle.dump(classifier, f)
        f.close()
        

class SvmPredict:
    def __init__(self, save_path):
        f = open(save_path, 'rb')
        self.classifer = pickle.load(f)
        f.close()
    
    def Predict2Status(self, scalar):
        self.labels = self.classifer.predict(scalar)
        self.label2str = {}
        faces = ['U', 'R', 'F', 'D', 'L', 'B']

        for i in range(6):
            self.label2str[labels[i*9+4]] = faces[i]
            print(labels[i*9+4], faces[i])
        
        status = [self.label2str[i] for i in labels]
        status = "".join(status)
        return status



if __name__ == "__main__":
    config = configparser.ConfigParser()
    config.read("../configs/vision_pretreat.ini")

    pic_path = "../BackupSource/*.jpg"
    pic_paths = [i for i in glob.glob(pic_path)]
    pics = []
    for i in pic_paths:
        print(i)
        img = cv2.imread(i)
        pics.append(img)

    pp = Pretreat(pics, config)
    train_data = pp.GetResult()

    t_list = []
    for i in range(6):
        tt_list = [i]*9
        t_list += tt_list
        print(t_list)
    labels = np.array(t_list)

    print(train_data)
    print(labels)

    trainer = SvmTrain(train_data, labels)
    trainer.Train("svm_linear.model")

    classifer = SvmPredict("svm_linear.model")
    result_str = classifer.Predict2Status(train_data)
    print(result_str)

    # label2str = {}
    # faces = ['U', 'R', 'F', 'D', 'L', 'B']

    # for i in range(6):
    #     label2str[labels[i*9+4]] = faces[i]
    #     print(labels[i*9+4], faces[i])
    
    # status = [label2str[i] for i in labels]
    # status = "".join(status)
    # print(status)
    