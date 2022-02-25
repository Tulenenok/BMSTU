from model.Point import Point
from model.Tools import Tools

class Line:
    def __init__(self, pointA, pointB):
        self.A = pointA.y - pointB.y
        self.B = pointB.x - pointA.x
        self.C = pointA.x * pointB.y - pointA.y * pointB.x

        self.start = pointA                                    # Сохраним две точки, принадлежащие прямой
        self.end = pointB                                      # для дальшейших рассчетов

    def findYByX(self, x):
        return (-self.C - self.A * x) / self.B

    def findXByY(self, y):
        return (-self.C - self.B * y) / self.A
