import cv2
import pickle

if __name__ == "__main__":
    print("How many web cam do your computer have?(include build-in cam)", end='')
    cam_num = int(input())
    if cam_num == 1:
        print("No enough cam!")
        exit()
    
    # cv2.namedWindow("cam frame", cv2.WINDOW_NORMAL)
    cp = cv2.VideoCapture(0)
    cam_idx_list = [0, 0]
    for i in range(cam_num):
        cp.open(i)
        while 1:
            _, frame = cp.read()
            if not _:
                continue
            
            cv2.putText(frame, "Is the up/down cam ?(u/d)", (50, 50), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)
            cv2.imshow("cam frame", frame)
            key = cv2.waitKey(1)
            if key == ord('u'):
                cam_idx_list[0] = i
                break
            elif key == ord('d'):
                cam_idx_list[1] = i
                break
            elif key == ord('q'):
                break
    cam_idx_file = open("../BackupSource/cam_idx.bin", 'wb')
    pickle.dump(cam_idx_list, cam_idx_file)