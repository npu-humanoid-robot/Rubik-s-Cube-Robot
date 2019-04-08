import cv2
import pickle
import numpy as np
from sklearn.svm import SVC
from sklearn.model_selection import train_test_split

class SvmTrain:
    def __init__(self, train_data, labels):
        self.train_data, self.test_data, self.train_label, self.test_label = train_test_split(train_data, labels, train_size=0.7)
        print(len(self.test_label))
        print(len(self.train_label))
        print(self.train_data.shape)

    def Train(self, save_path):
        self.classifier = SVC(C=0.8, kernel='linear', decision_function_shape='ovr')
        self.classifier.fit(self.train_data, self.train_label)

        f = open(save_path, 'wb')
        pickle.dump(self.classifier, f)
        f.close()
    def GetAccuracy(self):
        print(self.classifier.score(self.test_data, self.test_label))
if __name__ == "__main__":
    train_data = []
    train_label = []
    data_file = open("train_data.bin", 'rb')
    label_file = open("train_label.bin", 'rb')
    train_data = pickle.load(data_file)
    train_label = pickle.load(label_file)

    sample_num = len(train_data)

    train_data = np.array(train_data).reshape(sample_num, 9)
    print(train_data.shape)

    trainer = SvmTrain(train_data, train_label)
    trainer.Train("rbf.model")
    trainer.GetAccuracy()