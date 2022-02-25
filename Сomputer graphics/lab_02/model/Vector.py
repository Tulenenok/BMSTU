from model.Point import Point


class Vector:
    def __init__(self, pointStart, pointEnd):
        self.x = pointEnd.x - pointStart.x
        self.y = pointEnd.y - pointStart.y

    """ Косое произведение векторов """
    # Положительно, если поворот от первого вектора ко второму идет против часовой стрелки.
    # Равно нулю, если векторы коллинеарны.
    # Отрицательно, если поворот идет по часовой стрелки.
    @staticmethod
    def skewProductVectors(vecA, vecB):
        return vecA.x * vecB.y - vecA.y * vecB.x