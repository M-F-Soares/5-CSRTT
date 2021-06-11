import serial.tools.list_ports
import ctypes
import cv2 as cv
import numpy as np
from time import sleep
from datetime import datetime as dt

__arduinoVid__ = '2341'
__arduinoPid__ = '0010'

def findArduino():
    for port in serial.tools.list_ports.comports():
        if  port.vid != None and port.pid != None:
            if ('{:04X}'.format(port.vid) == __arduinoVid__)and('{:04X}'.format(port.pid) == __arduinoPid__):
                result = port.device
    return result

def readUSB(portaUSB):
    global isConnected
    try:
        if portaUSB.inWaiting()>0:
            caracLido = portaUSB.read().decode('utf-8')
            if (caracLido) == 'A':
                isConnected = True
            elif (caracLido) == 'B':
                isConnected = False
    except serial.SerialException:
        pass


screensize = ctypes.windll.user32.GetSystemMetrics(0), ctypes.windll.user32.GetSystemMetrics(1)
__camID__ = None
clicked = False
isConnected = True
cont = 0 

def clickEvent(event, x, y, flags, param):
    global __camID__, clicked
    if event == cv.EVENT_LBUTTONDOWN:
        if (x >= 0 and x < screensize[0]/3) and (y >= 0 and y <= screensize[0]/3):
            __camID__ = 0
            clicked = True
        elif (x >= screensize[0]/3 and x < screensize[0]*2/3) and (y >= 0 and y <= screensize[0]/3):
            __camID__ = 1
            clicked = True
        elif (x >= screensize[0]*2/3 and x < screensize[0]) and (y >= 0 and y <= screensize[0]/3):
            __camID__ = 2
            clicked = True
            
        
def chooseCam(isConnected):
    shape = int(screensize[0]/3), int(screensize[0]/3)
    __webIndex__ = ['%s' % (i) for i in range(100)]
    frames = []
    if isConnected:
        for __webID__ in __webIndex__:
            try:
                cap = cv.VideoCapture(int(__webID__) + cv.CAP_DSHOW)
                if(cap.isOpened()):
                    frames.append('')
                    ret, frames[int(__webID__)] = cap.read()
                    if int(__webID__) <= 0:
                        frame = cv.resize(frames[0], shape)
                    else:
                        frame = np.hstack((frame, cv.resize(frames[int(__webID__)], shape)))
                cap.release()
            except serial.SerialException:
                pass
        if ret== True:
            cv.imshow('CAM', frame)
            cv.moveWindow('CAM', 0, 0)
        while clicked == False:
            cv.setMouseCallback('CAM', clickEvent)
            cv.waitKey(1)
        cv.destroyWindow('CAM')
    return __camID__
        
def beginRecord(index):
    global cont
    try:
        cap = cv.VideoCapture(index + cv.CAP_DSHOW)
        now = dt.now().strftime('%d%m%Y_%H%M')
        codec = cv.VideoWriter_fourcc(*'H264') 
        fps = 30.0
        w = int (cap.get(cv.CAP_PROP_FRAME_WIDTH))
        h = int (cap.get(cv.CAP_PROP_FRAME_HEIGHT))
        out = cv.VideoWriter(now + '.avi', codec, fps, (w, h))
        portaUSB = serial.Serial(findArduino(), 9600, timeout = None)
        while (cap.isOpened()):
            ret, frame = cap.read()
            try:
                if ret == True and isConnected:
                    out.write(frame)
                    readUSB(portaUSB)
                    cv.imshow('Webcam', frame)
                    cv.moveWindow('Webcam', 0, 0)
                    cv.waitKey(1)
                else:
                    break
            except serial.SerialException:
                pass
        portaUSB.close()
        cap.release()
        out.release()
        cv.destroyAllWindows()
    except TypeError:
        pass

if __name__ == '__main__':
    beginRecord(chooseCam(isConnected))
    print(cont)

#"VER" https://stackoverflow.com/questions/6116564/destroywindow-does-not-close-window-on-mac-using-python-and-opencv
#"VER" https://www.youtube.com/watch?v=a7_dBO3EAng