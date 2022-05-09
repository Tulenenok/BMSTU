from prettytable import PrettyTable

# *******************
# Кубические сплайны
# *******************


class CubeSpline:
    def __init__(self, x, y, cStart=0, cEnd=0):
        """ cStart и cEnd -- заданные краевые значения """
        self.cStart = cStart
        self.cEnd = cEnd

        self.x, self.y, self.h, self.f, self.E, self.n, self.a, self.b, self.c, self.d = self.searchCoeff(x, y)

    def searchCoeff(self, x, y):
        """ По x, y найти коэффициенты сплайна """

        countValues = len(x)
        countSplines = countValues - 1

        h = [''] + [x[i] - x[i - 1] for i in range(1, countValues)]
        f = ['', ''] + [self.__Fi(y[i - 2], y[i - 1], y[i], h[i - 1], h[i]) for i in range(2, countValues)]

        E = ['', '', 0]
        for i in range(2, countValues):
            E.append(self.__Ei__1(h[i - 1], h[i], E[i]))

        n = ['', '', self.cStart]
        for i in range(2, countValues):
            n.append(self.__Ni__1(f[i], h[i - 1], h[i], E[i], n[i]))

        c = [''] + [self.cStart] + [0 for i in range(countValues - 2)] + [self.cEnd]
        for i in range(countValues - 1, 1, -1):
            c[i] = self.__Ci(h[i - 1], h[i], f[i], E[i], n[i], c[i + 1])

        a = [''] + [self.__Ai(y[i - 1]) for i in range(1, countValues)]

        b = [''] + \
            [self.__Bi(h[i], y[i - 1], y[i], c[i], c[i + 1]) for i in range(1, countSplines)] + \
            [self.__Bn(h[countSplines], y[countSplines - 1], y[countSplines], c[countSplines])]

        d = [''] + \
            [self.__Di(c[i], c[i + 1], h[i]) for i in range(1, countSplines)] + \
            [self.__Dn(c[countSplines], h[countSplines])]

        return x, y, h, f, E, n, a, b, c, d

    def printFullCoeffTable(self):
        """ Вывод полной таблицы коэффициентов, включая h, f, E, n """

        resTable = PrettyTable()
        resTable.field_names = ['x', 'y', 'h', 'f', 'E', 'n', 'c', 'a', 'b', 'd']

        for i in range(len(self.x)):
            resTable.add_row([self.x[i], self.y[i], self.h[i], self.f[i], self.E[i], self.n[i],
                              self.c[i], self.a[i], self.b[i], self.d[i]])
        print(resTable)

    def printXYABCDTable(self):
        """ Вывод таблицы коэффициентов, НЕ включая h, f, E, n """

        print('CUBE SPLINE TABLE')

        resTable = PrettyTable()
        resTable.field_names = ['x', 'y', 'a', 'c', 'b', 'd']

        for i in range(len(self.x)):
            resTable.add_row([self.x[i], self.y[i], self.a[i], self.c[i], self.b[i], self.d[i]])
        print(resTable)

    """ Вспомогательные функции подсчета коэффициентов """
    """ Условные обозначения: """
    """ yi    --> y[i]     """
    """ yi_1  --> y[i - 1] """
    """ yi__1 --> y[i + 1] """
    def __Fi(self, yi_2, yi_1, yi, hi_1, hi):
        return 3 * ((yi - yi_1) / hi - (yi_1 - yi_2) / hi_1)

    def __Ei__1(self, hi_1, hi, Ei):
        return - hi / (hi_1 * Ei + 2 * (hi_1 + hi))

    def __Ni__1(self, fi, hi_1, hi, Ei, ni):
        return (fi - hi_1 * ni) / (hi_1 * Ei + 2 * (hi_1 + hi))

    def __Ci(self, hi_1, hi, fi, Ei, ni, ci__1):
        return - hi / (hi_1 * Ei + 2 * (hi_1 + hi)) * ci__1 + (fi - hi_1 * ni) / (hi_1 * Ei + 2 * (hi_1 + hi))

    def __Ai(self, yi_1):
        return yi_1

    def __Bi(self, hi, yi_1, yi, ci, ci__1):
        return (yi - yi_1) / hi - hi * (ci__1 + 2 * ci) / 3

    def __Bn(self, hn, yn_1, yn, cn):
        return (yn - yn_1) / hn - hn * 2 * cn / 3

    def __Di(self, ci, ci__1, hi):
        return (ci__1 - ci) / (3 * hi)

    def __Dn(self, cn, hn):
        return - cn / (3 * hn)