import cv2
import numpy as np
import pickle

CP_OPEN = 0
frame = None

current_color_pointer = 0
color = ['White', 'Red', 'Green', 'Yellow', 'Orange', 'Blue']
bgr_color = [(255, 255, 255), (0, 0, 255), (0, 255, 0), (0, 255, 255), (0, 127, 255), (255, 0, 0)]
color2bgr = dict(zip(color, bgr_color))

train_data = []
train_label = []

window_name = "get_color_sample"

def MouseHandler(event, x, y, flags, param):
    global train_label
    global train_data
    if event == cv2.EVENT_LBUTTONDOWN :
        bgr_pix = frame[y:y+1, x:x+1]
        hsv_pix = cv2.cvtColor(bgr_pix, cv2.COLOR_BGR2HSV_FULL)
        lab_pix = cv2.cvtColor(bgr_pix, cv2.COLOR_BGR2LAB)

        whole_vec = np.concatenate((bgr_pix, hsv_pix, lab_pix), axis = 2)
        print(whole_vec[0][0].shape)
        train_label.append(current_color_pointer)
        train_data.append(whole_vec)
        print(whole_vec, current_color_pointer)
    return 



if __name__ == "__main__":
    data_file = open("train_data.bin", 'rb')
    label_file = open("train_label.bin", 'rb')

    train_data = pickle.load(data_file)
    train_label = pickle.load(label_file)
    print(train_data)
    print(train_label)

    cam_idx_file = open("../../BackupSource/cam_idx.bin", 'rb')
    cam_idx_list = pickle.load(cam_idx_file)

    cp = cv2.VideoCapture(cam_idx_list[CP_OPEN])
    cv2.namedWindow(window_name)
    cv2.setMouseCallback(window_name, MouseHandler)
    while True:
        _, frame = cp.read()
        if not _:
            continue
        cv2.rectangle(frame, (10, 10), (100, 100), color2bgr[color[current_color_pointer]], 27)
        cv2.putText(frame, "%s mode"%color[current_color_pointer],  (120, 50), cv2.FONT_HERSHEY_SIMPLEX, 1.5, color2bgr[color[current_color_pointer]], 2)


        print(train_label)
        cv2.imshow(window_name, frame)
        key = cv2.waitKey(1)
        if key == ord('s'): 
            data_file = open("train_data.bin", 'wb')
            label_file = open("train_label.bin", 'wb')
            pickle.dump(train_data, data_file)
            pickle.dump(train_label, label_file)
            data_file.close()
            label_file.close()
        elif key == ord('p'):
            current_color_pointer += 1
            current_color_pointer %= 6
        elif key == ord('d'):
            if len(train_data) > 0:
                del train_data[-1]
                del train_label[-1]
        elif key == ord('q'):
            break
        elif key == ord('c'):
            CP_OPEN += 1
            CP_OPEN %= 2
            print(CP_OPEN)
            cp.open(cam_idx_list[CP_OPEN])