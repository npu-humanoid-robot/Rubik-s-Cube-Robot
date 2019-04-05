from Pretreat import *

import glob
from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
from sklearn.decomposition import PCA

if __name__ == "__main__":
    # load raw pics and config 
    pic_path = "../BackupSource/*.jpg"
    pic_paths = [i for i in glob.glob(pic_path)]
    pics = []
    for j in pic_paths:
        i = cv2.imread(j)
        print(j)

        pics.append(i)
    
    config = configparser.ConfigParser()
    config.read("../configs/vision_pretreat.ini")

    # get color scalars
    pp = Pretreat(pics, config)
    result = pp.sample_scalars

    arr = np.array(result)
    pca = PCA(n_components = 2)
    reduced_X = pca.fit_transform(arr)
    plt.scatter(reduced_X[:,0],reduced_X[:,1])
    plt.show() 

    # show scalars
    fig = plt.figure()
    ax1 = plt.axes(projection='3d')
    # ax1 = plt.axes()


    colors = ['black', 'orange',
            'blue', 'green',
            'red', 'yellow']
    
    for i in range(6):
        r = []
        g = []
        b = []
        for j in  range(9):
            b.append(result[i*9+j][0])
            g.append(result[i*9+j][1])
            r.append(result[i*9+j][2])
        ax1.scatter3D(b, g, r, color = colors[i])
        # ax1.scatter(r, g, color=colors[i])
        
    plt.show()