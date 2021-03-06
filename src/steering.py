import numpy as np
import math




class AckermannSimCmd1:
    """
    w - distance beetwen left and right wheels
    l - distance beetwen front and back wheel pairs
    r - radius of wheel
    minR - max value of the turning radius
    ma - maximum rotation angle of the servo
    """
    def __init__(self, w, l, r, minR, ma):
        self.w = w
        self.l = l
        self.r = r
        self.minR = minR
        self.ma = ma    
    def calcCmdServo(self, lvx, servo_a):
        a = np.clip(servo_a, -self.ma, self.ma)
        R = self.l*math.tan(a)
        R = self.minR*(2*(R >= 0)-1) if abs(R) < self.minR else R 
        
        # phi1 = math.atan2()
        # phi2 = math.atan2()




    def calcCmdAngularVel(self, lvx, avz):
    # def calcCmd(self, lvx, avz):
        




    

        



