from model.Point import Point
from model.Line import Line
from model.SetPoints import SetPoints
from model.Tools import Tools
from model.AnalyticalGeometry import AnalyticalGeometry


def findLine(points):
    if points.size() < 2:
        return Tools.EXIT_FAILURE

    if points.size() == 3:
        return points.getPoint(0), points.getPoint(1), [points.getPoint(2)], [points.getPoint(0), points.getPoint(1)], []

    idealMore, idealEqual, idealLess = AnalyticalGeometry.findLeftRightSet(points, Line(points.getPoint(0), points.getPoint(1)))
    idealI, idealJ = 0, 1

    for i in range(points.size() - 1):
        for j in range(i + 1, points.size()):
            more, equal, less = AnalyticalGeometry.findLeftRightSet(points, Line(points.getPoint(i), points.getPoint(j)))
            if abs(more.size() - less.size()) < abs(idealMore.size() - idealLess.size()):
                idealMore, idealEqual, idealLess = more, equal, less
                idealI, idealJ = i, j

    return points.getPoint(idealI), points.getPoint(idealJ), idealMore, idealEqual, idealLess

def minCircle(points):
    return AnalyticalGeometry.findMinCircle(points)


# s = SetPoints(Point(-2, -1), Point(-1, -8), Point(2, 1), Point(2, -2), Point(3, 4), Point(4, 2))
# i, j, more, equal, less = findLine(s)
# i.print()
# j.print()

# s = SetPoints(Point(-2, -1), Point(-1, -8), Point(2, 1), Point(2, -2), Point(3, 4), Point(4, 2))
# c = minCircle(s)
# c.center.print()
# print(c.r)

# s = SetPoints(Point(178, 77), Point(113, 124))
# c = minCircle(s)
# c.center.print()
# print(c.r)

# s = SetPoints(Point(-10, 5), Point(-8, 12), Point(33, 2), Point(100, 100))
# c = minCircle(s)
# c.center.print()
# print(c.r)