from model.Point import Point
from model.Vector import Vector


class Circle:
    def __init__(self, center, r):
        self.center = center
        self.r = r

    @staticmethod
    def __findCenterHelp(vecAB, vecAC):
        B = vecAB.x * vecAB.x + vecAB.y * vecAB.y
        C = vecAC.x * vecAC.x + vecAC.y * vecAC.y
        D = vecAB.x * vecAC.y - vecAB.y * vecAC.x
        return Point((vecAC.y * B - vecAB.y * C) / (2 * D), (vecAB.x * C - vecAC.x * B) / (2 * D))

    @staticmethod
    def circleFromThree(pointA, pointB, pointC):
        center = Circle.__findCenterHelp(Vector(pointA, pointB), Vector(pointA, pointC))
        center.x += pointA.x
        center.y += pointA.y
        return Circle(center, Point.dist(center, pointA))

    @staticmethod
    def circleFromTwo(pointA, pointB):
        center = Point((pointA.x + pointB.x) / 2, (pointA.y + pointB.y) / 2)
        return Circle(center, Point.dist(pointA, pointB) / 2)
