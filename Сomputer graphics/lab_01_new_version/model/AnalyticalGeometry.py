from model.Point import Point
from model.Vector import Vector
from model.Line import Line
from model.SetPoints import SetPoints
from model.Circle import Circle
from model.Tools import Tools
import math


class AnalyticalGeometry:
    """ Положение точки относительно прямой                          """
    """ > 0 -- выше (правее), == 0 -- на прямой, < 0 -- ниже (левее) """
    @staticmethod
    def positionPointRelativeLine(point, line):
        vam = Vector(line.start, point)
        vab = Vector(line.start, line.end)
        return Vector.skewProductVectors(vab, vam)

    """ Разделить множество точек на три множества: """
    """ 1. Точки выше прямой (правее)               """
    """ 2. Точки на прямой                          """
    """ 3. Точки ниже прямой (левее)                """
    @staticmethod
    def findLeftRightSet(setPoints, line):
        more, less, equal = SetPoints([]), SetPoints([]), SetPoints([])
        for point in setPoints.getAll():
            rc = AnalyticalGeometry.positionPointRelativeLine(point, line)
            if rc > 0:
                more.addPoint(point)
            elif rc < 0:
                less.addPoint(point)
            else:
                equal.addPoint(point)

        return more, equal, less

    @staticmethod
    def isPointInsideCircle(point, circle):
        return Point.dist(circle.center, point) <= circle.r + 1

    @staticmethod
    def isAllPointsInsideCircle(setPoints, circle):
        for p in setPoints.getAll():
            if not AnalyticalGeometry.isPointInsideCircle(p, circle):
                return False
        return True

    @staticmethod
    def isRightCircle(setPoints, circle, *insteadOf):
        for i, p in enumerate(setPoints.getAll()):
            if i in insteadOf:
                print(i)
                continue
            if not AnalyticalGeometry.isPointInsideCircle(p, circle):
                print('Problem')
                p.print()
                return False
        return True

    @staticmethod
    def __minCircleTwo(setPoints, minCircle):
        for i in range(setPoints.size() - 1):
            for j in range(i + 1, setPoints.size()):
                circle = Circle.circleFromTwo(setPoints.getPoint(i), setPoints.getPoint(j))

                if AnalyticalGeometry.isRightCircle(setPoints, circle, i, j) \
                        and (minCircle.r == -1 or minCircle.r > circle.r):
                    minCircle = circle

        return minCircle

    """ МОЖНО ПОСТАВИТЬ МЕТОД isRightCircle для большей уверенности, но и так должно работать """
    @staticmethod
    def __minCircleThree(setPoints, minCircle):
        for i in range(setPoints.size() - 2):
            for j in range(i + 1, setPoints.size() - 1):
                for k in range(j + 1, setPoints.size()):
                    circle = Circle.circleFromThree(setPoints.getPoint(i), setPoints.getPoint(j), setPoints.getPoint(k))
                    if AnalyticalGeometry.isRightCircle(setPoints, circle, i, j, k) \
                            and (minCircle.r == -1 or minCircle.r > circle.r):
                        minCircle = circle

        return minCircle

    """ Найти окружность минимального радиуса, которая содержала бы в себе все точки множества """
    @staticmethod
    def findMinCircle(setPoints):
        if setPoints.size() == 0:
            return Circle(Point(0, 0), 0)

        if setPoints.size() == 1:
            return Circle(setPoints.getPoint(0), 0)

        if setPoints.size() == 2:
            return Circle.circleFromTwo(setPoints.getPoint(0), setPoints.getPoint(1))

        # if setPoints.size() == 3:
        #     return Circle.circleFromThree(setPoints.getPoint(0), setPoints.getPoint(1), setPoints.getPoint(2))

        minCircle = AnalyticalGeometry.__minCircleTwo(setPoints, Circle(Point(0, 0), -1))
        if minCircle.r == -1:
            minCircle = AnalyticalGeometry.__minCircleThree(setPoints, minCircle)

        return minCircle

    # R1 — радиус первой окружности;
    # R2 — радиус второй окружности;
    # D — расстояние между центрами окружностей.
    @staticmethod
    def intersectionSquare(R1, R2, C1, C2):
        D = Point.dist(C1, C2)

        F1 = 2 * math.acos((R1 ** 2 - R2 ** 2 + D ** 2) / (2 * R1 * D))
        F2 = 2 * math.acos((R2 ** 2 - R1 ** 2 + D ** 2) / (2 * R2 * D))

        S1 = R1 ** 2 * (F1 - math.sin(F1)) / 2
        S2 = R2 ** 2 * (F2 - math.sin(F2)) / 2

        return S1 + S2

    @staticmethod
    def totalArea(R1, R2, C1, C2):
        S1 = math.pi * R1 ** 2
        S2 = math.pi * R2 ** 2
        try:
            intrt = AnalyticalGeometry.intersectionSquare(R1, R2, C1, C2)
        except:
            intrt = 0
        return int(S1 + S2 - intrt)
