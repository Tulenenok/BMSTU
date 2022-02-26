from model.Point import Point
from model.Line import Line
from model.Tools import Tools
from model.AnalyticalGeometry import AnalyticalGeometry
from model.SetPoints import SetPoints

import pandas as pd
import math


def findLine(points):
    if points.size() < 2:
        return Tools.EXIT_FAILURE

    if points.size() == 3:
        return points.getPoint(0), points.getPoint(1), SetPoints([points.getPoint(2)]), \
               SetPoints([points.getPoint(0), points.getPoint(1)]), SetPoints([])

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


# Читает построчно точки из txt-файла (точки записаны в виде x ; y)
def inputPointsTXT(filename):
    if not Tools.isRightFilename(filename) or filename[-4::] != '.txt':
        return -1

    coords = []
    with open(filename, 'r') as fin:
        indLine = 1
        for line in fin:
            try:
                x, y = line.split(Tools.SEPARATOR_COORDS)
                coords.append((float(x), float(y)))
            except:
                return indLine           # Если не получается считать, то вернет номер строки, где произошла ошибка
        return coords                    # Вернет массив координат для рисования


# Читает построчно точки из xlsx-файла (координаты точек записаны в двух столбцах, столбцы называются X, Y, лист Points)
def inputPointsXLSX(filename):
    if not Tools.isRightFilename(filename) or filename[-5::] != '.xlsx':
        return Tools.INVALID_FILENAME

    try:
        xl = pd.ExcelFile(filename.replace('\\', '\\\\'))
        list_points = xl.parse('Points')
        data = list_points[['X', 'Y']]
        x, y = list(data['X']), list(data['Y'])
    except ValueError:
        return Tools.INVALID_LISTNAME
    except KeyError:
        return Tools.INVALID_HEAD
    except:
        return Tools.OBSCURE_ERROR

    try:
        coords = [(float(x[i]), float(y[i])) for i in range(len(x))]
        return coords
    except ValueError:
        return Tools.INVALID_FORMAT_DATA
    except IndexError:
        return Tools.INVALID_DATA
    except:
        return Tools.OBSCURE_ERROR


def findArea(R1, R2, C1, C2):
    return AnalyticalGeometry.totalArea(R1, R2, C1, C2)

def Square(circle):
    return math.pi * circle.r ** 2


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