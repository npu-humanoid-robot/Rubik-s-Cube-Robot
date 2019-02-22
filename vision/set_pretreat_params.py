import numpy as np
import cv2
import configparser


current_point_counter = -1
colors = [(0, 0, 255), (0, 255, 0), (255, 255, 0), (255, 0, 0)]
radius = [0, 0, 0, 0]
points = []

frame = None
M = None

def MouseHandler(event, x, y, flags, param):
    global current_point_counter
    global points
    if event == cv2.EVENT_LBUTTONDOWN :
        current_point_counter += 1
        current_point_counter %= 4
        if len(points) < 4:
            points.append((x, y))
        else:
            points[current_point_counter] = (x, y)
            radius[current_point_counter] = 0
    return 

if __name__ == "__main__":
    cp = cv2.VideoCapture(0)
    cv2.namedWindow("233")
    cv2.setMouseCallback("233", MouseHandler)
    while True:
        _, frame = cp.read()
        cv2.imshow("233", frame)
        
        for i in range(current_point_counter+1):
            if radius[i] < 7:
                radius[i] += 1
            cv2.circle(frame, points[i], radius[i], colors[i], 2)
            frame = cv2.putText(frame, str(i+1), points[i], cv2.FONT_HERSHEY_SIMPLEX, 0.77, (255, 255, 255), 2)
            cv2.imshow("233", frame)
        
        if current_point_counter == 3:
            pts1 = np.float32(points)
            pts2 = np.float32([[0,0],[300,0],[0,300],[300,300]]) 
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
            M = cv2.getPerspectiveTransform(pts1,pts2)
            dst = cv2.warpPerspective(frame,M,(300,300))

            cv2.imshow("fixed", dst)
        key = cv2.waitKey(1)
        if key == ord('q'): 
            break
        elif key-ord('1') <= 3 and key != -1:
            config = configparser.ConfigParser()
            config.read("../configs/vision_pretreat.ini")
            print(config.sections())
            section = 'tran_mat_%d'%(key-ord('1'))
            for i in range(9):
                config[section]['element_%d'%i] = str(M[int(i/3), int(i%3)])
            with open("../configs/vision_pretreat.ini", "w") as r:
                config.write(r)
        # collect images
        elif key-ord('1') >= 4 and key-ord('1') <=8:
            cv2.imwrite("../BackupSource/%d.jpg"%(key-ord('1')), frame)