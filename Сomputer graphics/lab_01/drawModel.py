from math import sqrt
def isPointsOnLine(x1, y1, x2, y2, x3, y3):
    return abs((x3 - x1) * (y2 - y1) - (y3 - y1) * (x2 - x1)) < 1

def isOneLine(a, b, c):
    x1 = isPointsOnLine(a[0], a[1], b[0], b[1], c[0], c[1])
    x2 = isPointsOnLine(b[0], b[1], a[0], a[1], c[0], c[1])
    x3 = isPointsOnLine(a[0], a[1], c[0], c[1], b[0], b[1])
    if x1 + x2 + x3 == 0:
        return False
    return True

def lenSide(firstPoint, secondPoint):
    return ((firstPoint[0] - secondPoint[0]) ** 2 + (firstPoint[1] - secondPoint[1]) ** 2) ** 0.5

def sides(firstPoint, secondPoint, thirdPoint):
    firstSide = lenSide(firstPoint, secondPoint)
    secondSide = lenSide(secondPoint, thirdPoint)
    thirdSide = lenSide(firstPoint, thirdPoint)
    return [firstSide, secondSide, thirdSide]

def lenBisector(firstPoint, secondPoint, thirdPoint):
    a, b, c = sides(firstPoint, secondPoint, thirdPoint)
    p = (a + b + c) / 2
    bisector1 = lenB(a, b, c, p)
    bisector2 = lenB(a, c, b, p)
    bisector3 = lenB(b, a, c, p)
    return bisector1 + bisector2 + bisector3

def lenB(a, b, c, p):
    return 2 * (a * c * p * (p - b))**0.5 / (a + c)


def minThreeElByAttr(list, func):
    min, minEl = None, 0
    for i in range(len(list)):
        for j in range(i + 1, len(list)):
            for k in range(j + 1, len(list)):
                if not isOneLine(list[i], list[j], list[k]):
                    newMin = func(list[i], list[j], list[k])
                    if min == None or newMin < min:
                        min, minEl = newMin, [list[i], list[j], list[k]]
                    print("Точки  -- ", list[i], list[j], list[k], ",  длинна биссектрисы  -- ", round(newMin, 4))

    print("Ответ: ", minEl)
    return minEl
