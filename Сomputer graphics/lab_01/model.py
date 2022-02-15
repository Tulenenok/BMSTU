# Дано множество точек в виде массива кортежей
# Найти прямую, проходящую через две точки так, чтобы оставшиеся точки разбивались на два множества так, что их мощности
# отличались наиболее незначительно

# Косое произведение векторов
# Положительно, если поворот от первого вектора ко второму идет против часовой стрелки.
# Равно нулю, если векторы коллинеарны.
# Отрицательно, если поворот идет по часовой стрелки.

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
    return (point_b[1] - point_a[1]) * (x -  point_a[0]) // (point_b[0] - point_a[0]) + point_a[1]

# Test
# points = [(0, 6), (-4, 5), (2, 4), (-2, 3), (3, 2), (-4, 1), (2, -1), (-2, -2), (4, -3), (0, -3)]
#points = [(-3, 2), (-2, -2), (4, 4), (2, -2), (6, -1)]
#print(findLine(points))
#