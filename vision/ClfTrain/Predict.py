import cv2
import numpy as np
import pickle
import time


CP_OPEN = 0
frame = None

predict_label = -1
color = ['White', 'Red', 'Green', 'Yellow', 'Orange', 'Blue']
bgr_color = [(255, 255, 255), (0, 0, 255), (0, 255, 0), (0, 255, 255), (0, 127, 255), (255, 0, 0)]
color2bgr = dict(zip(color, bgr_color))

window_name = "color test"

model_name = './now.model'

clf = None

def MouseHandler(event, x, y, flags, param):
    global predict_label

    bgr_pix = frame[y:y+1, x:x+1]
    hsv_pix = cv2.cvtColor(bgr_pix, cv2.COLOR_BGR2HSV_FULL)
    lab_pix = cv2.cvtColor(bgr_pix, cv2.COLOR_BGR2LAB)

    whole_vec = np.concatenate((bgr_pix, hsv_pix, lab_pix), axis = 2).reshape(1, 9)

    starttime = time.time()
    # for i in range(54):
    predict_label = int(clf.predict(whole_vec))
    endtime = time.time()

    print(color[predict_label])
    print("take time:", (endtime-starttime))
    return 

if __name__ == "__main__":
    f = open(model_name, 'rb')
    clf = pickle.load(f)

    cp = cv2.VideoCapture(CP_OPEN)
    cv2.namedWindow(window_name)
    cv2.setMouseCallback(window_name, MouseHandler)

    while True:
        _, frame = cp.read()
        if not _:
            continue
        if predict_label >= 0:
            cv2.putText(frame, "get %s"%color[predict_label],  (120, 50), cv2.FONT_HERSHEY_SIMPLEX, 1.5, color2bgr[color[predict_label]], 2)

        cv2.imshow(window_name, frame)
        key = cv2.waitKey(1)
        if key == ord('q'):
            break
        elif key == ord('c'):
            CP_OPEN = 2-CP_OPEN
            print(CP_OPEN)
            cp.open(CP_OPEN)