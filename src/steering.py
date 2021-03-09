import numpy as np
import math




class AckermannSimCmd1:
    """
    w - distance beetwen left and right wheels
    l - distance beetwen front and back wheel pairs
    r - radius of wheel
    minR - max value of the turning radius
    ma - maximum rotation angle of the servo
    servo_a > 0 - right
    """
    def __init__(self, w, l, r, ma, k):
        self.w = w
        self.l = l
        self.r = r
        # self.minR = minR
        self.ma = ma    
        # self.k = 
    def calcCmdServo(self, motor, servo_a):
        a = np.clip(servo_a, -self.ma, self.ma)
        R = self.l*math.tan(a)
        R = self.minR*(2*(R >= 0)-1) if abs(R) < self.minR else R 
        if servo_a == 0:
            return motor, 0, 0
        a0 = math.radians(a)
        if a0 > 0:
            phi0 = math.pi - a0
            R = self.l*math.tan(phi0)
            l1 = R+self.w/2
            l2 = R-self.w/2
            phi1 = math.atan(l1/self.l)
            phi2 = math.atan(l2/self.l)
            a1 = math.pi - phi1
            a2 = math.pi - phi2
        else a0 < 0:
            phi0 = math.pi - math.abs(a0)
            R = self.l*math.tan(phi0)
            l1 = R-self.w/2
            l2 = R+self.w/2
            phi1 = math.atan(l1/self.l)
            phi2 = math.atan(l2/self.l)
            a1 = -(math.pi - phi1)
            a2 = -(math.pi - phi2)
        return motor, a1, a2


        # phi1 = math.atan2()
        # phi2 = math.atan2()




    # def calcCmdAngularVel(self, lvx, avz):
    # def calcCmd(self, lvx, avz):
        




    

        



