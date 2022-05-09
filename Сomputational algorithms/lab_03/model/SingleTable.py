from model.InterAlgorithms import *
from model.CubeSpline import *
from model.Polynomial import *

from prettytable import PrettyTable

# ***********************************************
# Одномерная интерполяция (по x предсказываем y)
# ***********************************************


class SingleTable:
    def __init__(self, x=None, y=None):
        """ Создание таблицы на каких-то значениях """

        self.x = x if x else []           # одномерный массив
        self.y = y if y else []           # одномерный массив


    def inputFromTXTFile(self, filename=FILE_WITH_SINGLE_TABLE):
        """ Файл содержит в себе данные в формате: """
        """ x1 y1 """
        """ x2 y2 """
        """ .. .. """

        with open(filename, 'r') as fin:
            s = fin.readline()
            while s:
                _x, _y = map(float, s.split())
                self.x.append(_x)
                self.y.append(_y)
                s = fin.readline()


    def print(self):
        """ Вывод таблицы на экран """

        resTable = PrettyTable()
        resTable.field_names = ['X', 'Y']

        for i in range(len(self.x)):
            resTable.add_row([self.x[i], self.y[i]])

        print(resTable)

    def checkingForAlreadySetPoint(self, x):
        for i, _x in enumerate(self.x):
            if x == _x:
                return i
        return -1

    def NewtonInter(self, x, nx, showComments=False):
        """ Интерполяция по Ньютону """
        """ x -- значение, для которого хотим предсказать y """
        """ nx -- степень полинома """
        """ Возвращается построенный полином в виде объекта класса Polynomial и предсказанный y """

        indXStart, indXEnd = findNearestInd(self.x, x, nx)

        table = [[self.x[i] for i in range(indXStart, indXEnd)], [self.y[i] for i in range(indXStart, indXEnd)]]
        tableNewton, polStr, pol = InterAlgorithms.interpolationNewton(table, x, showComments)

        p = Polynomial(strRepresentation=polStr, variables=['x'])

        return p, float(pol)


    def SplineInter(self, x, nx, showComments=False, cStart=0, cEnd=0):
        """ Интерполяция с помощью сплайнов """
        """ Пока работает только для кубических (т.е. для nx = 3) """

        if nx != 3:
            print('Такого человечество (то есть я) еще не придумало (не написало)')
            return

        # Находим ближайшие к x два значения, чтобы потом работать со сплайном между ними
        indXStart, indXEnd = findNearestInd(self.x, x, 1)

        cubeSp = CubeSpline(self.x, self.y, cStart, cEnd)
        if showComments:
            cubeSp.printXYABCDTable()

        a, b, c, d = cubeSp.a[indXEnd - 1], cubeSp.b[indXEnd - 1], cubeSp.c[indXEnd - 1], cubeSp.d[indXEnd - 1]
        p = Polynomial(variables=['x'])
        p.updateUseData([a, b, c, d], [self.x[indXStart]] * 3)
        p.print(name='CUBE SPLINE POLYNOMIAL')

        return p, p.findValue(x=x)
