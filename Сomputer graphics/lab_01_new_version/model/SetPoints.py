from model.Point import Point
from model.Tools import Tools


class SetPoints:
    def __init__(self, points):
        self.__data = []
        for p in points:
            self.addPoint(p)

    def addPoint(self, point):
        if self.isPointInSet(point):                     # Если точка уже есть в множестве, то добавлять ее не нужно
            return Tools.EXIT_FAILURE

        self.__data.append(point)
        return Tools.EXIT_SUCCESS

    def removePoint(self, point):
        for i, p in enumerate(self.__data):
            if Point.isPointsEqual(p, point):
                self.__data.pop(i)
                return Tools.EXIT_SUCCESS

        return Tools.EXIT_FAILURE

    def isPointInSet(self, point):
        for i, p in enumerate(self.__data):
            if Point.isPointsEqual(p, point):
                return True
        return False

    def size(self):
        return len(self.__data)

    def getPoint(self, index):
        return self.__data[index]

    def setPoint(self, index, newValue):
        self.__data[index] = newValue

    def print(self, end='\n', sep=' '):
        for point in self.__data:
            point.print(end, sep)
        print()

    def getAll(self):
        return self.__data

    def cleanAll(self):
        self.__data.clear()

    """ Применить какой-то метод, общий для всех элементов множества, к каждому элементу """
    def wrap(self, funcPoint, *args):
        for point in self.__data:
            point.funcPoint(args)


""" Test """
# s = SetPoints(Point(1, 2), Point(1, 2), Point(2, 3), Point(1, 9), Point(4, 5))
# s.print(end=' ')
# s.addPoint(Point(3, 4))
# s.print(end=' ')
# s.addPoint(Point(2, 3))
# s.print(end=' ')
# s.removePoint(Point(2, 3))
# s.print(end=' ')
# s.removePoint(Point(4, 5))
# s.print(end=' ')
# s.removePoint(Point(1, 1))
# s.print(end=' ')

