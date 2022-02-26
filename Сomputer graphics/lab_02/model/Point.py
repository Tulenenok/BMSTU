import math


class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def print(self, end='\n', sep=' '):
        print(f'({self.x}, {self.y})', end=end, sep=sep)

    def likeStr(self):
        return f'{self.x} ; {self.y}'

    @staticmethod
    def isPointsEqual(pointA, pointB):
        return pointA.x == pointB.x and pointA.y == pointB.y

    @staticmethod
    def dist(pointA, pointB):
        return math.sqrt(pow(pointA.x - pointB.x, 2) + pow(pointA.y - pointB.y, 2))

    # mode -- в чем задается угол (gr - градусы, r - радианы)
    # side -- в какую сторону поворачивать положительные градусы
    def rotate(self, pointCenter, alpha, mode='gr', side='right'):
        if mode == 'gr':
            alpha = math.radians(alpha)
        if mode == 'right':
            alpha = -alpha

        evk_x = self.x - pointCenter.x
        evk_y = self.y - pointCenter.y
        rotate_evk_x = evk_x * math.cos(alpha) - evk_y * math.sin(alpha)
        rotate_evk_y = evk_x * math.sin(alpha) + evk_y * math.cos(alpha)
        self.x = rotate_evk_x + pointCenter.x
        self.y = rotate_evk_y + pointCenter.y

    def shift(self, xShift, yShift):
        self.x += xShift
        self.y += yShift

    def scale(self, k):
        self.x *= k
        self.y *= k
