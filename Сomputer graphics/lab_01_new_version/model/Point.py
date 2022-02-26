import math


class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def print(self, end='\n', sep=' '):
        print(f'({self.x}, {self.y})', end=end, sep=sep)

    def likeStr(self):
        return f'{self.x} ; {self.y}'

    def likeFormatStr(self):
        return '(%.3f; %.3f)' % (self.x, self.y)

    @staticmethod
    def isPointsEqual(pointA, pointB):
        return pointA.x == pointB.x and pointA.y == pointB.y

    @staticmethod
    def dist(pointA, pointB):
        return math.sqrt(pow(pointA.x - pointB.x, 2) + pow(pointA.y - pointB.y, 2))
