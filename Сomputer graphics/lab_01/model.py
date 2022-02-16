# Дано множество точек в виде массива кортежей
# Найти прямую, проходящую через две точки так, чтобы оставшиеся точки разбивались на два множества так, что их мощности
# отличались наиболее незначительно

# Косое произведение векторов
# Положительно, если поворот от первого вектора ко второму идет против часовой стрелки.
# Равно нулю, если векторы коллинеарны.
# Отрицательно, если поворот идет по часовой стрелки.

import math
import ctypes

def skewProductVectors(vec_a, vec_b):
    return vec_a[0] * vec_b[1] - vec_a[1] * vec_b[0]

def relationshipsPointLine(point_m, point_a, point_b):
    vec_am = (point_m[0] - point_a[0], point_m[1] - point_a[1])
    vec_ab = (point_b[0] - point_a[0], point_b[1] - point_a[1])

    return skewProductVectors(vec_ab, vec_am)                  # > 0 -- (правее), < 0 -- ниже(левее)

# Найти на какие множества разбиватеся общее множество прямой с координатами coord_a, coord_b
def findLeftRightSet(points, point_a, point_b):
    more, less, equal = [], [], []
    for point in points:
        rc = relationshipsPointLine(point, point_a, point_b)
        if rc > 0:
            more.append(point)
        elif rc < 0:
            less.append(point)
        else:
            equal.append(point)

    return more, equal, less

def findLine(points):
    if len(points) < 2:
        return 0

    idealMore, idealEqual, idealLess = findLeftRightSet(points, points[0], points[1])
    idealI, idealJ = 0, 1

    for i in range(len(points) - 1):
        for j in range(i + 1, len(points)):
            more, equal, less = findLeftRightSet(points, points[i], points[j])
            if abs(len(more) - len(less)) < abs(len(idealMore) - len(idealLess)):
                idealMore, idealEqual, idealLess = more, equal, less
                idealI, idealJ = i, j

    return points[idealI], points[idealJ], idealMore, idealEqual, idealLess

def ByXFindYOnLine(x, point_a, point_b):
    return (point_b[1] - point_a[1]) * (x - point_a[0]) / (point_b[0] - point_a[0]) + point_a[1]

# Test
# points = [(0, 6), (-4, 5), (2, 4), (-2, 3), (3, 2), (-4, 1), (2, -1), (-2, -2), (4, -3), (0, -3)]
#points = [(-3, 2), (-2, -2), (4, 4), (2, -2), (6, -1)]
#print(findLine(points))
#

# def dist(A, B):
#     return math.sqrt(pow(A[0] - B[0], 2) + pow(A[1] - B[1], 2))
#
# def getCircleCenter(bx, by, cx, cy):
#     B = bx * bx + by * by
#     C = cx * cx + cy * cy
#     D = bx * cy - by * cx
#     return [(cy * B - by * C) / (2 * D), (bx * C - cx * B) / (2 * D)]
#
# def circleThreePoints(A, B, C):
#     I = getCircleCenter(B[0] - A[0], B[1] - A[1], C[0] - A[0], C[1] - A[1])
#     I[0] += A[0]
#     I[1] += A[1]
#     return I, dist(I, A)
#
# def circleTwoPoints(A, B):
#     C = ((A[0] + B[0]) / 2, (A[1] + B[1]) / 2)
#     return C, dist(A, B) / 2
#
# def minCircleTrivial(points):
#     if len(points) == 0:
#         return (0, 0), 0
#     elif len(points) == 1:
#         return points[0], 0
#     elif len(points) == 2:
#         return circleTwoPoints(points[0], points[1])
#
#     for i in range(3):
#         for j in range(i + 1, 3):
#             c = circleTwoPoints(points[i], points[j])
#             if isValidCircle(c, points):
#                 return c
#
#     return circleThreePoints(points[0], points[1], points[2])
#
# def isInside(circle, point):
#     return dist(circle[0], point) <= circle[1]
#
# def isValidCircle(circle, points):
#     for p in points:
#         if not isInside(circle, p):
#             return False
#     return True
#
# """
# алгоритм welzl
#     вход: Конечные множества P и R точек на плоскости |R| ≤ 3.
#     вывод: Минимальный диск, заключающий P с R на границе.
#
# Если  P пусто или |R| = 3, то
#     Вернуть trivial(R)
#
# Выбрать p в P
#     D := welzl(P − {p}, R)
#     Если  p находится в D, то
#         Вернуть  D
#
#     Верните welzl(P − {p}, R ∪ {p})
# """
#
# def minCircle(points, R, n):
#     if n == 0 or len(R) == 3:
#         return minCircleTrivial(R)
#
#     # print(n)
#     # print(points)
#     p = points[0]
#     points[0], points[len(points) - 1] = points[len(points) - 1], points[0]
#     # p = points.pop()
#     d = minCircle(points, R, n - 1)
#
#     if isInside(d, p):
#         return d
#
#     R.append(p)
#     return minCircle(points, R, n - 1)


# mec = minCircle([(0, 0), (0, 1), (1, 0)])
# print("Center = { ", mec[0], " } Radius = ", mec[1])                  # Center = {  (0.5, 0.5)  } Radius =  0.707106
#
# mec = minCircle([(5, -2), (-3, -2), (-2, 5), (1, 6), (0, 2)])
# print("Center = { ", mec[0], " } Radius = ", mec[1])                  # Center = {  [1.0, 1.0]  } Radius =  5.0

# mec = minCircle([(95, 214), (81, 129), (60, 71)], [])                 # center =  (77.5, 142.5) r  73.610461213064
# print("Center = { ", mec[0], " } Radius = ", mec[1])                  # Center = {  [1.0, 1.0]  } Radius =  5.0
#
# mec = minCircle([(141, 165), (53, 104), (93, 92), (131, 75), (242, 109)], [], 5)  # {  (308.5, 255.0)  } Radius =  136.1993024945429
# print("Center = { ", mec[0], " } Radius = ", mec[1])                  # Center = {  [1.0, 1.0]  } Radius =  5.0


#points =  [(141, 165), (53, 104), (93, 92), (131, 75), (242, 109)]
#center =  [104.63543091655266, 123.48495212038304] r  55.18950158383116


def dist(a, b):
    return math.sqrt(pow (a[0] - b[0], 2) + pow (a[1] - b[1], 2))

def is_inside(c, p):
    return dist(c[0], p) <= c[1]

def get_circle_center(bx, by, cx, cy):
    B = bx * bx + by * by
    C = cx * cx + cy * cy
    D = bx * cy - by * cx
    return [(cy * B - by * C) // (2 * D), (bx * C - cx * B) // (2 * D) ]

def circle_from_three( A, B, C):
    I = get_circle_center(B[0] - A[0], B[1] - A[1], C[0] - A[0], C[1] - A[1])
    I[0] += A[0]
    I[1] += A[1]
    return I, dist(I, A)

def circle_from_two(A, B):
    C = (A[0] + B[0]) / 2.0, (A[1] + B[1]) / 2.0
    return C, dist(A, B) / 2.0

def is_valid_circle(circle, P):
    for p in P:
        if not is_inside(circle, p):
            return False
    return True

def min_circle_trivial(points):
    if len(points) == 0:
        return (0, 0), 0

    elif len(points) == 1:
        return points[0], 0

    elif len(points) == 2:
        return circle_from_two(points[0], points[1])

    for i in range(3):
        for j in range(i + 1, 3):
            c = circle_from_two(points[i], points[j])
            if is_valid_circle(c, points):
                return c

    return circle_from_three(points[0], points[1], points[2])

def welzl_helper(points, R, n):
    if n == 0 or len(R) == 3:
        return min_circle_trivial(R)

    print("N = ", n, "\n", points)
    p = points[0]
    points[0], points[n - 1] = points[n - 1], points[0]
    print(points)

    d = welzl_helper(points, R, n - 1)

    if (is_inside(d, p)):
        return d

    R.append(p)

    return welzl_helper(points, R, n - 1)

def minCircle(points):
    p_copy = points[:]
    return welzl_helper(p_copy, [], len(p_copy))

# mec = minCircle([(202, 329), (317, 262), (339, 313), (374, 163), (255, 198)])  # {  (308.5, 255.0)  } Radius =  136.1993024945429
# print("Center = { ", mec[0], " } Radius = ", mec[1])                  # Center = {  [1.0, 1.0]  } Radius =  5.0

def enumMinCircle(points):
    minCenter, minRadius = -1, -1
    for i in range(len(points) - 1):
        for j in range(i + 1, len(points)):
            circle = circle_from_two(points[i], points[j])
            if is_valid_circle(circle, points) and (minRadius == -1 or minRadius > circle[1]):
                minCenter, minRadius = circle[0], circle[1]

    if minRadius != -1:
        return minCenter, minRadius

    for i in range(len(points) - 2):
        for j in range(i + 1, len(points) - 1):
            for k in range(j + 1, len(points)):
                circle = circle_from_three(points[i], points[j], points[k])
                if is_valid_circle(circle, points) and (minRadius == -1 or minRadius > circle[1]):
                    minCenter, minRadius = circle[0], circle[1]

    return minCenter, minRadius


# mec = minCircle([(94, 272), (171, 212), (86, 147), (73, 191)])  # {  (308.5, 255.0)  } Radius =  136.1993024945429
# print("Center = { ", mec[0], " } Radius = ", mec[1])                  # Center = {  [1.0, 1.0]  } Radius =  5.0


# R1 — радиус первой окружности;
# R2 — радиус второй окружности;
# D — расстояние между центрами окружностей.
def intersectionSquare(R1, R2, C1, C2):
    D = dist(C1, C2)

    F1 = 2 * math.acos((R1**2 - R2**2 + D**2) / (2 * R1 * D))
    F2 = 2 * math.acos((R2**2 - R1**2 + D**2) / (2 * R2 * D))

    S1 = R1**2 * (F1 - math.sin(F1)) / 2
    S2 = R2**2 * (F2 - math.sin(F2)) / 2

    return S1 + S2

def totalArea(R1, R2, C1, C2):
    S1 = math.pi * R1**2
    S2 = math.pi * R2**2

    return S1 + S2 - intersectionSquare(R1, R2, C1, C2)

print(intersectionSquare(2, 4, (0, 0), (3, 0)))






