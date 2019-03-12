from Pretreat import *

import glob
from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


if __name__ == "__main__":
    # load raw pics and config 
    pic_path = "../BackupSource/*.jpg"
    pic_paths = [i for i in glob.glob(pic_path)]
    pics = []
    for i in pic_paths:
        img = cv2.imread(i)
        print(i)
        pics.append(img)
    
    config = configparser.ConfigParser()
    config.read("../configs/vision_pretreat.ini")

    # get color scalars
    pp = Pretreat(pics, config)
    result = pp.sample_scalars

    # show scalars
    fig = plt.figure()
    ax1 = plt.axes(projection='3d')


    colors = ['red', 'orange',
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

    plt.show()