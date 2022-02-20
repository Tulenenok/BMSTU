from model.Point import Point
from model.Vector import Vector
from model.Line import Line
from model.SetPoints import SetPoints
from model.Circle import Circle
from model.Tools import Tools


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
        more, less, equal = SetPoints(), SetPoints(), SetPoints()
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
        return Point.dist(circle.center, point) <= circle.r

    @staticmethod
    def isAllPointsInsideCircle(setPoints, circle):
        for p in setPoints.getAll():
            if not AnalyticalGeometry.isPointInsideCircle(p, circle):
                return False
        return True

    @staticmethod
    def __minCircleTwo(setPoints, minCircle):
        for i in range(setPoints.size() - 1):
            for j in range(i + 1, setPoints.size()):
                circle = Circle.circleFromTwo(setPoints.getPoint(i), setPoints.getPoint(j))

                if AnalyticalGeometry.isAllPointsInsideCircle(setPoints, circle) \
                        and (minCircle.r == -1 or minCircle.r > circle.r):
                    minCircle = circle

        return minCircle

    @staticmethod
    def __minCircleThree(setPoints, minCircle):
        for i in range(setPoints.size() - 2):
            for j in range(i + 1, setPoints.size() - 1):
                for k in range(j + 1, setPoints.size()):
                    circle = Circle.circleFromThree(setPoints.getPoint(i), setPoints.getPoint(j), setPoints.getPoint(k))
                    if AnalyticalGeometry.isAllPointsInsideCircle(setPoints, circle) \
                            and (minCircle.r == -1 or minCircle.r > circle.r):
                        minCircle = circle

        return minCircle

    """ Найти окружность минимального радиуса, которая содержала бы в себе все точки множества """
    @staticmethod
    def findMinCircle(setPoints):
        if setPoints.size() == 0:
            return Point(0, 0), 0

        if setPoints.size() == 1:
            return setPoints.getPoint(0), 0

        if setPoints.size() == 2:
            return Circle.circleFromTwo(setPoints.getPoint(0), setPoints.getPoint(1))

        if setPoints.size() == 3:
            return Circle.circleFromThree(setPoints.getPoint(0), setPoints.getPoint(1), setPoints.getPoint(2))

        minCircle = AnalyticalGeometry.__minCircleTwo(setPoints, Circle(Point(0, 0), -1))
        if minCircle.r == -1:
            minCircle = AnalyticalGeometry.__minCircleThree(setPoints, minCircleTwo)

        return minCircle
