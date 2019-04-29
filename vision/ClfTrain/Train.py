import cv2
import pickle
import numpy as np
from sklearn.svm import SVC
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import scale
from sklearn.svm import LinearSVC
from sklearn.tree import DecisionTreeClassifier
from sklearn.ensemble import RandomForestClassifier
from sklearn.neighbors import KNeighborsClassifier
from sklearn.ensemble import GradientBoostingClassifier, AdaBoostClassifier
from sklearn.neural_network import MLPClassifier
from sklearn.cluster import KMeans


class SvmTrain:
    def __init__(self, train_data, labels):
        self.train_data, self.test_data, self.train_label, self.test_label = train_test_split(train_data, labels, train_size=0.7, random_state=1)
        # self.train_data = scale(self.train_data)
        # self.test_data = scale(self.test_data)
        
        print(len(self.test_label))
        print(len(self.train_label))
        print(self.train_data.shape)
        
    def Train(self, save_path):
        print("want to train on the old model ?(y/n)")
        ans = input()
        if ans in ['y', 'Y']:
            f = open("./now.model", 'rb')
            self.classifier = pickle.load(f)
        else:
            # self.classifier = KMeans(n_clusters=6)
            # self.classifier = AdaBoostClassifier()
            # self.classifier = MLPClassifier(hidden_layer_sizes=(100, 100, 100)) 
            # self.classifier = GradientBoostingClassifier()
            # self.classifier = KNeighborsClassifier(n_neighbors=5)
            # self.classifier = RandomForestClassifier()
            # self.classifier = DecisionTreeClassifier()
            self.classifier = SVC(kernel='linear', decision_function_shape='ovr')
            # self.classifier = LinearSVC()

        self.classifier.fit(self.train_data, self.train_label)
        # self.classifier.fit(self.train_data)

        f = open(save_path, 'wb')
        pickle.dump(self.classifier, f)
        f.close()
    def GetAccuracy(self):
        print(self.classifier.score(self.train_data, self.train_label))
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
    trainer.Train("now.model")
    trainer.GetAccuracy()