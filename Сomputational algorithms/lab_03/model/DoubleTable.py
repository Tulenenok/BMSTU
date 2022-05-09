from prettytable import PrettyTable
from model.InterAlgorithms import *

"""         Рудимент предыдущей лабы            """
# *************************************************
# Двумерная интерполяция (по x, y предсказываем z)
# *************************************************


class DoubleTable:
    def __init__(self):
        self.x = []  # одномерный массив
        self.y = []  # одномерный массив
        self.z = []  # двумерный массив

    def inputFromTXTFile(self, filename=FILE_WITH_DOUBLE_TABLE):
        with open(filename, 'r') as fin:
            self.inputFromOpenTXTFile(fin)

    def inputFromOpenTXTFile(self, f):
        self.x = list(map(float, f.readline().split()))
        s = f.readline()
        while s:
            if s == '\n':
                return 1           # строки в файле еще есть
            s = list(map(float, s.split()))
            self.y.append(s[0])
            self.z.append(s[1:])
            s = f.readline()
        return 0                    # строк в файле больше нет

    def print(self):
        resTable = PrettyTable()
        resTable.field_names = ['Y\X'] + [str(x) for x in self.x]

        for i in range(len(self.y)):
            add = [f"{self.y[i]}"]
            for j in range(len(self.z[i])):
                add.append(str(self.z[i][j]))
            resTable.add_row(add)

        print(resTable)

    """ Задача -- провести двумерную интерполяцию (то есть по x, y предсказать z) """
    # nx, ny -- степени полиномов
    # Сначала нужно выбрать ближайшие к x nx + 1 значений и ближайшие к y ny + 1 значений
    # построить таблицу из x и z, провести для каждой строчки интреполяцию Ньютона
    # составить таблицу y и полученных значений
    # провести интреполяцию для них (она будет одна)
    def doubleNewtonInter(self, x, y, nx, ny, showComments=False):
        indXStart, indXEnd = findNearestInd(self.x, x, nx)
        indYStart, indYEnd = findNearestInd(self.y, y, ny)

        YTable = []  # результативная таблица "по строкам"
        for k in range(indYStart, indYEnd):
            tableForNewton = [[self.x[i] for i in range(indXStart, indXEnd)],
                              [self.z[x][k] for x in range(indXStart, indXEnd)]]

            tableNewton, polStr, pol = InterAlgorithms.interpolationNewton(tableForNewton, x)
            YTable += [float(pol)]

        # теперь последняя интерполяция по y и YTable
        tableForNewton = [[self.y[i] for i in range(indYStart, indYEnd)], YTable]
        tableNewton, polStr, pol = InterAlgorithms.interpolationNewton(tableForNewton, y)
        return pol